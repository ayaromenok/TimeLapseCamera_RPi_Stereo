#include "yastereotest.h"
#include <QDebug>
#include <QImage>

#include <opencv2/opencv.hpp>

YaStereoTest::YaStereoTest(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
}

YaStereoTest::~YaStereoTest()
{
    qInfo() << __PRETTY_FUNCTION__;
}
void
YaStereoTest::getImages()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaStereoTest::getImageL(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    img = QImage(":/test/imgCam13L.jpg");
}

void
YaStereoTest::getImageR(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    img = QImage(":/test/imgCam13R.jpg");
}

void
YaStereoTest::getImageL(cv::Mat &img)
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaStereoTest::getImageR(cv::Mat &img)
{
    qInfo() << __PRETTY_FUNCTION__;
}

