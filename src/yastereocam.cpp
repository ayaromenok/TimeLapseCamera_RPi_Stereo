#include "yastereocam.h"
#include <QDebug>
#include <QImage>

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
YaStereoCam::capImages()
{
    qInfo() << __PRETTY_FUNCTION__;
    *_capL >> *_imgInL;
    cv::imwrite("outCvImgInL.jpg",*_imgInL); //test write
}

void
YaStereoCam::getImageL(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    QImage qimg(_imgInL->ptr(), _imgInL->cols, _imgInL->rows,
                _imgInL->step, QImage::Format_RGB888);
    img = qimg;
}

void
YaStereoCam::getImageR(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
}
