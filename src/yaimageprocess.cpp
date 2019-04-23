#include "yaimageprocess.h"
#include "yastereocam.h"
#include "yastereotest.h"

#include <QDebug>
#include <QImage>

#include <opencv2/opencv.hpp>

YaImageProcess::YaImageProcess(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    _cam = new YaStereoCam(this);
    _test = new YaStereoTest(this);
    op = NOPS__SRC_CAM;
    _imgL = new cv::Mat;
    _imgR = new cv::Mat;
    _imgOutL = new cv::Mat;
    _imgOutR = new cv::Mat;
}

YaImageProcess::~YaImageProcess()
{
    qInfo() << __PRETTY_FUNCTION__;
    delete _imgL;
    delete _imgR;
    delete _imgOutL;
    delete _imgOutR;
}

void
YaImageProcess::getImages()
{
    qInfo() << __PRETTY_FUNCTION__;
    if (op & NOPS__SRC_TEST){
        _test->getImages();
    } else {
        _cam->capImages();
    }
}

void
YaImageProcess::setOpImage(OPERATION operation)
{
    qInfo() << __PRETTY_FUNCTION__ << operation;
    op = operation;
}


void
YaImageProcess::getImageL(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    QImage qimg(_imgOutL->ptr(), _imgOutL->cols, _imgOutL->rows,
                _imgOutL->step, QImage::Format_RGB888);
    img = qimg;
}

void
YaImageProcess::getImageR(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    QImage qimg(_imgOutR->ptr(), _imgOutR->cols, _imgOutR->rows,
                _imgOutR->step, QImage::Format_RGB888);
    img = qimg;
}

void
YaImageProcess::process()
{
    qInfo() << __PRETTY_FUNCTION__;

    getImages();

    _cam->getImageL(*_imgL);
    _cam->getImageR(*_imgR);

    qInfo() << "imgL" << _imgL->cols << _imgL->rows
            << "imgR" << _imgR->cols << _imgR->rows;

    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(*_imgR, *_imgOutR, cv::COLOR_BGR2RGB);

    emit imageLReady();
    emit imageRReady();
}
