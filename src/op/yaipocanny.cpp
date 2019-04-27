#include "yaipocanny.h"
#include <QDebug>

YaIpoCanny::YaIpoCanny()
{
    qDebug() << __PRETTY_FUNCTION__;
}

YaIpoCanny::~YaIpoCanny()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void
YaIpoCanny::process()
{
    qInfo() << __PRETTY_FUNCTION__;
    qInfo() << "Canny test";
}
