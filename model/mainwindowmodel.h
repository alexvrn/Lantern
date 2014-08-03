#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QString>
#include <QColor>
#include "model/package.h"

class MainWindowModel
{
public:
    enum Command {
        ON = 0x12,
        OFF = 0x13,
        COLOR = 0x20
    };

    MainWindowModel();

    QColor color() const;

    void setPackage(const Package&);

private:
    QColor colorFromBytes(const QByteArray&) const;

private:
    QColor colorOfLantern;
};

#endif // MAINWINDOWMODEL_H
