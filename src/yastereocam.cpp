#include "yastereocam.h"
#include <QDebug>

YaStereoCam::YaStereoCam(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
}

YaStereoCam::~YaStereoCam()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaStereoCam::getImage()
{
    qInfo() << __PRETTY_FUNCTION__;
}
