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

    enum TEST_IMAGE_SIZE{
        FULL            = 0x0001,
        HALF            = 0x0002,
        QUARTER         = 0x0004,
        DOUBLE          = 0x0008,
        W160xH120       = 0x0010,
        W320xH240       = 0x0020,
        W640xH480       = 0x0040,
        W1280xH960      = 0x0080
    };

    explicit YaStereoTest(QObject *parent = nullptr);
    ~YaStereoTest();

signals:

public slots:
    void setTestImage(TEST_IMAGE img);
    void setTestImageSize(TEST_IMAGE_SIZE size);
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
    TEST_IMAGE_SIZE     tImgSize;
    double              imgScale;
};

#endif // YASTEREOTEST_H
