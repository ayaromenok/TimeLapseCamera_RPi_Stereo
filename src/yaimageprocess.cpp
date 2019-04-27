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
    srcScale = 1;
    _imgL = new cv::Mat;
    _imgR = new cv::Mat;
    _imgOutL = new cv::Mat;
    _imgOutR = new cv::Mat;
    countImgPtL = 0;
    countImgPtR = 0;
    srcTestChanged = true;
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
        if(srcTestChanged){
            _test->setTestImageSize((YaStereoTest::TEST_IMAGE_SIZE) srcScale);
            _test->setTestImage((YaStereoTest::TEST_IMAGE) src);
            srcTestChanged = false;
        }
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
YaImageProcess::setSrcImageScale(int scale)
{
    qInfo() << __PRETTY_FUNCTION__ << scale;
    srcScale = scale;
    srcTestChanged = true;
}

void
YaImageProcess::setSrcImage(SOURCE source)
{
    qInfo() << __PRETTY_FUNCTION__ << source;
    src = source;
    srcTestChanged = true;
}

void
YaImageProcess::getImageL(QImage &img)
{
    getImage(img, true);
}

void
YaImageProcess::getImageR(QImage &img)
{
//    //qInfo() << __PRETTY_FUNCTION__;
//    QImage qimg(_imgOutR->ptr(), _imgOutR->cols, _imgOutR->rows,
//                _imgOutR->step, QImage::Format_RGB888);
//    img = qimg;
    getImage(img, false);
}

void
YaImageProcess::getImage(QImage &img,bool isLeft)
{
    //qInfo() << __PRETTY_FUNCTION__;
    int imgDepth = 0;
    int imgChannel = 0;
    QImage::Format format = QImage::Format_RGB888;

    if (isLeft){
        imgDepth = _imgOutL->depth();
        imgChannel = _imgOutL->channels();
    } else {
        imgDepth = _imgOutR->depth();
        imgChannel = _imgOutR->channels();
    }

    if(0 == imgDepth){
        switch (imgChannel) {
        case(1):{
            format = QImage::Format_Grayscale8;
            break;
        }
        case(2):{
            qWarning() << "Qt don't support 2 channel image: need 1 or 3";
            return;
        }
        case(3):{
            format = QImage::Format_RGB888;
            break;
        }
        case(4):{
            format = QImage::Format_RGBA8888;
            break;
        }
        default:{
            qInfo() << "Something wrong with cv:Mat channels";
            return;
        }
        }
    } else {
        qInfo() << "cv::Mat.depth" << _imgOutL->depth();
        qInfo() << "cv::Mat with more than 8U bit/channel not supported yet";
    }

    if (isLeft){
        QImage qimg(_imgOutL->ptr(), _imgOutL->cols, _imgOutL->rows,
                    _imgOutL->step, format);
        img = qimg;
    } else {
        QImage qimg(_imgOutR->ptr(), _imgOutR->cols, _imgOutR->rows,
                    _imgOutR->step, format);
        img = qimg;
    }
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
    cv::cvtColor(*_imgR, *_imgOutR, cv::COLOR_BGR2HLS);
    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2GRAY);

}

void
YaImageProcess::op3()
{
    qInfo() << __PRETTY_FUNCTION__ << "Canny filter";
    cv::Mat grayL, grayR, cannyL, cannyR;

    cv::cvtColor(*_imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::Canny(grayL, *_imgOutL, 400, 1000, 5);

    cv::cvtColor(*_imgR, grayR, cv::COLOR_BGR2GRAY);
    cv::Canny(grayR, *_imgOutR, 400, 1000, 7);
}

void
YaImageProcess::op4()
{
    qInfo() << __PRETTY_FUNCTION__ << "Checked Board";
    cv::Mat grayL, grayR;
    cv::Mat outPointsL, outPointsR;

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
    qInfo() << __PRETTY_FUNCTION__ << "Camera Calibration";

    cv::Mat grayL, grayR;
    cv::Mat outPointsCornerL, outPointsCornerR;

    cv::cvtColor(*_imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::cvtColor(*_imgR, grayR, cv::COLOR_BGR2GRAY);

    cv::cvtColor(*_imgL, *_imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(*_imgR, *_imgOutR, cv::COLOR_BGR2RGB);

    if (cv::findChessboardCorners(*_imgL, cv::Size(4,6), outPointsCornerL))
    {
        cv::cornerSubPix(grayL, outPointsCornerL, cv::Size(7,7),
                         cv::Size(-1,-1),
                         cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 30, 0.0001));
        cv::drawChessboardCorners(*_imgOutL, cv::Size(4,6), outPointsCornerL, true);

    } else {
        qInfo() << "Left: can't find check board";
    }

    if (cv::findChessboardCorners(*_imgR, cv::Size(4,6), outPointsCornerR))
    {
        cv::drawChessboardCorners(*_imgOutR, cv::Size(4,6), outPointsCornerR, true);
    } else {
        qInfo() << "Right: can't find check board";
    }
    //std::cout << "camL" << outPointsCornerL << std::endl;
    //std::cout << "camR" << outPointsCornerR << std::endl;
}

void
YaImageProcess::op6()
{
    qInfo() << __PRETTY_FUNCTION__;
}
