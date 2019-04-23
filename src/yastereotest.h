#ifndef YASTEREOTEST_H
#define YASTEREOTEST_H

#include <QObject>
class QImage;

namespace cv {
    class Mat;
    class VideoCapture;
}

class YaStereoTest : public QObject
{
    Q_OBJECT
public:
    explicit YaStereoTest(QObject *parent = nullptr);
    ~YaStereoTest();

signals:

public slots:
    void getImages();
    void getImageL(QImage &img);
    void getImageR(QImage &img);
    void getImageL(cv::Mat &img);
    void getImageR(cv::Mat &img);
private:
    cv::Mat             *_imgInL;
    cv::Mat             *_imgInR;
};

#endif // YASTEREOTEST_H
