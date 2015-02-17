#ifndef QTEST_HELPERS_HPP
#define QTEST_HELPERS_HPP

/**
  This is a collection of helper macros for doing TDD with QTestLib,
  it should save you some time if you work with opencv matrix comparison
  // Assumes:
    #include <QTest>
    #include <opencv2/opencv.hpp>
    using namespace cv;
*/

#define CheckMatrixSize(A,S) \
    do{ \
    QVERIFY2(A.cols == S.width && A.rows == S.height, \
    QString("Element dimensions are not correct. A is %1 x %2 and should be %3 x %4") \
    .arg(QString::number(A.rows)) \
    .arg(QString::number(A.cols)) \
    .arg(QString::number(S.height)) \
    .arg(QString::number(S.width)) \
    .toStdString().c_str()); \
    } while (0)

#define Useful_CVTypes_Translation "(CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6)"

#define CheckMatrixType(A,T) \
    do { \
    QVERIFY2(A.type()==T, \
    QString("\nmatrix type does not match "#T", matrix is %1-channel, depth = %2 "Useful_CVTypes_Translation) \
    .arg(A.channels()) \
    .arg(A.depth()) \
    .toStdString().c_str()); \
    } while (0)


#define CheckMatricesHaveSameType(A,B) \
    do { \
    QVERIFY2(A.type()==B.type(), \
    QString("\nmatrices have different type! \n" #A" is %1-channel, depth = %2 and \n" #B" is %3-channel, depth = %4 \n"Useful_CVTypes_Translation) \
    .arg(A.channels()) \
    .arg(A.depth()) \
    .arg(B.channels()) \
    .arg(B.depth()) \
    .toStdString().c_str()); \
    } while (0)


#define CheckMatricesAreEqualSized(A,B) \
    do { \
    QVERIFY2(A.data,"first element is empty"); \
    QVERIFY2(B.data,"second element is empty"); \
    QVERIFY2(A.cols == B.cols && A.rows == B.rows, \
    QString("\ndimensions between matrices do not match." #A" is %1 x %2 and " #B" is %3 x %4") \
    .arg(QString::number(A.rows)) \
    .arg(QString::number(A.cols)) \
    .arg(QString::number(B.rows)) \
    .arg(QString::number(B.cols)) \
    .toStdString().c_str()); \
    } while (0)

#define CheckMatricesAreEqual_msg(A, B, msg) \
    do { \
    CheckMatricesAreEqualSized(A,B); \
    CheckMatricesHaveSameType(A,B); \
    Mat __diffMatrix__ = (A-B).mul(A-B); \
    double __diff__ = cv::sum(__diffMatrix__).val[0]/A.total(); \
    bool __diffcond__ = (__diff__<1e-10); \
    if (!__diffcond__) {\
        QString __diffImageName__= QString("diffImage_%1_%2.jpg")\
        .arg(#A).arg(#B); \
        normalize(__diffMatrix__,__diffMatrix__,0,255,NORM_MINMAX); \
        __diffMatrix__.convertTo(__diffMatrix__,CV_8U); \
        imwrite(__diffImageName__.toStdString(),__diffMatrix__); \
        QWARN(QString("Storing image difference at %1").arg(__diffImageName__).toStdString().c_str());\
    }\
    QVERIFY2(__diffcond__,QString("\nElements "#A" and "#B " are different: diff is %1. %2") \
    .arg(QString::number(__diff__)) \
    .arg(msg) \
    .toStdString().c_str()); \
    } while (0)

#define CheckMatricesAreEqual(A,B) CheckMatricesAreEqual_msg(A,B,"")

// Lazyness stuff
#define BeginExceptionGuards try{
#define EndExceptionGuards }catch(...){QFAIL("Exception Caught");}





#endif // QTEST_HELPERS_HPP
