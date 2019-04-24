#include "yastereotest.h"
#include <QDebug>
#include <QImage>

#include <opencv2/opencv.hpp>

YaStereoTest::YaStereoTest(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    _qimgInL = new QImage(":/test/imgCam13L.jpg");
    _qimgInR = new QImage(":/test/imgCam13R.jpg");
    count = 0;
}

YaStereoTest::~YaStereoTest()
{
    qInfo() << __PRETTY_FUNCTION__;
    delete _qimgInL;
    delete _qimgInR;
    qInfo() << "total # of test frames" << count;
}
void
YaStereoTest::getImages()
{
    //qInfo() << __PRETTY_FUNCTION__;
    count++;
    qInfo() << "test frame #" << count;
}

void
YaStereoTest::getImageL(QImage &img)
{
    //qInfo() << __PRETTY_FUNCTION__;
    img = _qimgInL->copy(0,0,_qimgInL->width(), _qimgInL->height());
}

void
YaStereoTest::getImageR(QImage &img)
{
    //qInfo() << __PRETTY_FUNCTION__;
    img = _qimgInR->copy(0,0,_qimgInR->width(), _qimgInR->height());
}

void
YaStereoTest::getImageL(cv::Mat &img)
{
    //qInfo() << __PRETTY_FUNCTION__;
    cv::Mat imgOut(cv::Size(_qimgInL->width(),_qimgInL->height()),
                   CV_8UC4, _qimgInL->bits());
    img = imgOut;
}

void
YaStereoTest::getImageR(cv::Mat &img)
{
    //qInfo() << __PRETTY_FUNCTION__;
    cv::Mat imgOut(cv::Size(_qimgInR->width(),_qimgInR->height()),
                   CV_8UC4, _qimgInR->bits());
    img = imgOut;
}
void
YaStereoTest::setTestImage(TEST_IMAGE img)
{
    qInfo() << __PRETTY_FUNCTION__ << img;
    if (tImg == img){
        qInfo() << "same test image as before";
        return;
    }
    tImg = img;

    delete _qimgInL;
    delete _qimgInR;

    switch (tImg) {
    case BALKONY_HSIZE:{
        _qimgInL = new QImage(":/test/imgCam13L.jpg");
        _qimgInR = new QImage(":/test/imgCam13R.jpg");
        break;
    }
    case CHK_BOARD_HSIZE:{
        _qimgInL = new QImage(":/test/imgCam13LcheckBoard.jpg");
        _qimgInR = new QImage(":/test/imgCam13RcheckBoard.jpg");
        break;
    }
    default:{
        qInfo() << "default images";
        _qimgInL = new QImage(":/test/defaultL.jpg");
        _qimgInR = new QImage(":/test/defaultR.jpg");
        break;
    }
    }

}

