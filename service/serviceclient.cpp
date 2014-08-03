#include "serviceclient.h"
#include "model/package.h"

#include <QDebug>
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>
#include <QDir>

#include <iostream>
#include <sstream>
#include <string>

#include <QtEndian>
#include <QSharedPointer>
#include <QSettings>

ServiceClient::ServiceClient(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(disconnected()), this, SLOT(sltDisconnected()));

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(reportError(QAbstractSocket::SocketError)), Qt::DirectConnection);

    connect(socket, SIGNAL(readyRead()),
        this, SLOT(readFromSocket()), Qt::DirectConnection);
}

ServiceClient::~ServiceClient()
{
    closeConnect();
    delete socket;
}

void ServiceClient::nullInit()
{
    flagForWaitBytes = WaitType;
    tmpLength = 0;
}

bool ServiceClient::openConnect(QString host, quint16 port)
{
    nullInit();

    socket->abort();
    socket->connectToHost(host, port);
    if (socket->waitForConnected(10000))
    {
        qDebug() << "Connected!";
        return true;
    }
    else
        return false;
}

void ServiceClient::closeConnect()
{
    socket->disconnectFromHost();
    if (socket->state() == QAbstractSocket::UnconnectedState || socket->waitForDisconnected(1000))
        qDebug() << "Disconnected!";

    nullInit();
}

void ServiceClient::sltDisconnected()
{
    nullInit();
}

void ServiceClient::reportError(QAbstractSocket::SocketError ErrCode)
{
    qDebug() << "SOCKET ERROR=" << ErrCode;
}

void ServiceClient::readFromSocket()
{
    try
    {
        QDataStream in(socket);

        if (flagForWaitBytes == WaitType)
        {
            //wait type
            if (socket->bytesAvailable() < (qint64)sizeof(char))
                return;

            in >> tmpType;
            #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
                tmpType = qFromBigEndian(tmpType);
            #endif

            flagForWaitBytes = WaitLength;
        }
        if (flagForWaitBytes == WaitLength)
        {
            //wait length
            if (socket->bytesAvailable() < (qint64)sizeof(quint16))
                return;

            in >> tmpLength;
            #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
                tmpType = qFromBigEndian(tmpType);
            #endif

            flagForWaitBytes = WaitValue;
        }

        if(flagForWaitBytes == WaitValue)
        {
            if(tmpLength == 0)
            {
                Package pkg{tmpType};
                emit data(pkg);
                nullInit();
            }
            else
            {
                if (socket->bytesAvailable() < tmpLength)
                    return;
                else
                {
                    char* buff = new char[tmpLength];
                    #if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
                        for(int c = 0; c < tmpLength; c++)
                            c = qFromBigEndian(c);
                    #endif
                    in.readRawData(buff, tmpLength);
                    Package pkg;
                    pkg.type = tmpType;
                    pkg.buffer.append(buff);
                    delete[] buff;

                    emit data(pkg);
                    nullInit();
                }
            }
        }
    }
    catch(...)
    {
        qDebug() << "Error: read socket!";
    }
}
