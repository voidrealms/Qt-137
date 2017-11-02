#include "test.h"

Test::Test(QObject *parent) : QObject(parent)
{

}

Test::~Test()
{

}

void Test::doTest()
{
    m_source.setFileName("/home/rootshell/Documents/a.zip");
    m_destination.setFileName("/home/rootshell/Documents/b.zip");

    m_transfer.setSource(&m_source);
    m_transfer.setDestination(&m_destination);
    m_transfer.setRate(2046);
    m_transfer.setSize(250);

    if(!m_source.open(QFile::ReadOnly))
    {
        qCritical() << "Could not open the source!";
        return;
    }
    if(!m_destination.open(QFile::WriteOnly))
    {
        qCritical() << "Could not open the destination!";
        m_source.close();
        return;
    }

    connect(&m_transfer,&RateTransfer::started, this, &Test::started);
    connect(&m_transfer,&RateTransfer::transfered, this, &Test::transfered);
    connect(&m_transfer,&RateTransfer::finished, this, &Test::finished);
    connect(&m_transfer,&RateTransfer::error, this, &Test::error);

    m_transfer.start();

}

void Test::started()
{
    qDebug() << this << "Transfer Started";
}

void Test::transfered(int bytes)
{
    qDebug() << this << "Transfered " << bytes;
}

void Test::finished()
{
    qDebug() << this << "finished";
    m_source.close();
    m_destination.close();
}

void Test::error()
{
    qDebug() << this << "error = " << m_transfer.errorString();
}

