#ifndef TCPCONNECTON_H
#define TCPCONNECTON_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

class TcpConnecton : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnecton(QObject *parent = 0);
    ~TcpConnecton();

    virtual void setSocket(QTcpSocket *socket);

protected:
    QTcpSocket *m_socket;
    QTcpSocket *getSocket();

signals:

public slots:
    virtual void connected();
    virtual void disconnected();
    virtual void readyRead();
    virtual void bytesWritten(qint64 bytes);
    virtual void stateChanged(QAbstractSocket::SocketState socketState);
    virtual void error(QAbstractSocket::SocketError socketError);

};

#endif // TCPCONNECTON_H
