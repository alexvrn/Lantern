#ifndef PACKAGE_H
#define PACKAGE_H

#include <QByteArray>

struct Package {
    qint8 type;
    QByteArray buffer;
};

#endif // PACKAGE_H
