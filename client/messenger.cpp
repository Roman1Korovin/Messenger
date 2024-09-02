#include "messenger.h"
#include "ui_messenger.h"
#include "textEdit.h"


Messenger::Messenger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messenger),
    nextBlockSize(0)

{
    ui->setupUi(this);

    //замена элемента textEdit

    ui->sendButton->setEnabled(false);
    ui->textEdit->setFocus();

    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 2323);

    connect(socket, &QTcpSocket::readyRead, this, &Messenger::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, []() {
        qDebug() << "Disconnected from server";
    });

    connect(ui->textEdit,&MyTextEdit::enterPressed, this, &Messenger::on_sendEnter_pressed);
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
    out << quint16(0) << QTime::currentTime()<< str;
    out.device()->seek(0);
    out<<quint16(data.size()-sizeof(quint16));

    qint64 bytesWritten = socket->write(data);
    if (bytesWritten == -1) {
        qDebug() << "Failed to write data to server";
    } else {
        qDebug() << "Sent" << bytesWritten << "bytes to server";
    }

    ui->textEdit->clear();
}

void Messenger::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_14);

    if (in.status() == QDataStream::Ok)
    {
        for (;;)
        {
            if(nextBlockSize==0)
            {
                if(socket->bytesAvailable()<2)
                {
                    break;
                }
                in>>nextBlockSize;
            }
            if(socket->bytesAvailable()<nextBlockSize)
            {
                break;
            }
            QString str;
            QString timeStr;
            in >> timeStr >> str;
            nextBlockSize=0;
            ui->textBrowser->append(timeStr + "  "+str);
            break;
        }
    }
    else
    {
        ui->textBrowser->append("DataStream error");
    }
}

void Messenger::on_sendButton_clicked()
{

      SendToServer(ui->textEdit->toPlainText());
      ui->textEdit->setFocus();
}

void Messenger::on_sendEnter_pressed()
{
    if(ui->textEdit->hasFocus())
    {
        SendToServer(ui->textEdit->toPlainText());
    }
}


void Messenger::on_textEdit_textChanged()
{
    if(ui->textEdit->toPlainText().isEmpty())
    {
        ui->sendButton->setEnabled(false);
    }
    else
    {
       ui->sendButton->setEnabled(true);
    }
}


