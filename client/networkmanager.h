#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QTcpSocket>
#include <QObject>
#include <QVector>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    void connectToServer();


public slots:
    void slotSendToServer(const QString& messageType, const QVariantList& parameters);


private slots:
    void slotReadyRead();
    void slotErrorOccurred(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket *socket;
    quint16 nextBlockSize;

signals:
    void signalMessageReceived(const QString &timeStr, const QString &message);
    void signalClientListUpdated(const QVariantList clients);
    void signalErrorOccurred(const QString errorMessage);
    void signalAuthComplete(const QVariantList userParams);
    void signalAuthError(const QString errorType);
    void signalRegSuccess();
    void signalRegError();
};

#endif // NETWORKMANAGER_H
