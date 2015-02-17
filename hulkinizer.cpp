#include "hulkinizer.h"

HULKINIZER::HULKINIZER() :
    clasif(new CascadeClassifier("haarcascade_mcs_upperbody.xml"))
{

}

HULKINIZER::~HULKINIZER()
{
    delete clasif;
}




Mat HULKINIZER::run(Mat image, int TYPE)
{
    clasif->detectMultiScale(image,vector_detecciones,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, Size(80, 80), Size(200,200));


    //        for (int i=0;i<detecciones_vector.size();i++)
    //        {
    //            vector<Mat> canalesIm;
    //            split(myImage,canalesIm);
    //            canalesIm[1](detecciones_vector[i]) = 2*canalesIm[1](detecciones_vector[i]);
    //        }


    if (TYPE == Hulk)
    {
        vector<Mat> canalesIm;
        split(image,canalesIm);
        for (int i=0;i<vector_detecciones.size();i++)
        {
            Mat face = canalesIm[1](vector_detecciones[i]);
            face = 2*face;
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

