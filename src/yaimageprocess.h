#ifndef YAIMAGEPROCESS_H
#define YAIMAGEPROCESS_H

#include <QObject>
class YaStereoCam;
class YaStereoTest;
class YaImageProcess : public QObject
{
    Q_OBJECT
public:
    explicit YaImageProcess(QObject *parent = nullptr);
    ~YaImageProcess();

signals:

public slots:

private:
    YaStereoCam     *_cam;
    YaStereoTest    *_test;
};

#endif // YAIMAGEPROCESS_H
