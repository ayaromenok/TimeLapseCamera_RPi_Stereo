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
    if (src & SRC_TEST){
        _test->getImages();
        _test->getImageL(*_imgL);
        _test->getImageR(*_imgR);
    } else {
        _cam->capImages();
        _cam->getImageL(*_imgL);
        _cam->getImageR(*_imgR);
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

    switch (op) {
    case OP_NOP:{
        qInfo() << "OP_NOP";
        break;
    }
    case OP_OP1:{
        op1();
        break;
    }
    case OP_OP2:{
        op2();
        break;
    }
    case OP_OP3:{
        qInfo() << "OP_OP3 - not implemented for now";
        break;
    }
    case OP_OP4:{
        qInfo() << "OP_OP4 - not implemented for now";
        break;
    }
    case OP_OP5:{
        qInfo() << "OP_OP5 - not implemented for now";
        break;
    }
    case OP_OP6:{
        qInfo() << "OP_OP6 - not implemented for now";
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

void
YaImageProcess::op1()
{
    qInfo() << __PRETTY_FUNCTION__;
    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(*_imgR, *_imgOutR, cv::COLOR_BGR2RGB);
}

void
YaImageProcess::op2()
{
    qInfo() << __PRETTY_FUNCTION__;
    cv::Mat tmpR;
    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2HLS);
    cv::cvtColor(*_imgR, tmpR, cv::COLOR_BGR2GRAY);
    cv::cvtColor(tmpR, *_imgOutR, cv::COLOR_GRAY2RGB);
}
