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
    enum TEST_IMAGE{
        BALKONY_HSIZE   = 0x0002,
        CHK_BOARD_HSIZE = 0x0004,
    };
    explicit YaStereoTest(QObject *parent = nullptr);
    ~YaStereoTest();

signals:

public slots:
    void setTestImage(TEST_IMAGE img);
    void getImages();
    void getImageL(QImage &img);
    void getImageR(QImage &img);
    void getImageL(cv::Mat &img);
    void getImageR(cv::Mat &img);
private:
    cv::Mat             *_imgInL;
    cv::Mat             *_imgInR;
    QImage              *_qimgInL;
    QImage              *_qimgInR;
    quint64             count;
    TEST_IMAGE          tImg;
};

#endif // YASTEREOTEST_H
