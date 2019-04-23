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
    op = NO_OPS__TEST;
}

YaImageProcess::~YaImageProcess()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaImageProcess::getImages()
{
    qInfo() << __PRETTY_FUNCTION__;
    if (op & NO_OPS__TEST){
        qInfo() << "get test images";
    } else {
        qInfo() << "get cam images";
    }
    emit imageLReady();
    emit imageRReady();
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
    _test->getImageL(img);
}

void
YaImageProcess::getImageR(QImage &img)
{
    qInfo() << __PRETTY_FUNCTION__;
    _test->getImageR(img);
}
