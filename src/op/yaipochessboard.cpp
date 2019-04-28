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

    cv::cvtColor(imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::cvtColor(imgR, grayR, cv::COLOR_BGR2GRAY);

    cv::cvtColor(imgL, imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(imgR, imgOutR, cv::COLOR_BGR2RGB);

    if (cv::findChessboardCorners(imgL, cv::Size(4,6), outPointsL))
    {
        cv::drawChessboardCorners(imgOutL, cv::Size(4,6), outPointsL, true);
    } else {
        qInfo() << "img/L: can't find check board";
    }

    if (cv::findChessboardCorners(imgR, cv::Size(4,6), outPointsR))
    {
        cv::drawChessboardCorners(imgOutR, cv::Size(4,6), outPointsR, true);
    } else {
        qInfo() << "img/R: can't find check board";
    }
}
