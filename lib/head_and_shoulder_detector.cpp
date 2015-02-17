#include "head_and_shoulder_detector.h"

HeadAndShoulderDetector::HeadAndShoulderDetector()
{
    _classifier = new CascadeClassifier;
}

HeadAndShoulderDetector::~HeadAndShoulderDetector()
{
    delete _classifier;
}

void HeadAndShoulderDetector::init()
{
    _classifier->load("data/haarcascade_mcs_upperbody.xml");
}

void HeadAndShoulderDetector::run(const Mat &image, vector<Rect> &detections)
{
    Size minimumSize = Size(80,80);
    Size maximumSize = Size(200,200);
    _classifier->detectMultiScale(image,detections,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, minimumSize, maximumSize);
}

