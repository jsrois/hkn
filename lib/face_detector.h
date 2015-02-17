#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
#include "hulkinizer.h"

class FaceDetector : public Detector
{
    CascadeClassifier * _classifier;
public:
    FaceDetector();
    ~FaceDetector();

    void init();
    void run(const Mat &, vector<Rect> &);
};

#endif // FACEDETECTOR_H
