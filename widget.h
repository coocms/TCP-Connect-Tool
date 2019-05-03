#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QMessageBox>
#include <QThread>
namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnConnect_clicked();

    void on_btnSend_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *clientfd;
    bool BConnected = false;
};


#endif // WIDGET_H
