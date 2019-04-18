#ifndef YASTEREOCAM_H
#define YASTEREOCAM_H

#include <QObject>

class YaStereoCam : public QObject
{
    Q_OBJECT
public:
    explicit YaStereoCam(QObject *parent = nullptr);
    ~YaStereoCam();

signals:

public slots:
    void getImage();
private:

};

#endif // YASTEREOCAM_H
