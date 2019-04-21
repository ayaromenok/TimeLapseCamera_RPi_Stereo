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
