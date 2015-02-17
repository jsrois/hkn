#ifndef MYSQLDATABASE_HPP
#define MYSQLDATABASE_HPP
#include <opencv2/opencv.hpp>
#include "nulldefs.h"

class MySQLDatabase
{
public:
    static void addImageToDatabase(cv::Mat&)
    {
        QUERY("FROM * SELECT broza WHERE blabla");
        ANOTHER_QUERY("INSERT WHERE BLABLA THIS IS A MYSQL STATEMENT")
    }
};


#endif // MYSQLDATABASE_HPP
