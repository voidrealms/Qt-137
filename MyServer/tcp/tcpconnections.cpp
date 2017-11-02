#include "tcpconnections.h"

TcpConnections::TcpConnections(QObject *parent) : QObject(parent)
{
    qDebug() << this << "created";
}

TcpConnections::~TcpConnections()
{
    qDebug() << this << "destroyed";
}

int TcpConnections::count()
{
    QReadWriteLock lock;
    lock.lockForRead();
    int value = m_connections.count();
    lock.unlock();

    return value;
}

void TcpConnections::removeSocket(QTcpSocket *socket)
{
    if(!socket) return;
    if(!m_connections.contains(socket)) return;

    qDebug() << this << "removing socket = " <<  socket;

    if(socket->isOpen())
    {
        qDebug() << this << "socket is open, attempting to close it " << socket;
        socket->disconnect();
        socket->close();
    }

    qDebug() << this << "deleting socket" << socket;
    m_connections.remove(socket);
    socket->deleteLater();

    qDebug() << this << "client count = " << m_connections.count();

}

void TcpConnections::disconnected()
{
    if(!sender()) return;
    qDebug() << this << "disconnecting socket"<< sender();

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    if(!socket) return;

    removeSocket(socket);
}

void TcpConnections::error(QAbstractSocket::SocketError socketError)
{
    if(!sender()) return;
    qDebug() << this << "error in socket" << sender() << " error = " << socketError;

    QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
    if(!socket) return;

    removeSocket(socket);
}

void TcpConnections::start()
{
    qDebug() << this << "connections started on" << QThread::currentThread();
}

void TcpConnections::quit()
{
    if(!sender()) return;
    qDebug() << this << "connections quitting";

    foreach(QTcpSocket *socket, m_connections.keys())
    {
        qDebug() << this << "closing socket" << socket;
        removeSocket(socket);
    }

    qDebug() << this << "finishing";
    emit finished();
}

void TcpConnections::accept(qintptr handle, TcpConnecton *connection)
{
    qDebug() << "*** HEY WATCH THIS";
    QTcpSocket *socket = new QTcpSocket(this);

    if(!socket->setSocketDescriptor(handle))
    {
        qWarning() << this << "could not accept connection" << handle;
        connection->deleteLater();
        return;
    }

    // connect(socket,&QTcpSocket::disconnected,this,&TcpConnections::disconnected);
    // connect(socket,static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),this,&TcpConnections::error);

    connect(socket,&QTcpSocket::disconnected, this, &TcpConnections::disconnected);
    connect(socket,static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error),this,&TcpConnections::error);

    connection->moveToThread(QThread::currentThread());
    connection->setSocket(socket);

    m_connections.insert(socket,connection);
    qDebug() << this << "clients = " << m_connections.count();
    emit socket->connected();

}

