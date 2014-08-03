#include "mainwindowmodel.h"

MainWindowModel::MainWindowModel()
{
    colorOfLantern = QColor(0, 0, 0);
}

QColor MainWindowModel::color() const
{
    return colorOfLantern;
}

void MainWindowModel::setPackage(const Package &pkg)
{
    switch(pkg.type)
    {
        case ON:
            colorOfLantern = QColor(255, 255, 255);
            break;
        case OFF:
            colorOfLantern = QColor(0, 0, 0);
            break;
        case COLOR:
            colorOfLantern = colorFromBytes(pkg.buffer);
            break;
        default: return;
    }
}

QColor MainWindowModel::colorFromBytes(const QByteArray& array) const
{
    try
    {
        if(array.count() < 3)
            return Qt::black;
        return QColor(array[0], array[1], array[2]);
    }
    catch(...)
    {
        return Qt::black;
    }
}
