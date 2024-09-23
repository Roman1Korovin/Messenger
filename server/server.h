#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QString>
#include <QTime>
#include "QSqlDatabase"
#include "QSqlError"
#include "QSqlQuery"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    ~Server();

private:    
    QVector<QTcpSocket*> Sockets;
    quint16 nextBlockSize;
    QSqlDatabase db;

public slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void slotReadyRead();
    void SendToClient(QTcpSocket *socket, const QString& messageType, const QVariantList& parameters);

};

#endif // SERVER_H
