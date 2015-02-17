#include "hulkinizer.h"
#include <iostream>
#include "nulldefs.h"
#include "mysqldatabase.hpp"
using namespace std;

#define THRESHOLD 0.5

HULKINIZER::HULKINIZER(int FD)
{
    this->FD = FD;
    if (FD == 1)
    {
    clasif = new CascadeClassifier("data/haarcascade_frontalface_alt2.xml");
    }
    else
    {
        clasif = new CascadeClassifier("data/haarcascade_mcs_upperbody.xml");
    }

}

HULKINIZER::~HULKINIZER()
{
    delete clasif;
}




Mat HULKINIZER::run(Mat image, int TYPE)
{
    if (FD == 1)
    {
        Size minimo = Size(30,30);
        Size maximo = Size(200,200);
        clasif->detectMultiScale(image,vector_detecciones,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, minimo, maximo);
    }
    else
    {
        Size minimo = Size(80,80);
        Size maximo = Size(200,200);
        clasif->detectMultiScale(image,vector_detecciones,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, minimo, maximo);
    }

    //        for (int i=0;i<detecciones_vector.size();i++)
    //        {
    //            vector<Mat> canalesIm;
    //            split(myImage,canalesIm);
    //            canalesIm[1](detecciones_vector[i]) = 2*canalesIm[1](detecciones_vector[i]);
    //        }


    cout << "llego aquí" << endl;
    if (TYPE == Hulk)
    {
        vector<Mat> canalesIm;
        split(image,canalesIm);
        for (int i=0;i<vector_detecciones.size();i++)
        {
            Mat face = canalesIm[1](vector_detecciones[i]);
            face = 2*face;
            cout << "aaa" << endl;
        }
        merge(canalesIm,image);

    }
    else if (TYPE == DrManhattan)
    {
        vector<Mat> canalesIm;
        split(image,canalesIm);
        for (int i=0;i<vector_detecciones.size();i++)
        {
            Mat face = canalesIm[0](vector_detecciones[i]);
            face = 2*face;
        }
        merge(canalesIm,image);

    }
    else if (TYPE == HellBoy)
    {
        vector<Mat> canalesIm;
        split(image,canalesIm);
        for (int i=0;i<vector_detecciones.size();i++)
        {
            Mat face = canalesIm[2](vector_detecciones[i]);
            face = 2*face;
        }
        merge(canalesIm,image);

    }
    else if (TYPE == XYZfeatures)
    {
        Mat hsvImage;
        cvtColor(image,hsvImage,CV_BGR2HSV);
        for (int i=0;i<vector_detecciones.size();i++)
        {
            image(vector_detecciones[i]) = 1.0*hsvImage(vector_detecciones[i]);

            if (this->CLASSIFY_SVM(image(vector_detecciones[i]))<THRESHOLD)
                MySQLDatabase::addImageToDatabase(image);
        }

    }

    //    for (int i=0;i<detecciones_vector.size();i++)
    //        rectangle(image,detecciones_vector[i],CV_RGB(255,0,0));

    addDetections(image);

    return image;
}

void HULKINIZER::addDetections(Mat &im)
{

    for (int i=0;i<vector_detecciones.size();i++)
        rectangle(im,vector_detecciones[i],CV_RGB(255,0,0));
}

float HULKINIZER::CLASSIFY_SVM(Mat image)
{
    float ret_val = 0;
    for (int i=0;i<vector_detecciones.size();i++)
    {
      doStuffWithImage(image(vector_detecciones[i]));
      /*fake score*/
      RNG rng;
      ret_val = (float) rng.gaussian(0.05)+0.5;
    }
    return ret_val;
}

