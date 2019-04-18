#include "yastereocam.h"
#include <QDebug>

#include <opencv2/opencv.hpp>

YaStereoCam::YaStereoCam(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    _capL = new cv::VideoCapture(0);
    _capL->set(cv::CAP_PROP_FRAME_WIDTH, 320);
    _capL->set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    if(!_capL->isOpened()){
        qErrnoWarning("CV Camera capture error");
    } else {
        _imgInL = new cv::Mat(320,240,CV_8UC3);
    }
//    cv::VideoCapture    *_capR;
//    cv::Mat             *_imgInR;
}

YaStereoCam::~YaStereoCam()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaStereoCam::getImage()
{
    qInfo() << __PRETTY_FUNCTION__;
    *_capL >> *_imgInL;
    cv::imwrite("imgInL.jpg",*_imgInL); //test write
}
