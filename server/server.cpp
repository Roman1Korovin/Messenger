#include "server.h"
#include "QTimer"
#include <QThread>


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


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        qDebug() << "ОDatabase connection error:" << db.lastError().text();
    } else {
        qDebug() << "The connection to the database is successful!!";
    }

    nextBlockSize=0;
}



Server::~Server()
{
    db.close();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, [this, socket, socketDescriptor]()
    {
        Sockets.removeOne(socket);
        userMap.remove(socket);

        qDebug() << "Client disconnected" << socketDescriptor;

        updateClientList();

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

    if (in.status() != QDataStream::Ok)
    {
        qDebug() << "DataStream error";
        return;
    }

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


        QString messageType;
        in >> messageType;

        if (messageType == "message")
        {
            messageProccessing(in);

        } else if (messageType == "login")
        {
            loginProccessing(in, socket);
        }
        else if(messageType == "register")
        {
            registerProccessing(in, socket);
        }
        else {
            qDebug() << "Unknown messageType received:" << messageType;
        }

        nextBlockSize=0;
    }

}

void Server::SendToClient( QTcpSocket* socket, const QString& messageType, const QVariantList& parameters)
{
    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);

    // Форматирование времени без секунд

    out << quint16(0)<<messageType;

    for (const QVariant &param : parameters)
    {
        out << param;
    }

    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
}

void Server::updateClientList()
{
    // Отправляем список клиентских имен всем подключенным клиентам
    for (QTcpSocket *clientSocket : Sockets)
    {
        QVariantList userMapParams;

        // Получаем логин текущего клиента
        QString currentClientLogin = userMap.value(clientSocket).second;

        // Используем QSet для отслеживания уникальных логинов
        QSet<QString> uniqueLogins;


        for (auto it = userMap.constBegin(); it != userMap.constEnd(); ++it)
        {
            QString userLogin = it.value().second;

            // Пропустить текущего пользователя и избежать добавления дубликатов
            if (userLogin == currentClientLogin || uniqueLogins.contains(userLogin)) {
                continue;
            }

            // Добавляем логин в набор уникальных логинов
            uniqueLogins.insert(userLogin);

            QVariantMap userInfo;
            userInfo["username"] = it.value().first; // Имя
            userInfo["login"] = userLogin;           // Логин
            userMapParams << userInfo;
        }

        // Отправляем список остальных клиентов текущему клиенту
        SendToClient(clientSocket, "clientList", userMapParams);
    }
}

void Server::messageProccessing(QDataStream &in)
{
    QVariant senderLoginVariant, recipientLoginVariant, messageStrVariant;


    in >> senderLoginVariant >> recipientLoginVariant >> messageStrVariant;

    QString senderLogin = senderLoginVariant.toString();
    QString recipientLogin = recipientLoginVariant.toString();
    QString messageStr = messageStrVariant.toString();

    QString timeStr;
    timeStr = QTime::currentTime().toString("hh:mm");


    bool isMyselfMessage;

    for (auto it = userMap.constBegin(); it != userMap.constEnd(); ++it)
    {
        // Проверяем, совпадает ли логин

        if (it.value().second == recipientLogin) {  // Проверяем логин и исключаем отправителя

            QVariantList messageParams;

            messageParams << senderLogin;
            messageParams << timeStr;
            messageParams <<messageStr;
            isMyselfMessage= false;
            messageParams <<isMyselfMessage;

            SendToClient(it.key(), "message", messageParams);

        }
        if(it.value().second == senderLogin )
        {

            QVariantList messageParams;

            messageParams << recipientLogin;
            messageParams << timeStr;
            messageParams <<messageStr;
            isMyselfMessage= true;
            messageParams <<isMyselfMessage;

            SendToClient(it.key(), "message", messageParams);


        }
    }
}

void Server::loginProccessing(QDataStream &in, QTcpSocket* socket)
{

    QVariant loginVariant, passwordVariant;
    in >> loginVariant >> passwordVariant;


    QString login = loginVariant.toString();
    QString password = passwordVariant.toString();


    QSqlQuery query;
    query.prepare("SELECT username,login, password FROM users WHERE login = :login");
    query.bindValue(":login", login);


    if (query.exec())
    {
        if(query.next())
        {

            QString receivedUsername = query.value("username").toString();
            QString receivedLogin = query.value("login").toString();
            QString receivedPassword = query.value("password").toString();

            if (receivedPassword == password)
            {


                QVariantList userParams;
                userParams<<receivedUsername<<receivedLogin<<receivedPassword;

                SendToClient(socket, "authSuccess",userParams);

                isSendingAuthSuccess = true;

                connect(socket, &QTcpSocket::bytesWritten, this, [this, socket, receivedUsername, receivedLogin](qint64 bytes) {

                    if (isSendingAuthSuccess)
                    {

                        userMap.insert(socket, qMakePair(receivedUsername, receivedLogin));
                        updateClientList();
                        isSendingAuthSuccess = false;
                    }
                });
            } else
            {
                QVariantList errorParams;
                errorParams << "invalidPass";

                SendToClient(socket, "authError", errorParams);
            }
        } else
        {

            QVariantList errorParams;
            errorParams << "logNotFound";
            SendToClient(socket, "authError", errorParams );
        }
    } else
    {
        qDebug() << "Request execution error:" << query.lastError().text();
    }
}

void Server::registerProccessing(QDataStream &in, QTcpSocket *socket)
{
    QVariant usernameVariant, loginVariant, passwordVariant;
    in >> usernameVariant >> loginVariant >> passwordVariant;

    QString username = usernameVariant.toString();
    QString login = loginVariant.toString();
    QString password = passwordVariant.toString();

    QSqlQuery query;

    query.prepare("SELECT login FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if(query.exec())
    {
        if(!query.next())
        {

            query.prepare("INSERT INTO users (username, login, password) VALUES (:username, :login, :password)");
            query.bindValue(":username", username);
            query.bindValue(":login", login);
            query.bindValue(":password", password);

            if (!query.exec())
            {
                qDebug() << "Data insertion error" << query.lastError().text();
            } else
            {
                QVariantList completeRegParams;
                completeRegParams << "registerSuccess";
                SendToClient(socket, "regSuccess",  completeRegParams);
            }
        }
        else
        {
            QVariantList rejectRegParams;
            rejectRegParams << "uniqueError";

            SendToClient(socket, "regError", rejectRegParams);
        }
    }
    else
    {
        qDebug() << "Request execution error:" << query.lastError().text();
    }
}
