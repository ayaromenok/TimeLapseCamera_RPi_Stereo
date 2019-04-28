#include "yaimgprocop.h"
#include <QDebug>

YaImgProcOp::YaImgProcOp(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setObjectName("YaImageProcess Operation");
}

YaImgProcOp::~YaImgProcOp()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaImgProcOp::process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR)
{
    qInfo() << objectName() << "try to implement process() in child class";
}

void
YaImgProcOp::setParams(QMap<QString, QVariant> &params)
{    
    _p = params;
    if(_p.contains("dumpParamsToCon")){
        if(_p.value("dumpParamsToCon").toBool()){
            qInfo() << objectName() << "setParams()" << params;
        }
    }
}

