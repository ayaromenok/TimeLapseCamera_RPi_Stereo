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
    enum OPERATION{
        NO_OPS       = 0x0000,
        NO_OPS__TEST = 0x0001,
        NO_OPS__CAM = 0x0002
    };
    Q_OBJECT
public:
    explicit YaImageProcess(QObject *parent = nullptr);
    ~YaImageProcess();

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
