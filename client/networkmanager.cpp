#include "networkmanager.h"
#include "messenger.h"
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent), // Передаем родителя
      nextBlockSize(0)
{
    socket = new QTcpSocket(this); // Здесь 'this' будет родителем для QTcpSocket


    connect(socket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server";  // Сообщение об успешном подключении
    });

    connect(socket, &QTcpSocket::readyRead, this, &NetworkManager::slotReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
                this, &NetworkManager::slotErrorOccurred);
}

void NetworkManager::connectToServer()
{
    socket->connectToHost("127.0.0.1", 2323);

}

void NetworkManager::slotSendToServer(const QString& messageType, const QVariantList& parameters)
{

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);


        out << quint16(0) << messageType;

        if (messageType == "message") {

            QString message = parameters.value(0).toString();
            out << QTime::currentTime() << message;  // Отправка текстового сообщения с временем
           }
           // Возможны и другие типы сообщений
           else if (messageType == "login") {
               QString login = parameters.value(0).toString();
               QString password = parameters.value(1).toString();
               out << login << password;
           }
        else if(messageType == "register")
        {
            QString username = parameters.value(0).toString();
            QString login = parameters.value(1).toString();
            QString password = parameters.value(2).toString();
            out << username<<login<<password;
        }

           else {
               qDebug() << "Unknown messageType: " << messageType;
               return;
           }

        out.device()->seek(0);
        out<<quint16(data.size()-sizeof(quint16));

        qint64 bytesWritten = socket->write(data);
        if (bytesWritten == -1) {
            qDebug() << "Failed to write data to server";
        } else {
            qDebug() << "Sent" << bytesWritten << "bytes to server";
        }
}



 void NetworkManager::slotErrorOccurred(QAbstractSocket::SocketError socketError) {
            qDebug() << "Socket error occurred:" << socketError;

            QString errorMessage;

            switch (socketError) {
                        case QAbstractSocket::RemoteHostClosedError:
                            errorMessage = "Соединение с сервером потеряно (сервер закрыл соединение).";
                            break;
                        case QAbstractSocket::HostNotFoundError:
                            errorMessage = "Не удается найти сервер (проверьте адрес).";
                            break;
                        case QAbstractSocket::ConnectionRefusedError:
                            errorMessage = "Подключение отклонено (сервер недоступен).";
                            break;
                        case QAbstractSocket::NetworkError:
                            errorMessage = "Ошибка сети (проверьте интернет-соединение).";
                            break;
                        default:
                            errorMessage = "Произошла ошибка подключения к серверу.";
                            break;
                    }
            qDebug() <<errorMessage;
            emit signalErrorOccurred(errorMessage);

        }

void NetworkManager::slotReadyRead()
{

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_14);

    if (in.status() != QDataStream::Ok) {
            qDebug() << "DataStream error";
            return;
    }

    for (;;)
    {
        if (nextBlockSize == 0)
        {
            if (socket->bytesAvailable() < 2)
            {
                break;
            }
            in >> nextBlockSize;
        }
        if (socket->bytesAvailable() < nextBlockSize)

        {
            break;
        }

        QString messageType;

        in >> messageType;

        if (messageType == "message")
        {
            QString timeStr, str;
            qDebug()<< "111";
            in >> timeStr >> str;
            emit signalMessageReceived(timeStr, str);
        }
        else if (messageType == "clientList")
        {
            QStringList clientList;
            in >> clientList;

            qDebug() << "Cl:" <<clientList;

            emit signalClientListUpdated(clientList);
        }
        else if (messageType == "authSuccess")
        {
            QVariantList userParams;
            QString username, login, password;

            in >> username >> login >> password;

            userParams << username << login << password;

            emit signalAuthComplete(userParams);
        }
        else if (messageType == "authError")
        {
            QString typeError;

            in >> typeError;

            qDebug()<< typeError;

            emit signalAuthError(typeError);
        }
        else if (messageType == "regSuccess")
        {

            emit signalRegSuccess();

        }
        else if (messageType == "regError")
        {

            emit signalRegError();


        }

     else {
        qDebug() << "Unknown messageType received:" << messageType;
    }
        nextBlockSize = 0;
        break;
    }
}
