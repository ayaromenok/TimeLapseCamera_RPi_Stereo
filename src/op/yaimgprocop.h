#ifndef YAIMGPROCOP_H
#define YAIMGPROCOP_H

#include <QObject>
#include <QMap>
#include <QGroupBox>
#include <opencv2/core/base.hpp>
class QWidget;
class QStackedWidget;

class YaImgProcOp : public QObject
{
    Q_OBJECT
public:
    explicit YaImgProcOp(QObject *parent = nullptr);
    ~YaImgProcOp();

signals:

public slots:
    virtual void setParams(QMap<QString, QVariant> &params);
    virtual void process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR);    
    void setCtrlIpoUI(QStackedWidget &sw);
    void dumpParamsToCon();
protected:
    virtual void setupUI();
    QMap<QString, QVariant> _p;
    QWidget                *_wdgCtrl;
};

#endif // YAIMGPROCOP_H
