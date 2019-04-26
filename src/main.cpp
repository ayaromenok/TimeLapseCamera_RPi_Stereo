// Copyright(C) 2019 Andrey Yaromenok, ayaromenok@gmail.com
// MIT License
// https://raw.githubusercontent.com/ayaromenok/TimeLapseCamera_Stereo/master/LICENSE

#include <QApplication>
#include <QDebug>
#include "yastereowidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Andrey Yaromenok");
    QApplication::setOrganizationDomain("andreyayromenok.info");
    QApplication::setApplicationName("TimeLapse Camera for Stereo");
    QApplication::setApplicationVersion("0.1.a");
    qInfo() << QApplication::applicationName() << QApplication::applicationVersion();

    YaStereoWidget sw;

    sw.show();

    return a.exec();
}
