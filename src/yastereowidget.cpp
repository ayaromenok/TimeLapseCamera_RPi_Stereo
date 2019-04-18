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
    _loutImgL = new QVBoxLayout();
    _loutImgL->addWidget(_lbImgL);
    _gbImgL->setLayout(_loutImgL);

    _gbImgR = new QGroupBox(tr("Image/Right"));
    _lbImgR = new QLabel("Image/Right");
    _loutImgR = new QVBoxLayout();
    _loutImgR->addWidget(_lbImgR);
    _gbImgR->setLayout(_loutImgR);

    _gbCtrl = new QGroupBox(tr("Controls"));
    _lbCtrl = new QLabel("Controls");
    _loutCtrl = new QVBoxLayout();
    _loutCtrl->addWidget(_lbCtrl);
    _gbCtrl->setLayout(_loutCtrl);

    _loutMain->addWidget(_gbImgL);
    _loutMain->addWidget(_gbImgR);
    _loutMain->addWidget(_gbCtrl);

    setLayout(_loutMain);
}
