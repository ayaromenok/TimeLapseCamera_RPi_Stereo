#ifndef YAIPOCANNY_H
#define YAIPOCANNY_H

#include "yaimgprocop.h"

#include <opencv2/core/base.hpp>

class YaIpoCanny : public YaImgProcOp
{
public:
    YaIpoCanny();
    ~YaIpoCanny();

public slots:
   void process(cv::Mat &imgL, cv::Mat &imgR, cv::Mat &imgOutL, cv::Mat &imgOutR);

private:

};

#endif // YAIPOCANNY_H
