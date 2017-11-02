#ifndef RATETRANSFER_H
#define RATETRANSFER_H

#include <QObject>
#include <QIODevice>
#include <QTimer>
#include <QTime>
#include <QDebug>

class RateTransfer : public QObject
{
    Q_OBJECT
public:
    explicit RateTransfer(QObject *parent = 0);
    ~RateTransfer();

    int rate();
    void setRate(int value);

    int size();
    void setSize(int value);

    qint64 maximum();
    void setMaximum(qint64 value);

    QIODevice *source();
    void setSource(QIODevice *device);

    QIODevice *destination();
    void setDestination(QIODevice *device);

    bool isTransfering();
    QString errorString();

protected:
    int m_rate;
    int m_size;
    bool m_transfering;
    qint64 m_maximum;
    qint64 m_transfered;
    QIODevice *m_source;
    QIODevice *m_destination;
    QTimer m_timer;
    QString m_error;
    bool m_scheduled;

    void setDefaults();
    bool checkDevices();
    bool checkTransfer();
    void scheduleTransfer();

signals:
    void started();
    void transfered(qint64 bytes);
    void finished();
    void error();

public slots:
    void start();
    void stop();

protected slots:
    void transfer();
    void readyRead();
    void bytesWritten(qint64 bytes);
};

#endif // RATETRANSFER_H
