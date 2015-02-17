#ifndef HEADANDSHOULDERDETECTOR_H
#define HEADANDSHOULDERDETECTOR_H
#include "hulkinizer.h"


class HeadAndShoulderDetector : public Detector
{
    CascadeClassifier *_classifier;
public:
    HeadAndShoulderDetector();
    ~HeadAndShoulderDetector();

    void init();

    void run(const Mat &, vector<Rect> &);

};

#endif // HEADANDSHOULDERDETECTOR_H
