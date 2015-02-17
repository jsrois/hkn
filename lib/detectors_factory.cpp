#include "hulkinizer.h"
#include "delegates.h"
#include "face_detector.h"
#include "head_and_shoulder_detector.h"

namespace hulkinizer
{

Detector * Detector::create(int detectorType)
{
    switch (detectorType)
    {
    case Hulkinizer::faceDetector:
    {
        return new FaceDetector;
    }
    case Hulkinizer::headAndShoulderDetector:
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
