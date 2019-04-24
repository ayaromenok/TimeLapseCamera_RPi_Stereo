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
    op = OP_OP1;
    src = SRC_CAM;
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
//    qInfo() << __PRETTY_FUNCTION__;
    if (op & SRC_TEST){
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
YaImageProcess::setSrcImage(SOURCE source)
{
    qInfo() << __PRETTY_FUNCTION__ << source;
    src = source;
}

void
YaImageProcess::getImageL(QImage &img)
{
    //qInfo() << __PRETTY_FUNCTION__;
    QImage qimg(_imgOutL->ptr(), _imgOutL->cols, _imgOutL->rows,
                _imgOutL->step, QImage::Format_RGB888);
    img = qimg;
}

void
YaImageProcess::getImageR(QImage &img)
{
    //qInfo() << __PRETTY_FUNCTION__;
    QImage qimg(_imgOutR->ptr(), _imgOutR->cols, _imgOutR->rows,
                _imgOutR->step, QImage::Format_RGB888);
    img = qimg;
}

void
YaImageProcess::process()
{
//    qInfo() << __PRETTY_FUNCTION__;

    getImages();

    _cam->getImageL(*_imgL);
    _cam->getImageR(*_imgR);

//    qInfo() << "imgL" << _imgL->cols << _imgL->rows
//            << "imgR" << _imgR->cols << _imgR->rows;

    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(*_imgR, *_imgOutR, cv::COLOR_BGR2RGB);

    switch (op) {
    case OP_NOP:{
        qInfo() << "OP_NOP";
        break;
    }
    case OP_OP1:{
        qInfo() << "OP_OP1";
        break;
    }
    case OP_OP2:{
        qInfo() << "OP_OP2";
        break;
    }
    case OP_OP3:{
        qInfo() << "OP_OP3";
        break;
    }
    case OP_OP4:{
        qInfo() << "OP_OP4";
        break;
    }
    case OP_OP5:{
        qInfo() << "OP_OP5";
        break;
    }
    case OP_OP6:{
        qInfo() << "OP_OP6";
        break;
    }
    default:{
        qInfo() << "Operation not implemented";
        break;
    }
    }

    emit imageLReady();
    emit imageRReady();
}
