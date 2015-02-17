#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#include "hulkinizer.h"

int main()
{
    VideoCapture c1("data/trellis.avi");
//    VideoCapture video("test.avi");

//    CascadeClassifier
//            clasif("data/haarcascade_frontalface_alt2.xml");

    HULKINIZER myHulk;

    while (1)
    {
        Mat myImage,greyimage,rgb;

        c1 >> myImage;
//        c1.read(rgb);
        if (myImage.empty()) break;
//        vector<Rect> detecciones_vector;
//        clasif.detectMultiScale(myImage,detecciones_vector,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30), Size(200,200));
//        vector<Mat> canalesIm;
//        split(myImage,canalesIm);

////        for (int i=0;i<detecciones_vector.size();i++)
////        {
////            vector<Mat> canalesIm;
////            split(myImage,canalesIm);
////            canalesIm[1](detecciones_vector[i]) = 2*canalesIm[1](detecciones_vector[i]);
////        }

//        for (int i=0;i<detecciones_vector.size();i++)
//        {
//            Mat face = canalesIm[1](detecciones_vector[i]);
//            face = 2*face;
//        }

//        merge(canalesIm,myImage);

//        for (int i=0;i<detecciones_vector.size();i++)
//            rectangle(myImage,detecciones_vector[i],CV_RGB(255,0,0));

        Mat result = myHulk.run(myImage,HULKINIZER::Hulk);
        cout << "aaa" << endl;

        imshow("frame",result);
        char k = waitKey(10);
        if (k=='q') break;

    }
    return 0;
}
