#include "yastereocam.h"
#include <QDebug>
#include <QImage>
#include <QCoreApplication>

#include <opencv2/opencv.hpp>

YaStereoCam::YaStereoCam(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    _capL = new cv::VideoCapture(0);
    _capL->set(cv::CAP_PROP_FRAME_WIDTH, 320);
    _capL->set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    if(!_capL->isOpened()){
        qErrnoWarning("CV Camera/Left capture error");
    };
#ifdef DEBUG_PC
    qInfo() << "use single cam as a right source too";
#else
    _capR = new cv::VideoCapture(1);
    _capR->set(cv::CAP_PROP_FRAME_WIDTH, 320);
    _capR->set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    if(!_capR->isOpened()){
        qErrnoWarning("CV Camera/Right capture error");
    }
#endif
    _imgInL = new cv::Mat(320,240,CV_8UC3);
    _imgInR = new cv::Mat(320,240,CV_8UC3);
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
    if (_imgInL->empty()){
        qErrnoWarning("\tImage/Left is empty");
        QCoreApplication::exit(-1);
    }
#ifdef DEBUG_PC
    *_imgInR = *_imgInL;
#else
    *_capR >> *_imgInR;
    if (_imgInR->empty()){
        qErrnoWarning("\tImage/Right is empty");
        QCoreApplication::exit(-2);
    }
#endif

    //cv::imwrite("outCvImgInL.jpg",*_imgInL); //test write
    emit imageLReady();
    emit imageRReady();
}

void
YaStereoCam::getImageL(QImage &img, bool swapRnB)
{
    qInfo() << __PRETTY_FUNCTION__;
    if (swapRnB){
        cv::cvtColor(*_imgInL, *_imgInL, cv::COLOR_BGR2RGB);
    }
    QImage qimg(_imgInL->ptr(), _imgInL->cols, _imgInL->rows,
                _imgInL->step, QImage::Format_RGB888);
    img = qimg;
}

void
YaStereoCam::getImageR(QImage &img, bool swapRnB)
{
    qInfo() << __PRETTY_FUNCTION__;
#ifndef DEBUG_PC
    if (swapRnB){
        cv::cvtColor(*_imgInR, *_imgInR, cv::COLOR_BGR2RGB);
    }
#endif //DEBUG_PC
    QImage qimg(_imgInR->ptr(), _imgInR->cols, _imgInR->rows,
                _imgInR->step, QImage::Format_RGB888);
    img = qimg;
}
void
YaStereoCam::getImageL(cv::Mat &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    img = *_imgInL;
}
void
YaStereoCam::getImageR(cv::Mat &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    img = *_imgInR;
}
