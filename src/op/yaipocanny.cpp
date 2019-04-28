#include "yaipocanny.h"

#include <QDebug>

#include <opencv2/opencv.hpp>

YaIpoCanny::YaIpoCanny(YaImgProcOp *parent) : YaImgProcOp(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setObjectName("Canny filter L/R");
}

YaIpoCanny::~YaIpoCanny()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaIpoCanny::process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR)
{
    qInfo() << this->objectName() << "process()";
    cv::Mat grayL, grayR;
    //params
    double   lowThresholdL  = 400;
    double   ratioL         = 2.5;
    int      kernelSizeL    = 5;

    double   lowThresholdR  = 400;
    double   ratioR         = 2.5;
    int      kernelSizeR    = 5;



    if (_p.contains("kernelSizeL")) {
        kernelSizeL = _p.value("kernelSizeL").toInt();
    }
    if (_p.contains("kernelSizeR")) {
        kernelSizeR = _p.value("kernelSizeR").toInt();
    }

    cv::cvtColor(imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::Canny(grayL, imgOutL, lowThresholdL, lowThresholdL*ratioL, kernelSizeL);

    cv::cvtColor(imgR, grayR, cv::COLOR_BGR2GRAY);
    cv::Canny(grayR, imgOutR, lowThresholdR, lowThresholdR*ratioR, kernelSizeR);
}
