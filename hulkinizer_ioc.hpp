
// in Hulkinizer API:
struct Detector
{
  virtual void doDetectorStuff(Input input, Output result) = 0;
};

struct FeatureExtractor
{
    virtual void doFeatureExtractionStuff(Input input, Output result) = 0;
};

class HulkinizerLogic
{
  Detector * detector;
  FeatureExtractor * featExtractor;
public:

  HulkinizerLogic(Detector * d,FeatureExtractor * f) :
    detector(d),
    featExtractor(f)
  {

  }

  void run()
  {
    detector->doDetectorStuff(a,b);
    featExtractor->doFeatureExtractionStuff(b,c);
  }

};

// Client defines its own components

struct CustomDetector : public Detector
{
    void doDetectorStuff(Input input, Output result)
    {
        // do my custom stuff here
    }
};

struct CustomFeatureExtractor : public FeatureExtractor
{
    void doFeatureExtractionStuff(Input input, Output result)
    {
        // do my custom stuff here
    }
};

int main()
{
    HulkinizerLogic hLogic(new CustomDetector,new CustomFeatureExtractor);

    hLogic.run();
}
