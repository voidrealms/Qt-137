#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QThread>
#include "tcpconnections.h"
#include "tcpconnecton.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    ~TcpServer();

    virtual bool listen(const QHostAddress &address, quint16 port);
    virtual void close();
    virtual qint64 port();


protected:
    QThread *m_thread;
    TcpConnections *m_connections;
    virtual void incomingConnection(qintptr descriptor); //qint64, qHandle, qintptr, uint
    virtual void accept(qintptr descriptor, TcpConnecton *connection);

signals:
    void accepting(qintptr handle, TcpConnecton *connection);
    void finished();

public slots:
    void complete();
};

#endif // TCPSERVER_H
