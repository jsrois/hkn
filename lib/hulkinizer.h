#ifndef HULKINIZER_H
#define HULKINIZER_H
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
using namespace cv;
using namespace std;

class Detector
{
public:
    enum {faceDetector = 0, headAndShoulderDetector = 1};

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


class Hulkinizer
{
    Detector *               _detector;
    FeatureExtractor*  _featExtraction;
    std::vector<Rect> _detectionVector;

protected:
    void addDetections(Mat& im);
public:

    enum {Hulk = 0, DrManhattan = 1, HellBoy = 2, XYZfeatures = 3};

    Hulkinizer(int detectorType = Detector::faceDetector, int featureType = Hulk);
    ~Hulkinizer();
    Mat run(Mat image);
    float classifySVM(Mat image);
};

#endif // HULKINIZER_H
