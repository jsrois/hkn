#include "hulkinizer.h"
#include <iostream>
#include "nulldefs.h"
#include "mysqldatabase.hpp"
using namespace std;

#define THRESHOLD 0.5

Hulkinizer::Hulkinizer(int doFaceDetection)
{
    this->_doFaceDetection = doFaceDetection;
    if (doFaceDetection == 1)
    {
    _classifier = new CascadeClassifier("data/haarcascade_frontalface_alt2.xml");
    }
    else
    {
        _classifier = new CascadeClassifier("data/haarcascade_mcs_upperbody.xml");
    }

}

Hulkinizer::~Hulkinizer()
{
    delete _classifier;
}

Mat Hulkinizer::run(Mat image, int featureType)
{
    if (_doFaceDetection == 1)
    {
        Size minimumSize = Size(30,30);
        Size maximumSize = Size(200,200);
        _classifier->detectMultiScale(image,_detectionVector,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, minimumSize, maximumSize);
    }
    else
    {
        Size minimumSize = Size(80,80);
        Size maximumSize = Size(200,200);
        _classifier->detectMultiScale(image,_detectionVector,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, minimumSize, maximumSize);
    }

    if (featureType == Hulk)
    {
        vector<Mat> imageChannels;
        split(image,imageChannels);
        for (int i=0;i<_detectionVector.size();i++)
        {
            Mat face = imageChannels[1](_detectionVector[i]);
            face = 2*face;
        }
        merge(imageChannels,image);

    }
    else if (featureType == DrManhattan)
    {
        vector<Mat> imageChannels;
        split(image,imageChannels);
        for (int i=0;i<_detectionVector.size();i++)
        {
            Mat face = imageChannels[0](_detectionVector[i]);
            face = 2*face;
        }
        merge(imageChannels,image);

    }
    else if (featureType == HellBoy)
    {
        vector<Mat> imageChannels;
        split(image,imageChannels);
        for (int i=0;i<_detectionVector.size();i++)
        {
            Mat face = imageChannels[2](_detectionVector[i]);
            face = 2*face;
        }
        merge(imageChannels,image);

    }
    else if (featureType == XYZfeatures)
    {
        Mat hsvImage;
        cvtColor(image,hsvImage,CV_BGR2HSV);
        for (int i=0;i<_detectionVector.size();i++)
        {
            image(_detectionVector[i]) = 1.0*hsvImage(_detectionVector[i]);

            if (this->classifySVM(image(_detectionVector[i]))<THRESHOLD)
                MySQLDatabase::addImageToDatabase(image);
        }

    }
    addDetections(image);

    return image;
}

void Hulkinizer::addDetections(Mat &im)
{

    for (int i=0;i<_detectionVector.size();i++)
        rectangle(im,_detectionVector[i],CV_RGB(255,0,0));
}

float Hulkinizer::classifySVM(Mat image)
{
    float returnedValue = 0;
    for (int i=0;i<_detectionVector.size();i++)
    {
      doStuffWithImage(image(_detectionVector[i]));
      /*fake score*/
      RNG rng;
      returnedValue = (float) rng.gaussian(0.05)+0.5;
    }
    return returnedValue;
}

