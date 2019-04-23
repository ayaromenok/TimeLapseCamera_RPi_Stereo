#include "yastereowidget.h"

#include <QDebug>
#include <QtWidgets>

#include "yastereocam.h"
#include "yaimageprocess.h"

YaStereoWidget::YaStereoWidget(QWidget *parent) : QWidget(parent)
{
    qInfo() << __PRETTY_FUNCTION__;
    setWindowSize();
    setUI();
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    _timer->start(2000); //test time: 2 sec

    _imp = new YaImageProcess(this);

    connect(_timer, SIGNAL(timeout()), _imp, SLOT(getImages()));
    connect(_imp, SIGNAL(imageLReady()), this, SLOT(getImageL()));
    connect(_imp, SIGNAL(imageRReady()), this, SLOT(getImageR()));
}

YaStereoWidget::~YaStereoWidget()
{
    qInfo() << __PRETTY_FUNCTION__;
    _timer->stop();
}

void
YaStereoWidget::getImageL()
{
    qInfo() << __PRETTY_FUNCTION__;
    QImage imgL;
    _imp->getImageL(imgL);
    _lbImgL->setPixmap(QPixmap::fromImage(imgL).scaled(this->width()/3,this->width()/4));
}

void
YaStereoWidget::getImageR()
{
    qInfo() << __PRETTY_FUNCTION__;
    QImage imgR;
    _imp->getImageR(imgR);
    _lbImgR->setPixmap(QPixmap::fromImage(imgR).scaled(this->width()/3,this->width()/4));
}

void
YaStereoWidget::timerUpdate()
{
    qInfo() << "timer:" << QDateTime::currentSecsSinceEpoch();

}

void
YaStereoWidget::setWindowSize()
{
    qInfo() << __PRETTY_FUNCTION__;
#ifdef DEBUG_RPI_V7L
    this->setGeometry(QGuiApplication::primaryScreen()->geometry());
#endif //DEBUG_RPI_V7L

#ifdef DEBUG_PC
    this->setGeometry(100,100,854,480);
#endif //DEBUG_PC
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
