#include "yaimgprocop.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>

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

void
YaImgProcOp::dumpParamsToCon()
{
    QMapIterator<QString, QVariant> i(_p);
    while (i.hasNext()) {
        i.next();
        qInfo() << i.key() << ": " << i.value();
    }
}

void
YaImgProcOp::setCtrlIpoUI(QGroupBox &gb)
{
    qInfo() << __PRETTY_FUNCTION__;

    gb.setTitle("Ctrl/YaImgProcOp");
//QStackedWidget/QStackedLayout or use QTabWidget
}
