#include "networkmanager.h"
#include "messenger.h"
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent),
      nextBlockSize(0)
{
    socket = new QTcpSocket(this);


    connect(socket, &QTcpSocket::connected, this, []() {
        qDebug() << "Connected to server";
    });

    connect(socket, &QTcpSocket::readyRead, this, &NetworkManager::slotReadyRead);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &NetworkManager::slotErrorOccurred);
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
            QVariant senderLoginVariant, timeStrVariant, messageStrVariant, isMyselfMessageVariant;

            in >> senderLoginVariant >> timeStrVariant >> messageStrVariant >> isMyselfMessageVariant;

            QString senderLogin = senderLoginVariant.toString();
            QString timeStr = timeStrVariant.toString();
            QString messageStr = messageStrVariant.toString();
            bool isMyselfMessage = isMyselfMessageVariant.toBool();

            emit signalMessageReceived(senderLogin,  timeStr,messageStr, isMyselfMessage);
        }
        else if (messageType == "clientList")
        {

            QVariantList users;

            while (!in.atEnd()) {

                QVariant user;

                in >> user;

                users.append(user);
            }

            emit signalClientListUpdated(users);
        }
        else if (messageType == "authSuccess")
        {
            QVariantList userParams;

            QVariant usernameVariant, loginVariant, passwordVariant;
            in >> usernameVariant >> loginVariant >> passwordVariant;

            userParams << usernameVariant << loginVariant << passwordVariant;

            emit signalAuthComplete(userParams);
        }

        else if (messageType == "authError")
        {
            QVariant typeErrorVariant;

            in >> typeErrorVariant;

            QString typeError = typeErrorVariant.toString();

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
        else
        {
            qDebug() << "Unknown messageType received:" << messageType;
        }
        nextBlockSize = 0;
        break;
    }
}


void NetworkManager::slotSendToServer(const QString& messageType, const QVariantList& parameters)
{

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);


    out << quint16(0) << messageType;

    for (const QVariant &param : parameters) {

        out << param;
    }

    out.device()->seek(0);
    out<<quint16(data.size()-sizeof(quint16));

    qint64 bytesWritten = socket->write(data);
    if (bytesWritten == -1)
    {
        qDebug() << "Failed to write data to server";
    } else
    {
        qDebug() << "Sent" << bytesWritten << "bytes to server";
    }
}
