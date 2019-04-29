#include "yaipochessboard.h"

#include <QDebug>
#include <QtWidgets>

#include <opencv2/opencv.hpp>

YaIpoChessBoard::YaIpoChessBoard(YaImgProcOp *parent) : YaImgProcOp(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setObjectName("Chess Board detection L/R");
    setupUI();
}

YaIpoChessBoard::~YaIpoChessBoard()
{
    qInfo() << __PRETTY_FUNCTION__;
}
void
YaIpoChessBoard::process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR)
{
    qInfo() << this->objectName() << "process()";
    cv::Mat grayL, grayR;
    cv::Mat outPointsL, outPointsR;
    int sizeXL = 4;
    int sizeYL = 6;
    int sizeXR = 4;
    int sizeYR = 6;

    if (_p.contains("sizeXL")) { sizeXL = _p.value("sizeXL").toInt();}
    if (_p.contains("sizeYL")) { sizeYL = _p.value("sizeYL").toInt();}
    if (_p.contains("sizeXR")) { sizeXR = _p.value("sizeXR").toInt();}
    if (_p.contains("sizeYR")) { sizeYR = _p.value("sizeYR").toInt();}

    cv::cvtColor(imgL, grayL, cv::COLOR_BGR2GRAY);
    cv::cvtColor(imgR, grayR, cv::COLOR_BGR2GRAY);

    cv::cvtColor(imgL, imgOutL, cv::COLOR_BGR2RGB);
    cv::cvtColor(imgR, imgOutR, cv::COLOR_BGR2RGB);

    if (cv::findChessboardCorners(imgL, cv::Size(sizeXL, sizeYL), outPointsL))
    {
        cv::drawChessboardCorners(imgOutL, cv::Size(sizeXL, sizeYL), outPointsL, true);
    } else {
        qInfo() << "img/L: can't find check board";
    }

    if (cv::findChessboardCorners(imgR, cv::Size(sizeXR, sizeYR), outPointsR))
    {
        cv::drawChessboardCorners(imgOutR, cv::Size(sizeXR, sizeYR), outPointsR, true);
    } else {
        qInfo() << "img/R: can't find check board";
    }
}


void
YaIpoChessBoard::setupUI()
{
    _wdgCtrl = new QWidget;
    QHBoxLayout *lout = new QHBoxLayout();
    QGroupBox *gbLeft = new QGroupBox("Left image");
    QGroupBox *gbRight = new QGroupBox("Right image");

    QGridLayout *loutLeft = new QGridLayout();
    QLabel  *lbLeft0 = new QLabel("X corners:");
    QLineEdit *leLeft0 = new QLineEdit("4");
    QLabel  *lbLeft1 = new QLabel("Y corners:");
    QLineEdit *leLeft1 = new QLineEdit("6");
    loutLeft->addWidget(lbLeft0,0,0);
    loutLeft->addWidget(leLeft0,0,1);
    loutLeft->addWidget(lbLeft1,1,0);
    loutLeft->addWidget(leLeft1,1,1);
    loutLeft->setRowStretch(2,10);
    gbLeft->setLayout(loutLeft);

    QGridLayout *loutRight = new QGridLayout();
    QLabel  *lbRight0 = new QLabel("X corners:");
    QLineEdit *leRight0 = new QLineEdit("4");
    QLabel  *lbRight1 = new QLabel("Y corners:");
    QLineEdit *leRight1 = new QLineEdit("6");
    loutRight->addWidget(lbRight0,0,0);
    loutRight->addWidget(leRight0,0,1);
    loutRight->addWidget(lbRight1,1,0);
    loutRight->addWidget(leRight1,1,1);
    loutRight->setRowStretch(2,10);
    gbRight->setLayout(loutRight);

    lout->addWidget(gbLeft);
    lout->addWidget(gbRight);
    _wdgCtrl->setLayout(lout);
}



