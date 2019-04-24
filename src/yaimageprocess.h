#ifndef YAIMAGEPROCESS_H
#define YAIMAGEPROCESS_H

#include <QObject>
class YaStereoCam;
class YaStereoTest;
namespace cv {
    class Mat;
    class VideoCapture;
}

class YaImageProcess : public QObject
{

    Q_OBJECT
public:
    explicit YaImageProcess(QObject *parent = nullptr);
    ~YaImageProcess();

    enum OPERATION{
        OP_OP1          = 0x0001,
        OP_OP2          = 0x0002,
        OP_OP3          = 0x0004,
        OP_OP4          = 0x0008,
        OP_OP5          = 0x0010,
        OP_OP6          = 0x0020,
        OP_NOP          = 0xF000
    };
    enum SOURCE{
        SRC_CAM  = 0x0001,
        SRC_TEST_1 = 0x0002,
        SRC_TEST_2 = 0x0004,
        SRC_TEST_3 = 0x0008,
        SRC_TEST_4 = 0x00010
    };

signals:
    void imageLReady();
    void imageRReady();

public slots:
    void getImages();
    void setOpImage(OPERATION operation);
    void setSrcImage(SOURCE source);
    void getImageL(QImage &imgL);
    void getImageR(QImage &imgR);
    void process();

private:
    void  op1();
    void  op2();
    void  op3();
    void  op4();
    void  op5();
    void  op6();

    YaStereoCam     *_cam;
    YaStereoTest    *_test;
    OPERATION       op;
    SOURCE          src;
    cv::Mat         *_imgL;
    cv::Mat         *_imgR;

    cv::Mat         *_imgOutL;
    cv::Mat         *_imgOutR;
};

#endif // YAIMAGEPROCESS_H
