#ifndef HULKINIZER_H
#define HULKINIZER_H
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
using namespace cv;
using namespace std;

namespace hulkinizer
{

class Hulkinizer
{
    class Detector *               _detector;
    class FeatureExtractor*  _featExtraction;
    std::vector<Rect> _detectionVector;

protected:
    void addDetections(Mat& im);
public:
    enum {faceDetector = 0, headAndShoulderDetector = 1};
    enum {Hulk = 0, DrManhattan = 1, HellBoy = 2, XYZfeatures = 3};

    Hulkinizer(int detectorType = faceDetector, int featureType = Hulk);
    ~Hulkinizer();
    Mat run(Mat image);
    float classifySVM(Mat image);
};
} // namespace
#endif // HULKINIZER_H
