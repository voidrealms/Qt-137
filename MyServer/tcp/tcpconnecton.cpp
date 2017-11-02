#include "tcpconnecton.h"

TcpConnecton::TcpConnecton(QObject *parent) : QObject(parent)
{
    qDebug() << this << "Created";
}

TcpConnecton::~TcpConnecton()
{
    qDebug() << this << "Destroyed";
}

void TcpConnecton::setSocket(QTcpSocket *socket)
{
    m_socket = socket;
    connect(m_socket,&QTcpSocket::connected, this, &TcpConnecton::connected);
    connect(m_socket,&QTcpSocket::disconnected, this, &TcpConnecton::disconnected);
    connect(m_socket,&QTcpSocket::readyRead, this, &TcpConnecton::readyRead);
    connect(m_socket,&QTcpSocket::bytesWritten, this, &TcpConnecton::bytesWritten);
    connect(m_socket,&QTcpSocket::stateChanged, this, &TcpConnecton::stateChanged);
    connect(m_socket,static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),this,&TcpConnecton::error);

}

QTcpSocket *TcpConnecton::getSocket()
{
    if(!sender()) return 0;
    return static_cast<QTcpSocket*>(sender());
}

void TcpConnecton::connected()
{
    if(!sender()) return;
    qDebug() << this << " connected " << sender();
}

void TcpConnecton::disconnected()
{
    if(!sender()) return;
    qDebug() << this << " disconnected " << getSocket();
}

void TcpConnecton::readyRead()
{
    if(!sender()) return;
    qDebug() << this << " readyRead " << getSocket();
    QTcpSocket *socket = getSocket();
    if(!socket) return;
    socket->close();
}

void TcpConnecton::bytesWritten(qint64 bytes)
{
    if(!sender()) return;
    qDebug() << this << " bytesWritten " << getSocket() << " number of bytes = " << bytes;
}

void TcpConnecton::stateChanged(QAbstractSocket::SocketState socketState)
{
    if(!sender()) return;
    qDebug() << this << " stateChanged " << getSocket() << " state = " << socketState;
}

void TcpConnecton::error(QAbstractSocket::SocketError socketError)
{
    if(!sender()) return;
    qDebug() << this << " error " << getSocket() << " error = " << socketError;
}

