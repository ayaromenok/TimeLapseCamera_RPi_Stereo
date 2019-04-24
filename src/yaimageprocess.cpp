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
    if (src & SRC_CAM){
        _cam->capImages();
        _cam->getImageL(*_imgL);
        _cam->getImageR(*_imgR);

    } else {
        _test->setTestImage((YaStereoTest::TEST_IMAGE) src);
        _test->getImages();
        _test->getImageL(*_imgL);
        _test->getImageR(*_imgR);
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
    case OP_NOP:{ qInfo() << "OP_NOP"; break; }
    case OP_OP1:{ op1(); break; }
    case OP_OP2:{ op2(); break; }
    case OP_OP3:{ op3(); break; }
    case OP_OP4:{ op4(); break; }
    case OP_OP5:{ op5(); break; }
    case OP_OP6:{ op6(); break; }

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
    qInfo() << __PRETTY_FUNCTION__ << "BGR 2 RGB";
    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(*_imgR, *_imgOutR, cv::COLOR_BGR2RGB);
}

void
YaImageProcess::op2()
{
    qInfo() << __PRETTY_FUNCTION__ << "BGR 2 HLS/Gray";
    cv::Mat tmpR;
    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2HLS);
    cv::cvtColor(*_imgR, tmpR, cv::COLOR_BGR2GRAY);
    cv::cvtColor(tmpR, *_imgOutR, cv::COLOR_GRAY2RGB);
}

void
YaImageProcess::op3()
{
    qInfo() << __PRETTY_FUNCTION__ << "Canny filter";
    cv::Mat grayL, grayR, cannyL, cannyR;

    cv::cvtColor(*_imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::Canny(grayL, cannyL, 400, 1000, 5);
    cv::cvtColor(cannyL, *_imgOutL, cv::COLOR_GRAY2RGB);

    cv::cvtColor(*_imgR, grayR, cv::COLOR_BGR2GRAY);
    cv::Canny(grayR, cannyR, 400, 1000, 7);
    cv::cvtColor(cannyR, *_imgOutR, cv::COLOR_GRAY2RGB);
}

void
YaImageProcess::op4()
{
    qInfo() << __PRETTY_FUNCTION__ << "Checked Board";
    cv::Mat grayL, grayR;
    cv::Mat outPointsL,outPointsR;

    cv::cvtColor(*_imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::cvtColor(*_imgR, grayR, cv::COLOR_BGR2GRAY);

    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(*_imgR, *_imgOutR, cv::COLOR_BGR2RGB);

    if (cv::findChessboardCorners(*_imgL, cv::Size(4,6), outPointsL))
    {
        cv::drawChessboardCorners(*_imgOutL, cv::Size(4,6), outPointsL, true);
    } else {
        qInfo() << "Left: can't find check board";
    }

    if (cv::findChessboardCorners(*_imgR, cv::Size(4,6), outPointsR))
    {
        cv::drawChessboardCorners(*_imgOutR, cv::Size(4,6), outPointsR, true);
    } else {
        qInfo() << "Right: can't find check board";
    }
}

void
YaImageProcess::op5()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaImageProcess::op6()
{
    qInfo() << __PRETTY_FUNCTION__;
}
