#ifndef MESSENGER_H
#define MESSENGER_H

#include <QDialog>
#include "QTcpSocket"

namespace Ui {
class messenger;
}

class Messenger : public QDialog
{
    Q_OBJECT

public:
    explicit Messenger(QWidget *parent = nullptr);
    ~Messenger();

private:
    Ui::messenger *ui;
    QTcpSocket *socket;
    QByteArray Data;
    void SendToServer(const QString &str);

public slots:
    void slotReadyRead();
private slots:
    void on_sendButton_clicked();
    void on_lineEdit_returnPressed();
    void on_lineEdit_textChanged(const QString &arg1);
};

#endif // MESSENGER_H
