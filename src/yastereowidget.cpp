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

    _imp = new YaImageProcess(this);

    connect(_imp, SIGNAL(imageLReady()), this, SLOT(getImageL()));
    connect(_imp, SIGNAL(imageRReady()), this, SLOT(getImageR()));

    _timer->start(5000); //test time: 5 sec
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
    _imp->getImages();
}

void
YaStereoWidget::updateSource(int source)
{
    qInfo() << "source:" << source;
    if (0 == source){
        _imp->setOpImage(YaImageProcess::NOPS__SRC_TEST);
    } else {
        _imp->setOpImage(YaImageProcess::NO_OPS__SRC_CAM);
    }
    timerUpdate();
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
    _loutCtrl = new QVBoxLayout();
    _pbCtrlQuit = new QPushButton(tr("E&xit"), this);
    connect(_pbCtrlQuit, SIGNAL(clicked()), this, SLOT(close()));    
    _loutCtrl->addWidget(_pbCtrlQuit);
    _pbCtrlProcess = new QPushButton(tr("&Process"), this);
    connect(_pbCtrlProcess, SIGNAL(clicked()), this, SLOT(timerUpdate()));
    _loutCtrl->addWidget(_pbCtrlProcess);
    _cbCtrlSource = new QComboBox();
    _cbCtrlSource->addItem("Test Source");
    _cbCtrlSource->addItem("Camera Source");
    connect(_cbCtrlSource, QOverload<int>::of(&QComboBox::activated),
          this, &YaStereoWidget::updateSource);

    _loutCtrl->addWidget(_cbCtrlSource);
    _lbCtrlImage = new QLabel("Control Image place");
    _loutCtrl->addWidget(_lbCtrlImage);
    _gbCtrl->setLayout(_loutCtrl);

    _loutMain->addWidget(_gbImgL);
    _loutMain->addWidget(_gbImgR);
    _loutMain->addWidget(_gbCtrl);

    setLayout(_loutMain);
}
