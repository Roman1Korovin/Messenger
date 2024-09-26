#ifndef MESSENGER_H
#define MESSENGER_H

#include <QMainWindow>
#include "QTime"
#include <QKeyEvent>
#include "user.h"
#include "authorization.h"



namespace Ui {
class Messenger;
}

class Messenger : public QMainWindow
{
    Q_OBJECT

public:
    explicit Messenger(QWidget *parent = nullptr);
    ~Messenger();


private:
    Ui::Messenger *ui;
    Authorization* auth;
    NetworkManager* netManager;
    User* currentUser;

    QVariantList clients;

    void reset();

signals:
    void signalSendToServer(const QString& messageType, const QVariantList& parameters);



public slots:
    void slotMessageReceived(const QString &timeStr, const QString &message);
    void slotClientListUpdated(const QVariantList &receivedClients);
    void slotAuthComplete(const QVariantList userParams);
    void slotErrorOccurred(QString errorMessage);


private slots:   
    void on_sendButton_clicked();
    void on_sendEnter_pressed();
    void on_textEdit_textChanged();
    void on_userButton_clicked();
    void on_exitButton_clicked();
    void slotItemSelectionChanged();
};

#endif // MESSENGER_H
