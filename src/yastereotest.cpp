#include "yastereotest.h"
#include <QDebug>
#include <QImage>

#include <opencv2/opencv.hpp>

YaStereoTest::YaStereoTest(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    _qimgInL = new QImage(":/test/defaultL.jpg");
    _qimgInR = new QImage(":/test/defaultR.jpg");
    count = 0;
    imgScale = 1.0;
    tImg = BALKONY_HSIZE;
    tImgSize = FULL;
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
    QImage tmpL, tmpR;
//    if (tImg == img){
//        qInfo() << "same test image as before";
//        return;
//    }
    tImg = img;

    delete _qimgInL;
    delete _qimgInR;

    switch (tImg) {
    case BALKONY_HSIZE:{
        tmpL = QImage(":/test/imgCam13L.jpg");
        tmpR = QImage(":/test/imgCam13R.jpg");
        break;
    }
    case CHK_BOARD_HSIZE:{
        tmpL = QImage(":/test/imgCam13LcheckBoard.jpg");
        tmpR = QImage(":/test/imgCam13RcheckBoard.jpg");
        break;
    }
    default:{
        qInfo() << "default images";
        tmpL = QImage(":/test/defaultL.jpg");
        tmpR = QImage(":/test/defaultR.jpg");
        break;
    }
    }
    _qimgInL = new QImage(tmpL.scaledToWidth((int)tmpL.width()*imgScale, Qt::SmoothTransformation));
    _qimgInR = new QImage(tmpR.scaledToWidth((int)tmpR.width()*imgScale,Qt::SmoothTransformation));
}

 void
 YaStereoTest::setTestImageSize(TEST_IMAGE_SIZE size)
 {
    qInfo() << __PRETTY_FUNCTION__ << size;
    tImgSize = size;

    switch (size) {
    case TEST_IMAGE_SIZE::FULL:{
        imgScale = 1.0;
        break;
    }
    case TEST_IMAGE_SIZE::HALF:{
        imgScale = 0.5;
        break;
    }
    case TEST_IMAGE_SIZE::QUARTER:{
        imgScale = 0.25;
        break;
    }
    case TEST_IMAGE_SIZE::DOUBLE:{
        imgScale = 2.0;
        break;
    }
    case TEST_IMAGE_SIZE::W160xH120:{
        imgScale = (double)160.0/_qimgInL->width();
        break;
    }
    case TEST_IMAGE_SIZE::W320xH240:{
        imgScale = (double) 320.0/_qimgInL->width();
        break;
    }
    case TEST_IMAGE_SIZE::W640xH480:{
        imgScale = (double) 640.0/_qimgInL->width();
        break;
    }
    case TEST_IMAGE_SIZE::W1280xH960:{
        imgScale = (double)1280.0/_qimgInL->width();
        break;
    }
    default:{
        imgScale = 1.0;
        qWarning() << "worng place for scale";
        break;
    }
    }
    qInfo() << "test Image Scale" << imgScale;
    //setTestImage(tImg);
}
