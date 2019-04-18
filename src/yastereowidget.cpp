#include "yastereowidget.h"
#include <QDebug>
#include <QtWidgets>

YaStereoWidget::YaStereoWidget(QWidget *parent) : QWidget(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    this->setGeometry(100,100,854,480);
    setUI();
}

YaStereoWidget::~YaStereoWidget()
{
    qInfo() << __PRETTY_FUNCTION__;
}

void
YaStereoWidget::setUI()
{
    qInfo() << __PRETTY_FUNCTION__;
    _loutMain = new QHBoxLayout;

    _gbImgL = new QGroupBox(tr("Image/Left"));
    _lbImgL = new QLabel("Image/Left");
    _imgL = new QImage(":/test/imgCam13L.jpg");
    _lbImgL->setPixmap(QPixmap::fromImage(*_imgL).scaled(320,240));
    _loutImgL = new QVBoxLayout();
    _loutImgL->addWidget(_lbImgL);
    _gbImgL->setLayout(_loutImgL);

    _gbImgR = new QGroupBox(tr("Image/Right"));
    _lbImgR = new QLabel("Image/Right");
    _imgR = new QImage(":/test/imgCam13R.jpg");
    _lbImgR->setPixmap(QPixmap::fromImage(*_imgR).scaled(320,240));
    _loutImgR = new QVBoxLayout();
    _loutImgR->addWidget(_lbImgR);
    _gbImgR->setLayout(_loutImgR);

    _gbCtrl = new QGroupBox(tr("Controls"));
    _lbCtrl = new QLabel("Controls");
    _pbCtrlQuit = new QPushButton(tr("E&xit"), this);
    connect(_pbCtrlQuit, SIGNAL(clicked()), this, SLOT(close()));
    _loutCtrl = new QVBoxLayout();
    _loutCtrl->addWidget(_pbCtrlQuit);
    _loutCtrl->addWidget(_lbCtrl);
    _gbCtrl->setLayout(_loutCtrl);

    _loutMain->addWidget(_gbImgL);
    _loutMain->addWidget(_gbImgR);
    _loutMain->addWidget(_gbCtrl);

    setLayout(_loutMain);
}