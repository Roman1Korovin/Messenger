#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QString>
#include <QTime>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();

private:
    QVector<QTcpSocket*> Sockets;
    void SendToClient(QTcpSocket *socket, const QString &str, const QString &messageType);
    quint16 nextBlockSize;
public slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void slotReadyRead();
    void SendClientList();
};

#endif // SERVER_H
