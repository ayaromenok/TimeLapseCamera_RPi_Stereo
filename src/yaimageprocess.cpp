#include "yaimageprocess.h"
#include "yastereocam.h"
#include "yastereotest.h"

#include <QDebug>
#include <QImage>

YaImageProcess::YaImageProcess(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    _cam = new YaStereoCam(this);
    _test = new YaStereoTest(this);
    op = NOPS__SRC_TEST;
}

YaImageProcess::~YaImageProcess()
{
    qInfo() << __PRETTY_FUNCTION__;
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
    qInfo() << __PRETTY_FUNCTION__;
    op = operation;
}


void
YaImageProcess::getImageL(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    if (op & NOPS__SRC_TEST){
        _test->getImageL(img);
    } else {
        _cam->getImageL(img, true);
    }
}

void
YaImageProcess::getImageR(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    if (op & NOPS__SRC_TEST){
        _test->getImageR(img);
    } else {
        _cam->getImageR(img, true);
    }
}

void
YaImageProcess::process()
{
    qInfo() << __PRETTY_FUNCTION__;
    getImages();

    emit imageLReady();
    emit imageRReady();
}
