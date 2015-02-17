#ifndef HULKINIZER_H
#define HULKINIZER_H
#include <opencv2/opencv.hpp>
using namespace cv;



class HULKINIZER
{
    CascadeClassifier *clasif;
    std::vector<Rect> vector_detecciones;

public:



    HULKINIZER();
    ~HULKINIZER();

    Mat run(Mat image, int TYPE=Hulk);
protected:
    void addDetections(Mat& im);
public:
    enum {Hulk = 0, DrManhattan = 1, HellBoy = 2, XYZfeatures = 3};
};

#endif // HULKINIZER_H
