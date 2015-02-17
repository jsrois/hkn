#include "face_detector.h"

FaceDetector::FaceDetector()
{
    _classifier = new CascadeClassifier;
}

FaceDetector::~FaceDetector()
{
    delete _classifier;
}

void FaceDetector::init()
{
    _classifier->load("data/haarcascade_frontalface_alt2.xml");
}

void FaceDetector::run(const Mat &image, vector<Rect> &detections)
{
    Size minimumSize = Size(30,30);
    Size maximumSize = Size(200,200);
    _classifier->detectMultiScale(image,detections,1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, minimumSize, maximumSize);
}

