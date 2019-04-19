#ifndef YAIMAGEPROCESS_H
#define YAIMAGEPROCESS_H

#include <QObject>

class YaImageProcess : public QObject
{
    Q_OBJECT
public:
    explicit YaImageProcess(QObject *parent = nullptr);
    ~YaImageProcess();

signals:

public slots:
};

#endif // YAIMAGEPROCESS_H
