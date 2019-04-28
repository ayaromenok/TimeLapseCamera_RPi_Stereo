#ifndef YAIMGPROCOP_H
#define YAIMGPROCOP_H

#include <QObject>
#include <QMap>
#include <QGroupBox>
#include <opencv2/core/base.hpp>
class QVBoxLayout;

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
    virtual void setCtrlIpoUI(QGroupBox &gb);
    void dumpParamsToCon();
protected:
    QMap<QString, QVariant> _p;
    QVBoxLayout             *_lout;
};

#endif // YAIMGPROCOP_H
