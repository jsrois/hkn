#ifndef HULKINIZER_H
#define HULKINIZER_H
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;

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
    virtual void run(const Mat&, Mat) = 0;
};


class Hulkinizer
{
    Detector * _detector;
    std::vector<Rect> _detectionVector;

protected:
    void hulkFeatureExtraction(const Mat& input, Mat& output);
    void hellboyFeatureExtraction(const Mat& input, Mat& output);
    void manhattanFeatureExtraction(const Mat& input, Mat& output);
    void xyzFeatureExtraction(const Mat& input, Mat& output);
    void addDetections(Mat& im);
public:

    enum {Hulk = 0, DrManhattan = 1, HellBoy = 2, XYZfeatures = 3};

    Hulkinizer(int detectorType = Detector::faceDetector);
    ~Hulkinizer();
    Mat run(Mat image, int featureType=Hulk);
    float classifySVM(Mat image);
};

#endif // HULKINIZER_H
