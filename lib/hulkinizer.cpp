#include "hulkinizer.h"
#include <iostream>
#include "nulldefs.h"
#include "mysqldatabase.hpp"
#include "delegates.h"
using namespace std;

#define THRESHOLD 0.5

namespace hulkinizer
{
Hulkinizer::Hulkinizer(int detectorType, int featureType)
{
    _detector = Detector::create(detectorType);
    _detector->init();

    _featExtraction = FeatureExtractor::create(featureType);
}

Hulkinizer::~Hulkinizer()
{

}

Mat Hulkinizer::run(Mat image)
{
    _detector->run(image,_detectionVector);

    Mat processedImage;

    _featExtraction->run(image,_detectionVector,processedImage);

    classifySVM(processedImage);

    addDetections(processedImage);

    return processedImage;
}

void Hulkinizer::addDetections(Mat &im)
{
    for (int i=0;i<_detectionVector.size();i++)
        rectangle(im,_detectionVector[i],CV_RGB(255,0,0));
}

float Hulkinizer::classifySVM(Mat image)
{
    float returnedValue = 0;
    for (int i=0;i<_detectionVector.size();i++)
    {
      doStuffWithImage(image(_detectionVector[i]));
      /*fake score*/
      RNG rng;
      returnedValue = (float) rng.gaussian(0.05)+0.5;
    }
    return returnedValue;
}

} // namespace
