#include "yaipocanny.h"

#include <QDebug>

#include <opencv2/opencv.hpp>

YaIpoCanny::YaIpoCanny()
{
    qDebug() << __PRETTY_FUNCTION__;
    setObjectName("Canny filter L/R");
}

YaIpoCanny::~YaIpoCanny()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void
YaIpoCanny::process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR)
{
    qInfo() << this->objectName() << "process()";
    cv::Mat grayL, grayR;

    cv::cvtColor(imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::Canny(grayL, imgOutL, 400, 1000, 5);

    cv::cvtColor(imgR, grayR, cv::COLOR_BGR2GRAY);
    cv::Canny(grayR, imgOutR, 400, 1000, 7);
}
