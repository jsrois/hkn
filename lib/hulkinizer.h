#ifndef HULKINIZER_H
#define HULKINIZER_H
#include <opencv2/core/core.hpp>

namespace hulkinizer
{

class Hulkinizer
{
    class PImpl;
    PImpl* _pimpl;
public:
    enum {faceDetector = 0, headAndShoulderDetector = 1};
    enum {Hulk = 0, DrManhattan = 1, HellBoy = 2, XYZfeatures = 3};

    Hulkinizer(int detectorType = faceDetector, int featureType = Hulk);
    ~Hulkinizer();
    cv::Mat run(cv::Mat image);
    float classifySVM(cv::Mat image);
};
} // namespace
#endif // HULKINIZER_H
