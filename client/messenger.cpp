#include "messenger.h"
#include "ui_messenger.h"


Messenger::Messenger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messenger)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    ui->sendButton->setEnabled(false);

    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 2323);

    connect(socket, &QTcpSocket::readyRead, this, &Messenger::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server";
    });
}

Messenger::~Messenger()
{
    delete ui;
}

void Messenger::SendToServer(const QString &str)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    out << str;

    qint64 bytesWritten = socket->write(data);
    if (bytesWritten == -1) {
        qDebug() << "Failed to write data to server";
    } else {
        qDebug() << "Sent" << bytesWritten << "bytes to server";
    }

    ui->lineEdit->clear();
}

void Messenger::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_14);

    if (in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        ui->textBrowser->append(str);
    }
    else
    {
        ui->textBrowser->append("DataStream error");
    }
}

void Messenger::on_sendButton_clicked()
{
    SendToServer(ui->lineEdit->text());
    ui->lineEdit->setFocus();
}

void Messenger::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}

void Messenger::on_lineEdit_textChanged(const QString &text)
{
    if(text=="")
    {
        ui->sendButton->setEnabled(false);
    }
    else
    {
       ui->sendButton->setEnabled(true);
    }
}
