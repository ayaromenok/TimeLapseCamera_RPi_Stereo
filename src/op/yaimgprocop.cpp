#include "yaimgprocop.h"
#include <QDebug>
#include <QtWidgets>

YaImgProcOp::YaImgProcOp(QObject *parent) : QObject(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setObjectName("YaImageProcess Operation");
    _wdgCtrl = new QWidget;
    QVBoxLayout *lout = new QVBoxLayout();
    QLabel  *lb0 = new QLabel("Label YaImgProcOp");
    lout->addWidget(lb0);
    _wdgCtrl->setLayout(lout);
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
YaImgProcOp::setCtrlIpoUI(QStackedWidget &sw)
{
    qInfo() << __PRETTY_FUNCTION__;

    qInfo() << __PRETTY_FUNCTION__;
    if(-1 == sw.indexOf(_wdgCtrl) ){
       sw.addWidget(_wdgCtrl);
    }
    sw.setCurrentWidget(_wdgCtrl);
}
