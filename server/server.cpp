#include "server.h"

Server::Server()
{
    if (this->listen(QHostAddress::Any, 2323))
    {
        qDebug() << "Server started on port 2323";
    }
    else
    {
        qDebug() << "Server failed to start";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, [this, socket, socketDescriptor]() {
        qDebug() << "Client disconnected" << socketDescriptor;
        Sockets.removeOne(socket);
        socket->deleteLater();
    });

    Sockets.push_back(socket);
    qDebug() << "Client connected:" << socketDescriptor;
}

void Server::slotReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
    {
        qDebug() << "Socket cast error";
        return;
    }

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_14);

    if (in.status() == QDataStream::Ok)
    {
        qDebug() << "Reading data...";
        QString str;
        in >> str;
        qDebug() << "Received:" << str;
        SendToClient(socket, str);


    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::SendToClient(QTcpSocket *socket, const QString &str)
{
    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);
    out << str;
    socket->write(Data);
}
