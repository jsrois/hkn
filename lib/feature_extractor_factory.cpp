#include "hulkinizer.h"

class HulkExtractor : public FeatureExtractor
{
public:
    void run(const Mat & input, vector<Rect> roiVector , Mat& output)
    {
        vector<Mat> imageChannels;
        split(input,imageChannels);
        for (int i=0;i<roiVector.size();i++)
        {
            Mat face = imageChannels[1](roiVector[i]);
            face = 2*face;
        }
        merge(imageChannels,output);
    }
};

class HellBoyExtractor : public FeatureExtractor
{
public:
    void run(const Mat & input, vector<Rect> roiVector , Mat& output)
    {
        vector<Mat> imageChannels;
        split(input,imageChannels);
        for (int i=0;i<roiVector.size();i++)
        {
            Mat face = imageChannels[2](roiVector[i]);
            face = 2*face;
        }
        merge(imageChannels,output);
    }
};

class ManhattanExtractor : public FeatureExtractor
{
public:
    void run(const Mat & input, vector<Rect> roiVector , Mat& output)
    {
        vector<Mat> imageChannels;
        split(input,imageChannels);
        for (int i=0;i<roiVector.size();i++)
        {
            Mat face = imageChannels[0](roiVector[i]);
            face = 2*face;
        }
        merge(imageChannels,output);
    }
};

class XYZExtractor : public FeatureExtractor
{
public:
    void run(const Mat & input, vector<Rect> roiVector , Mat& output)
    {
        output = input.clone();
        Mat hsvImage;
        cvtColor(input,hsvImage,CV_BGR2HSV);
        for (int i=0;i<roiVector.size();i++)
        {
            output(roiVector[i]) = 1.0*hsvImage(roiVector[i]);
        }
    }
};

FeatureExtractor * FeatureExtractor::create(int featureType)
{
    switch (featureType)
    {
    case Hulkinizer::Hulk:
    {
        return new HulkExtractor;
    }
    case Hulkinizer::HellBoy:
    {
        return new HellBoyExtractor;
    }
    case Hulkinizer::DrManhattan:
    {
        return new ManhattanExtractor;
    }
    case Hulkinizer::XYZfeatures:
    {
        return new XYZExtractor;
    }
    default:
    {
        abort();
    }

    }
}
