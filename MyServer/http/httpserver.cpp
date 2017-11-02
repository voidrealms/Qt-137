#include "httpserver.h"

HttpServer::HttpServer(QObject *parent) : TcpServer(parent)
{
    m_root = QCoreApplication::applicationDirPath();
    m_rate = 15360;
}

HttpServer::~HttpServer()
{

}

QString HttpServer::root()
{
    return m_root;
}

void HttpServer::setRoot(QString path)
{
    m_root = path;
    if(m_root.endsWith("/") || m_root.endsWith("\\"))
    {
        m_root = m_root.mid(0, m_root.length() - 1);
    }
    qDebug() << this << "root set to:" << m_root;
}

int HttpServer::rate()
{
    return m_rate;
}

void HttpServer::setRate(int value)
{
    m_rate = value;
    qDebug() << this << "rate set to:" << value;
}

void HttpServer::incomingConnection(qintptr descriptor)
{
    qDebug() << this << "Incomming HTTP connection: " << descriptor;

    HttpConnection *connection = new HttpConnection();
    connection->setRate(m_rate);
    connection->setRoot(m_root);
    accept(descriptor,connection);
}

