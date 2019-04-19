#ifndef YASTEREOCAM_H
#define YASTEREOCAM_H

#include <QObject>
class QImage;

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
    void imageLReady();

public slots:
    void capImages();
    void getImageL(QImage &img);
    void getImageR(QImage &img);
private:

    cv::VideoCapture    *_capL;
    cv::VideoCapture    *_capR;
    cv::Mat             *_imgInL;
    cv::Mat             *_imgInR;
};

#endif // YASTEREOCAM_H
