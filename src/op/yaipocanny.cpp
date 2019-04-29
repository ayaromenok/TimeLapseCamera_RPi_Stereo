#include "yaipocanny.h"

#include <QDebug>
#include <QtWidgets>

#include <opencv2/opencv.hpp>

YaIpoCanny::YaIpoCanny(YaImgProcOp *parent) : YaImgProcOp(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setObjectName("Canny filter L/R");
    _wdgCtrl = new QWidget;
    QVBoxLayout *lout = new QVBoxLayout();
    QLabel  *lb0 = new QLabel("Label Canny");
    lout->addWidget(lb0);
    _wdgCtrl->setLayout(lout);
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

    double  lowThresholdL       = 400;
    double  ratioL              = 2.5;
    int     kernelSizeL         = 5;

    double  lowThresholdR       = 400;
    double  ratioR              = 2.5;
    int     kernelSizeR         = 5;


    if (_p.contains("lowThresholdL")) { lowThresholdL = _p.value("lowThresholdL").toDouble();}
    if (_p.contains("lowThresholdR")) { lowThresholdR = _p.value("lowThresholdR").toDouble();}

    if (_p.contains("ratioL")) { ratioL = _p.value("ratioL").toDouble();}
    if (_p.contains("ratioR")) { ratioR = _p.value("ratioR").toDouble();}

    if (_p.contains("kernelSizeL")) { kernelSizeL = _p.value("kernelSizeL").toInt();}
    if (_p.contains("kernelSizeR")) { kernelSizeR = _p.value("kernelSizeR").toInt();}


    cv::cvtColor(imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::Canny(grayL, imgOutL, lowThresholdL, lowThresholdL*ratioL, kernelSizeL);

    cv::cvtColor(imgR, grayR, cv::COLOR_BGR2GRAY);
    cv::Canny(grayR, imgOutR, lowThresholdR, lowThresholdR*ratioR, kernelSizeR);
}


