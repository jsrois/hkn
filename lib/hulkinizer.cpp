#include "hulkinizer.h"
#include <iostream>
#include "nulldefs.h"
#include "mysqldatabase.hpp"
using namespace std;

#define THRESHOLD 0.5

Hulkinizer::Hulkinizer(int detectorType)
{
    _detector = Detector::create(detectorType);
    _detector->init();
}

Hulkinizer::~Hulkinizer()
{

}

Mat Hulkinizer::run(Mat image, int featureType)
{
    _detector->run(image,_detectionVector);

    Mat processedImage;

    if (featureType == Hulk)
    {
        hulkFeatureExtraction(image,processedImage);
    }
    else if (featureType == DrManhattan)
    {
        manhattanFeatureExtraction(image,processedImage);
    }
    else if (featureType == HellBoy)
    {
        hellboyFeatureExtraction(image,processedImage);
    }
    else if (featureType == XYZfeatures)
    {
        xyzFeatureExtraction(image,processedImage);

    }
    addDetections(processedImage );

    return processedImage;
}



void Hulkinizer::hulkFeatureExtraction(const Mat &input, Mat &output)
{
    vector<Mat> imageChannels;
    split(input,imageChannels);
    for (int i=0;i<_detectionVector.size();i++)
    {
        Mat face = imageChannels[1](_detectionVector[i]);
        face = 2*face;
    }
    merge(imageChannels,output);
}

void Hulkinizer::hellboyFeatureExtraction(const Mat &input, Mat &output)
{
    vector<Mat> imageChannels;
    split(input,imageChannels);
    for (int i=0;i<_detectionVector.size();i++)
    {
        Mat face = imageChannels[2](_detectionVector[i]);
        face = 2*face;
    }
    merge(imageChannels,output);
}

void Hulkinizer::manhattanFeatureExtraction(const Mat &input, Mat &output)
{
    vector<Mat> imageChannels;
    split(input,imageChannels);
    for (int i=0;i<_detectionVector.size();i++)
    {
        Mat face = imageChannels[0](_detectionVector[i]);
        face = 2*face;
    }
    merge(imageChannels,output);
}

void Hulkinizer::xyzFeatureExtraction(const Mat &input, Mat &output)
{
    output = input.clone();
    Mat hsvImage;
    cvtColor(input,hsvImage,CV_BGR2HSV);
    for (int i=0;i<_detectionVector.size();i++)
    {
        output(_detectionVector[i]) = 1.0*hsvImage(_detectionVector[i]);

        if (this->classifySVM(output(_detectionVector[i]))<THRESHOLD)
            MySQLDatabase::addImageToDatabase(output);
    }
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

