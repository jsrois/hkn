#include <QTest>
#include <opencv2/opencv.hpp>
#include <hulkinizer.h>
#include "qtest_opencv_helpers.hpp"
using namespace std;
using namespace cv;

class hulkinizer_test : public QObject
{
    Q_OBJECT
public:
    hulkinizer_test();

private Q_SLOTS:
    void characterizationTest_data();
    void characterizationTest();
};


hulkinizer_test::hulkinizer_test()
{

}

/*
    We create this high level tests before refactoring
*/
void hulkinizer_test::characterizationTest_data()
{
    // define test variables
    QTest::addColumn<QString>("inputImageName");
    QTest::addColumn<int>("featureType");
    QTest::addColumn<QString>("groundTruthImageName");

    // add fixtures
    QTest::newRow("test1") << "data/sampleImage.png" << int(Hulkinizer::Hulk) << "data/gt_hulk.bmp";
    QTest::newRow("test2") << "data/sampleImage.png" << int(Hulkinizer::HellBoy) << "data/gt_hellboy.bmp";
    QTest::newRow("test3") << "data/sampleImage.png" << int(Hulkinizer::DrManhattan) << "data/gt_manhattan.bmp";
    QTest::newRow("test4") << "data/sampleImage.png" << int(Hulkinizer::XYZfeatures) << "data/gt_xyz.bmp";
}

   #include <QDebug>
void hulkinizer_test::characterizationTest()
{
    QFETCH(QString,inputImageName);
    QFETCH(int,featureType);
    QFETCH(QString,groundTruthImageName);

    Mat inputImage          = imread(inputImageName.toStdString().c_str());
    Mat groundTruthImage    = imread(groundTruthImageName.toStdString().c_str());

    Hulkinizer hulk(Detector::faceDetector);

    Mat result = hulk.run(inputImage,featureType);


    CheckMatricesAreEqual(result,groundTruthImage);
}

QTEST_APPLESS_MAIN(hulkinizer_test)

#include "tst_hulkinizer.moc"
