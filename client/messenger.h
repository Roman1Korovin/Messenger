#ifndef MESSENGER_H
#define MESSENGER_H

#include <QDialog>
#include "QTcpSocket"
#include "QTime"
#include <QKeyEvent>
#include "user.h"

namespace Ui {
class messenger;
}

class Messenger : public QDialog
{
    Q_OBJECT

public:
    explicit Messenger(const User& user, QWidget *parent = nullptr);
    ~Messenger();


private:
    Ui::messenger *ui;
    QTcpSocket *socket;
    quint16 nextBlockSize;
    User currentUser;


    void SendToServer(const QString &str);

    void processServerMessage(QDataStream &in);




public slots:
    void slotReadyRead();
private slots:
    void on_sendButton_clicked();
    void on_sendEnter_pressed();
    void on_textEdit_textChanged();
    void on_userButton_clicked();
    void on_pushButton_clicked();
};

#endif // MESSENGER_H
