#ifndef HULKINIZER_H
#define HULKINIZER_H
#include <opencv2/opencv.hpp>
using namespace cv;


class Hulkinizer
{
    CascadeClassifier * _classifier;
    std::vector<Rect> _detectionVector;
    int _doFaceDetection;/*1 = Face detection, 0 = H&S detection */
protected:
    void runDetection(const Mat &image);
    void hulkFeatureExtraction(const Mat& input, Mat& output);
    void hellboyFeatureExtraction(const Mat& input, Mat& output);
    void manhattanFeatureExtraction(const Mat& input, Mat& output);
    void xyzFeatureExtraction(const Mat& input, Mat& output);
    void addDetections(Mat& im);
public:

    enum {Hulk = 0, DrManhattan = 1, HellBoy = 2, XYZfeatures = 3};

    Hulkinizer(int doFaceDetection = 1);
    ~Hulkinizer();
    Mat run(Mat image, int featureType=Hulk);
    float classifySVM(Mat image);
};

#endif // HULKINIZER_H
