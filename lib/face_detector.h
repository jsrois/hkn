#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
#include "hulkinizer.h"
#include "delegates.h"
class FaceDetector : public hulkinizer::Detector
{
    CascadeClassifier * _classifier;
public:
    FaceDetector();
    ~FaceDetector();

    void init();
    void run(const Mat &, vector<Rect> &);
};

#endif // FACEDETECTOR_H
