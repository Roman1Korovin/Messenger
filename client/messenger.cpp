#include "messenger.h"
#include "ui_messenger.h"
#include "textEdit.h"
#include "QMessageBox"
#include "authorization.h"


Messenger::Messenger(const User& user, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::messenger),
    nextBlockSize(0),
    currentUser(user)

{
    ui->setupUi(this);

    ui->userButton->setText(currentUser.getUsername());
    ui->stackedWidget->setCurrentIndex(1);

    ui->usernameLabel->setText(ui->usernameLabel->text() + "\n"+currentUser.getUsername());
    ui->loginLabel->setText(ui->loginLabel->text() + "\n"+currentUser.getLogin());
    ui->passwordLabel->setText(ui->passwordLabel->text() + "\n"+currentUser.getPassword());



    //замена элемента textEdit

    ui->sendButton->setEnabled(false);
    ui->textEdit->setFocus();

    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 2323);

    // Подключение сигнала успешного подключения
        connect(socket, &QTcpSocket::connected, this, []() {
            qDebug() << "Connected to server";  // Сообщение об успешном подключении
        });

    connect(socket, &QTcpSocket::readyRead, this, &Messenger::slotReadyRead);

    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, [=](QAbstractSocket::SocketError socketError) {
        qDebug() << "Socket error occurred:" << socketError;

        if (socketError == QAbstractSocket::RemoteHostClosedError) {
            QMessageBox::critical(this, "Ошибка", "Соединение с сервером потеряно.");
            qDebug() << "Server closed the connection.";
            QApplication::quit();
        } else {
            qDebug() << "Network error or client-side issue.";
            QMessageBox::critical(this, "Ошибка", "Соединение с сервером потеряно.");
            QApplication::quit();
        }



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
            // Считываем тип сообщения
                        QString messageType;
                        in >> messageType;

                        if (messageType == "message") {
                            // Обработка текстовых сообщений
                            QString timeStr, str;
                            in >> timeStr >> str;
                            ui->textBrowser->append(timeStr + "  " + str);

                        } else if (messageType == "clientList") {
                            processServerMessage(in);
                        }

                        nextBlockSize = 0;
                        break;
                    }
                }
                else
                {
                    ui->textBrowser->append("DataStream error");
                }
            }

void Messenger::processServerMessage(QDataStream &in) {


        QStringList clientList;
        in >> clientList;

         qDebug() << QString::number(socket->socketDescriptor());

        // Удаляем текущего клиента из списка
        clientList.removeAll(QString::number(socket->socketDescriptor()));



        // Обновляем listView

        ui->listWidget->clear();
        ui->listWidget->addItems(clientList);


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



void Messenger::on_userButton_clicked()
{
    if(ui->stackedWidget->currentIndex()==0)
        ui->stackedWidget->setCurrentIndex(1);
    else
        ui->stackedWidget->setCurrentIndex(0);
}

void Messenger::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow();
    w->show();
    this->close();

}
