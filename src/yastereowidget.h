#ifndef YASTEREOWIDGET_H
#define YASTEREOWIDGET_H

#include <QWidget>
class QLayout;
class QVBoxLayout;
class QGroupBox;
class QLabel;
class QPushButton;
class QImage;

class YaStereoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YaStereoWidget(QWidget *parent = nullptr);
    ~YaStereoWidget();
signals:

public slots:

private:
    void setUI();
    QLayout         *_loutMain;
    QGroupBox           *_gbImgL;
    QVBoxLayout             *_loutImgL;
    QImage                      *_imgL;
    QLabel                      *_lbImgL;
    QGroupBox           *_gbImgR;
    QVBoxLayout             *_loutImgR;
    QImage                      *_imgR;
    QLabel                      *_lbImgR;
    QGroupBox           *_gbCtrl;
    QVBoxLayout             *_loutCtrl;
    QImage                      *_imgCtrl;
    QLabel                      *_lbCtrl;
    QPushButton                 *_pbCtrlQuit;

};

#endif // YASTEREOWIDGET_H
