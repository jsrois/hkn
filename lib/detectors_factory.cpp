#include "hulkinizer.h"
#include "face_detector.h"
#include "head_and_shoulder_detector.h"

namespace hulkinizer
{

Detector * Detector::create(int detectorType)
{
    switch (detectorType)
    {
    case faceDetector:
    {
        return new FaceDetector;
    }
    case headAndShoulderDetector:
    {
        return new HeadAndShoulderDetector;
    }
    default:
    {
        // shouldn't happen
        abort();
    }

    }

}
}
