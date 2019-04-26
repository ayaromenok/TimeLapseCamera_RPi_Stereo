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
    void getImageL(cv::Mat &img);
    void getImageR(cv::Mat &img);
private:

    cv::VideoCapture    *_capL;
    cv::VideoCapture    *_capR;
    cv::Mat             *_imgInL;
    cv::Mat             *_imgInR;
    quint64             count;

    double             _camWidth;
    double             _camHeight;
    double             _camFrameCount;
    double             _camFps;
};

#endif // YASTEREOCAM_H
