#ifndef DELEGATES_H
#define DELEGATES_H

namespace hulkinizer
{
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

