#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
//#include "tcpserver.h"
#include "httpserver.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::Dialog *ui;
    //TcpServer m_server;
    HttpServer m_server;
    void setStarted(bool started);
};

#endif // DIALOG_H
