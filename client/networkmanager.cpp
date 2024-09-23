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

void NetworkManager::slotSendToServer(QString message)
{

        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        out << quint16(0) << QTime::currentTime()<< message;
        out.device()->seek(0);
        out<<quint16(data.size()-sizeof(quint16));

        qint64 bytesWritten = socket->write(data);
        if (bytesWritten == -1) {
            qDebug() << "Failed to write data to server";
        } else {
            qDebug() << "Sent" << bytesWritten << "bytes to server";
        }
}

void NetworkManager::connectToServer()
{
    socket->connectToHost("127.0.0.1", 2323);

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

    if (in.status() == QDataStream::Ok)
    {
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
                emit messageReceived(timeStr, str);
            }
            else if (messageType == "clientList")
            {
                QStringList clientList;
                in >> clientList;

                qDebug() << "Cl:" <<clientList;

                emit clientListUpdated(clientList);


            }

            nextBlockSize = 0;
            break;
        }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}
