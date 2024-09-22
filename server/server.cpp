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
    nextBlockSize=0;
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

         // После отключения клиента обновляем список
        for (QTcpSocket *clientSocket : Sockets) {
                   SendToClient(clientSocket, QString(), "clientList");
               }
    });

    Sockets.push_back(socket);
    qDebug() << "Client connected:" << socketDescriptor;

    // Отправляем текущий список клиентов всем подключенным клиентам
       for (QTcpSocket *clientSocket : Sockets) {
           SendToClient(clientSocket, QString(), "clientList");
       }
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
        for (;;)
        {
            if(nextBlockSize==0)
            {
                qDebug() << "nextBlockSize = 0";
                if(socket->bytesAvailable()<2)
                {
                    qDebug() <<"Data <2, break";
                    break;
                }
                in>>nextBlockSize;
                qDebug()<<"nextBlockSize = " << nextBlockSize;
            }
            if(socket->bytesAvailable()<nextBlockSize)
            {
                qDebug()<<"Data not full, break";
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            qDebug()<<"Recieved:"<<str;
            nextBlockSize=0;
            SendToClient(socket,str,"messasge");
            break;
        }
    }
    else
    {
        qDebug() << "DataStream error";
    }
}

void Server::SendToClient(QTcpSocket *socket, const QString &str, const QString &messageType)
{
    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);

    // Форматирование времени без секунд
    QTime time = QTime::currentTime();
    QString timeStr = time.toString("hh:mm");

    out << quint16(0)<<messageType;

    if (messageType == "message") {
            out << timeStr << str; // Для текстового сообщения
        } else if (messageType == "clientList") {
            QStringList clientList;
            for (QTcpSocket *clientSocket : Sockets) {
                clientList.append(QString::number(clientSocket->socketDescriptor()));
            }
            out << clientList; // Отправляем список клиентов
        }

    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
}


