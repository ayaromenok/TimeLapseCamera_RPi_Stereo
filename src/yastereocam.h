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
    void imageRReady();

public slots:
    void capImages();
    void getImageL(QImage &img, bool swapRnB = false);
    void getImageR(QImage &img, bool swapRnB = false);
private:

    cv::VideoCapture    *_capL;
    cv::VideoCapture    *_capR;
    cv::Mat             *_imgInL;
    cv::Mat             *_imgInR;
};

#endif // YASTEREOCAM_H
