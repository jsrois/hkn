#ifndef DELEGATES_H
#define DELEGATES_H
#include "hulkinizer.h"
#include <opencv2/opencv.hpp>
using namespace cv;
namespace hulkinizer
{


class Hulkinizer::PImpl
{
public:
    class Detector *               _detector;
    class FeatureExtractor*  _featExtraction;
    std::vector<Rect> _detectionVector;
    void addDetections(Mat& im);
};

class Detector
{
public:

    // factory method
    static Detector* create(int detectorType);

    // pure virtual methods
    virtual void init() = 0;
    virtual void run(const Mat&, vector<Rect>&) = 0;
};

class FeatureExtractor
{
public:
    // factory method
    static FeatureExtractor * create(int);

    // pure virtual methods
    virtual void run(const Mat & input, vector<Rect> roiVector , Mat& output) = 0;
};

}

#endif // DELEGATES_H

