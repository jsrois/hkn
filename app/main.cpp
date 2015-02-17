#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#include <hulkinizer.h>
using namespace hulkinizer;

int main()
{
    VideoCapture c1("data/trellis.avi");

    Hulkinizer myHulk;



    while (1)
    {
        Mat myImage;

        c1 >> myImage;
        if (myImage.empty()) break;

        Mat result = myHulk.run(myImage);

        if (myHulk.classifySVM(result)<0.5)
            putText(result,"Male",Point(20,20),1,1.0,CV_RGB(255,255,255));

        imshow("frame",result);
        char k = waitKey(10);
        if (k=='q') break;

    }
    return 0;
}
