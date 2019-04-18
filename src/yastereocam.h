#ifndef YASTEREOCAM_H
#define YASTEREOCAM_H

#include <QObject>

namespace cv {
    class Mat;
    class VideoCapture;
}

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

    cv::VideoCapture    *_capL;
    cv::VideoCapture    *_capR;
    cv::Mat             *_imgInL;
    cv::Mat             *_imgInR;
};

#endif // YASTEREOCAM_H
