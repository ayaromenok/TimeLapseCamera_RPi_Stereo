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
        NOPS       = 0x0000,
        NOPS__SRC_TEST = 0x0001,
        NO_OPS__SRC_CAM = 0x0002
    };

signals:
    void imageLReady();
    void imageRReady();

public slots:
    void getImages();
    void setOpImage(OPERATION operation);
    void getImageL(QImage &imgL);
    void getImageR(QImage &imgR);

private:
    YaStereoCam     *_cam;
    YaStereoTest    *_test;
    OPERATION       op;
};

#endif // YAIMAGEPROCESS_H
