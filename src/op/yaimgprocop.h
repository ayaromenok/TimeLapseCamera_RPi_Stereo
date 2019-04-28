#ifndef YAIMGPROCOP_H
#define YAIMGPROCOP_H

#include <QObject>
#include <opencv2/core/base.hpp>

class YaImgProcOp : public QObject
{
    Q_OBJECT
public:
    explicit YaImgProcOp(QObject *parent = nullptr);
    ~YaImgProcOp();

signals:

public slots:
    virtual void process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR);
};

#endif // YAIMGPROCOP_H
