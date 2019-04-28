#include "yaipochessboard.h"

#include <QDebug>

#include <opencv2/opencv.hpp>

YaIpoChessBoard::YaIpoChessBoard(YaImgProcOp *parent) : YaImgProcOp(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setObjectName("Chess Board detection L/R");
}

YaIpoChessBoard::~YaIpoChessBoard()
{
    qInfo() << __PRETTY_FUNCTION__;
}
void
YaIpoChessBoard::process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR)
{
    qInfo() << this->objectName() << "process()";
    cv::Mat grayL, grayR;
    cv::Mat outPointsL, outPointsR;
    int sizeXL = 4;
    int sizeYL = 6;
    int sizeXR = 4;
    int sizeYR = 6;

    if (_p.contains("sizeXL")) { sizeXL = _p.value("sizeXL").toInt();}
    if (_p.contains("sizeYL")) { sizeYL = _p.value("sizeYL").toInt();}
    if (_p.contains("sizeXR")) { sizeXR = _p.value("sizeXR").toInt();}
    if (_p.contains("sizeYR")) { sizeYR = _p.value("sizeYR").toInt();}

    cv::cvtColor(imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::cvtColor(imgR, grayR, cv::COLOR_BGR2GRAY);

    cv::cvtColor(imgL, imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(imgR, imgOutR, cv::COLOR_BGR2RGB);

    if (cv::findChessboardCorners(imgL, cv::Size(sizeXL, sizeYL), outPointsL))
    {
        cv::drawChessboardCorners(imgOutL, cv::Size(sizeXL, sizeYL), outPointsL, true);
    } else {
        qInfo() << "img/L: can't find check board";
    }

    if (cv::findChessboardCorners(imgR, cv::Size(sizeXR, sizeYR), outPointsR))
    {
        cv::drawChessboardCorners(imgOutR, cv::Size(sizeXR, sizeYR), outPointsR, true);
    } else {
        qInfo() << "img/R: can't find check board";
    }
}
