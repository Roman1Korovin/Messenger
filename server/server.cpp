#include "server.h"
#include "QTimer"

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
    connect(socket, &QTcpSocket::disconnected, this, [this, socket, socketDescriptor]() {
        qDebug() << "Client disconnected" << socketDescriptor;
        Sockets.removeOne(socket);
        userMap.remove(socket);


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

    if (in.status() != QDataStream::Ok) {
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

        if (messageType == "message") {

            QString login, messageStr;
            QString timeStr;

            in >> login>>  messageStr;

            timeStr = QTime::currentTime().toString("hh:mm");



            QVariantList messageParams;
            messageParams << login;
            messageParams << timeStr;
            messageParams <<messageStr;



            qDebug()<<"Map: "<<userMap;

            for (auto it = userMap.constBegin(); it != userMap.constEnd(); ++it) {
                    // Проверяем, совпадает ли логин

                qDebug()<<"Value.first = "<<it.value().first << " log:" <<login;

                qDebug()<<"it.key = "<<it.key() << " socket:" <<socket;

                    if (it.value().second == login && it.key() != socket) {  // Проверяем логин и исключаем отправителя

                        qDebug() << it.key() << " here  "<< messageParams;
                        SendToClient(it.key(), "message", messageParams);  // Отправляем сообщение
                    }
            }


        } else if (messageType == "login") {

            QString login, password;


            in >> login >> password;


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

                    if (receivedPassword == password) {
                        // Успешная авторизация

                        QVariantList userParams;
                        userParams<<receivedUsername<<receivedLogin<<receivedPassword;

                        SendToClient(socket, "authSuccess",userParams);

                        isSendingAuthSuccess = true;  // Устанавливаем флаг

                        connect(socket, &QTcpSocket::bytesWritten, this, [this, socket, receivedUsername, receivedLogin](qint64 bytes) {
                            // Если отправка сообщения об успешной авторизации завершена
                            if (isSendingAuthSuccess) {
                                // Теперь обновляем список клиентов
                                userMap.insert(socket, qMakePair(receivedUsername, receivedLogin));
                                updateClientList();
                                isSendingAuthSuccess = false;  // Сбрасываем флаг
                            }
                        });





                    } else {
                        // Неправильный пароль
                        QVariantList errorParams;
                        errorParams << "invalidPass";

                        SendToClient(socket, "authError", errorParams);
                    }
                } else {
                    // Логин не найден
                    QVariantList errorParams;
                    errorParams << "logNotFound";
                    SendToClient(socket, "authError", errorParams );
                }
            } else
            {
                qDebug() << "Request execution error:" << query.lastError().text();
            }

        }
        else if(messageType == "register")
        {
            QString username,login,password;

            in >> username >> login >>password;

            QSqlQuery query;

            query.prepare("SELECT login FROM users WHERE login = :login");
            query.bindValue(":login", login);

            if(query.exec())
            {
                if(!query.next()) // Пользователь с таким логином не найден
                {
                    // Прячем сообщение об ошибке и вставляем нового пользователя в базу данных
                    query.prepare("INSERT INTO users (username, login, password) VALUES (:username, :login, :password)");
                    query.bindValue(":username", username);
                    query.bindValue(":login", login);
                    query.bindValue(":password", password);

                    if (!query.exec()) {
                        qDebug() << "Data insertion error" << query.lastError().text();
                    } else {
                        QVariantList completeRegParams;
                        completeRegParams << "registerSuccess";
                        SendToClient(socket, "regSuccess",  completeRegParams);
                    }
                }
                else
                {
                    // Если логин уже существует

                    QVariantList rejectRegParams;
                    rejectRegParams << "uniqueError";


                    SendToClient(socket, "regError", rejectRegParams);
                }

            }
            else{
                qDebug() << "Request execution error:" << query.lastError().text();
            }
        }
        else {
            qDebug() << "Unknown messageType received:" << messageType;
        }


        nextBlockSize=0;
    }

}

void Server::SendToClient(QTcpSocket *socket, const QString& messageType, const QVariantList& parameters)
{
    QByteArray Data;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_14);

    // Форматирование времени без секунд

    out << quint16(0)<<messageType;

    if (messageType == "message") {

        QString timeStr = parameters.value(0).toString();
        QString messageStr = parameters.value(1).toString();

        out << timeStr << messageStr; // Для текстового сообщения
    }
    else if (messageType == "clientList") {

        for (const QVariant &param : parameters) {

            out << param;
        }
        qDebug()<<parameters;
    }
    else if (messageType == "authSuccess")
    {

        QString username, login,password;

        username = parameters.value(0).toString();
        login = parameters.value(1).toString();
        password = parameters.value(2).toString();

        out << username << login<<password;


    }
    else if(messageType == "authError")
    {
        QString typeError = parameters.value(0).toString();

        out << typeError;

    }
    else if(messageType == "regSuccess")
    {
        qDebug() << "Registration success";
    }
    else if(messageType == "regError")
    {
        qDebug() << "Login uniqueness error";

    }
    else {
        qDebug() << "Unknown messageType: " << messageType;
        return;
    }

    out.device()->seek(0);
    out<<quint16(Data.size()-sizeof(quint16));
    socket->write(Data);
}

void Server::updateClientList()
{
    // Отправляем список клиентских имен всем подключенным клиентам
    for (QTcpSocket *clientSocket : Sockets) {
        QVariantList userMapParams;

        // Получаем логин текущего клиента
        QString currentClientLogin = userMap.value(clientSocket).second;

        // Используем QSet для отслеживания уникальных логинов
        QSet<QString> uniqueLogins;

        // Собираем данные для отправки, исключая дубликаты и данные о текущем клиенте
        for (auto it = userMap.constBegin(); it != userMap.constEnd(); ++it) {
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
