#include "yaimgprocop.h"
#include <QDebug>

YaImgProcOp::YaImgProcOp(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
}

YaImgProcOp::~YaImgProcOp()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaImgProcOp::process()
{
    qInfo() << __PRETTY_FUNCTION__;
}
