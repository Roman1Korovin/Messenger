#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QString>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();

private:
    QVector<QTcpSocket*> Sockets;  // Хранит указатели на активные соединения
    void SendToClient(QTcpSocket *socket, const QString &str);  // Метод для отправки данных конкретному клиенту

public slots:
    void incomingConnection(qintptr socketDescriptor) override;  // Обработка нового входящего соединения
    void slotReadyRead();  // Обработка данных, поступивших от клиента
};

#endif // SERVER_H
