#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("TCP Connect tool");
}

Widget::~Widget()
{
    delete ui;
    if(BConnected)
    {
        clientfd->close();
        free(clientfd);
        clientfd = NULL;
    }

    exit(0);

}

void Widget::on_btnConnect_clicked()
{
    if(BConnected == false)
    {
        if(ui->editIp->text() == "" || ui->editPort->text() == "")
        {
            QMessageBox box(QMessageBox::Warning,"TCP_CLIENT","请输入IP地址和端口号");
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString("确 定"));
            box.exec();
        }
        else
        {
            QString StrIp = ui->editIp->text();
            QString StrPort = ui->editPort->text();
            char*  ch;
            QByteArray ba = StrPort.toLatin1(); // must
            ch=ba.data();
            int port;
            sscanf(ch, "%d", &port);
            clientfd = new QTcpSocket(this);
            //连接服务器
            clientfd->connectToHost(StrIp,port);
            //等待连接成功
            if(!clientfd->waitForConnected(2000))
            {
                QMessageBox box(QMessageBox::Warning,"TCP_CLIENT","建立连接超时，请检查你的网络连接");
                box.setStandardButtons (QMessageBox::Ok);
                box.setButtonText (QMessageBox::Ok,QString("确 定"));
                box.exec();

                free(clientfd);
                clientfd = NULL;
            }
            else
            {
                BConnected = !BConnected;
                ui->btnConnect->setText("断开TCP连接");
            }
        }
    }
    else
    {
        clientfd->close();
        free(clientfd);
        clientfd = NULL;
        BConnected = !BConnected;
        ui->btnConnect->setText("建立TCP连接");
    }

}

void Widget::on_btnSend_clicked()
{
    if(BConnected)
    {
        QString context = ui->editSend->toPlainText();
        QByteArray arr = context.toLatin1();
        clientfd->write(arr);
        char buf[100] = {0};

        if(clientfd->waitForReadyRead(1000))//阻塞等待读数据，至多1秒
        {
            clientfd->read(buf, sizeof buf);
            qDebug() << buf << endl;
            ui->editReceive->setText(buf);

        }

    }
    else
    {
        QMessageBox box(QMessageBox::Warning,"TCP_CLIENT","请先连接服务器");
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("确 定"));
        box.exec();
    }
}


