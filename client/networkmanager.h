#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QTcpSocket>
#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    void connectToServer();


public slots:
    void slotSendToServer(QString message);


private slots:
    void slotReadyRead();
    void slotErrorOccurred(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket *socket;
    quint16 nextBlockSize;

signals:
    void messageReceived(const QString &timeStr, const QString &message);
    void clientListUpdated(const QStringList clients);
    void signalErrorOccurred(const QString errorMessage);

};

#endif // NETWORKMANAGER_H
