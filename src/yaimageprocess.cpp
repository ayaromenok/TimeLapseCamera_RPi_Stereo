#include "yaimageprocess.h"

#include <QDebug>

YaImageProcess::YaImageProcess(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
}

YaImageProcess::~YaImageProcess
{
    qInfo() << __PRETTY_FUNCTION__;
}
