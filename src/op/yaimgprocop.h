#ifndef YAIMGPROCOP_H
#define YAIMGPROCOP_H

#include <QObject>

class YaImgProcOp : public QObject
{
    Q_OBJECT
public:
    explicit YaImgProcOp(QObject *parent = nullptr);
    ~YaImgProcOp();

signals:

public slots:
    virtual void process();
};

#endif // YAIMGPROCOP_H
