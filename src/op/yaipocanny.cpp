#include "yaipocanny.h"

#include <QDebug>
#include <QtWidgets>

#include <opencv2/opencv.hpp>

YaIpoCanny::YaIpoCanny(YaImgProcOp *parent) : YaImgProcOp(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setObjectName("Canny filter L/R");
    setupUI();
}

YaIpoCanny::~YaIpoCanny()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaIpoCanny::process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR)
{
    qInfo() << this->objectName() << "process()";
    cv::Mat grayL, grayR;

    double  lowThresholdL       = 400;
    double  ratioL              = 2.5;
    int     kernelSizeL         = 5;

    double  lowThresholdR       = 400;
    double  ratioR              = 2.5;
    int     kernelSizeR         = 5;


    if (_p.contains("lowThresholdL")) { lowThresholdL = _p.value("lowThresholdL").toDouble();}
    if (_p.contains("lowThresholdR")) { lowThresholdR = _p.value("lowThresholdR").toDouble();}

    if (_p.contains("ratioL")) { ratioL = _p.value("ratioL").toDouble();}
    if (_p.contains("ratioR")) { ratioR = _p.value("ratioR").toDouble();}

    if (_p.contains("kernelSizeL")) { kernelSizeL = _p.value("kernelSizeL").toInt();}
    if (_p.contains("kernelSizeR")) { kernelSizeR = _p.value("kernelSizeR").toInt();}


    cv::cvtColor(imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::Canny(grayL, imgOutL, lowThresholdL, lowThresholdL*ratioL, kernelSizeL);

    cv::cvtColor(imgR, grayR, cv::COLOR_BGR2GRAY);
    cv::Canny(grayR, imgOutR, lowThresholdR, lowThresholdR*ratioR, kernelSizeR);
}


void
YaIpoCanny::setupUI()
{
    _wdgCtrl = new QWidget;
    QHBoxLayout *lout = new QHBoxLayout();
    QGroupBox *gbLeft = new QGroupBox("Left image");
    QGroupBox *gbRight = new QGroupBox("Right image");

    QGridLayout *loutLeft = new QGridLayout();
    QLabel  *lbLeft0 = new QLabel("low Thresholt:");
    QLineEdit *leLeft0 = new QLineEdit("400");
    QLabel  *lbLeft1 = new QLabel("ratio:");
    QLineEdit *leLeft1 = new QLineEdit("2.5");
    QLabel  *lbLeft2 = new QLabel("kernel size:");
    QLineEdit *leLeft2 = new QLineEdit("5");
    loutLeft->addWidget(lbLeft0,0,0);
    loutLeft->addWidget(leLeft0,0,1);
    loutLeft->addWidget(lbLeft1,1,0);
    loutLeft->addWidget(leLeft1,1,1);
    loutLeft->addWidget(lbLeft2,2,0);
    loutLeft->addWidget(leLeft2,2,1);
    loutLeft->setRowStretch(3,10);
    gbLeft->setLayout(loutLeft);

    QGridLayout *loutRight = new QGridLayout();
    QLabel  *lbRight0 = new QLabel("low Thresholt:");
    QLineEdit *leRight0 = new QLineEdit("400");
    QLabel  *lbRight1 = new QLabel("ratio:");
    QLineEdit *leRight1 = new QLineEdit("2.5");
    QLabel  *lbRight2 = new QLabel("kernel size:");
    QLineEdit *leRight2 = new QLineEdit("5");
    loutRight->addWidget(lbRight0,0,0);
    loutRight->addWidget(leRight0,0,1);
    loutRight->addWidget(lbRight1,1,0);
    loutRight->addWidget(leRight1,1,1);
    loutRight->addWidget(lbRight2,2,0);
    loutRight->addWidget(leRight2,2,1);
    loutRight->setRowStretch(3,10);
    gbRight->setLayout(loutRight);

    lout->addWidget(gbLeft);
    lout->addWidget(gbRight);
    _wdgCtrl->setLayout(lout);
}
