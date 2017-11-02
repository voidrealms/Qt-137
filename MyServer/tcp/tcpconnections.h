#ifndef TCPCONNECTIONS_H
#define TCPCONNECTIONS_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QTcpSocket>
#include <QMap>
#include <QReadWriteLock>
#include "tcpconnecton.h"


class TcpConnections : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnections(QObject *parent = 0);
    ~TcpConnections();

    virtual int count();

protected:
    QMap<QTcpSocket*, TcpConnecton*> m_connections;
    void removeSocket(QTcpSocket *socket);

signals:
    void quitting();
    void finished();

protected slots:
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);

public slots:

    void start();
    void quit();
    void accept(qintptr handle, TcpConnecton *connection);
};

#endif // TCPCONNECTIONS_H
