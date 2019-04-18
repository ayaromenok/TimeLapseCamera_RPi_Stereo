// Copyright(C) 2019 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License
// https://raw.githubusercontent.com/ayaromenok/TimeLapseCamera_Stereo/master/LICENSE

#include <QApplication>
#include <QDebug>
#include "yastereowidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInfo() << "TimeLapse Camera for Stereo";
    YaStereoWidget sw;

    sw.show();

    return a.exec();
}
