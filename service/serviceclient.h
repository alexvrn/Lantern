#ifndef SERVICECLIENT_H
#define SERVICECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QModelIndex>
#include "model/package.h"

class ServiceClient : public QObject
{
    Q_OBJECT

private:
    enum WaitState {
        WaitType,
        WaitLength,
        WaitValue
    };

public:
    explicit ServiceClient(QObject *parent = 0);
    ~ServiceClient();

    bool openConnect(QString host, quint16 port);
    void closeConnect();

private:
    void nullInit();

signals:
    void data(const Package&);

private slots:
    void sltDisconnected();
    void reportError(QAbstractSocket::SocketError ErrCode);
    void readFromSocket();

private:
    QTcpSocket *socket;

    WaitState flagForWaitBytes;

    qint8 tmpType;
    quint16 tmpLength;
};

#endif // SERVICECLIENT_H
