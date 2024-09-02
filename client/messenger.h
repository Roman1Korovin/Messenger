#ifndef MESSENGER_H
#define MESSENGER_H

#include <QDialog>
#include "QTcpSocket"
#include "QTime"
#include <QKeyEvent>

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
    quint16 nextBlockSize;

    void SendToServer(const QString &str);



public slots:
    void slotReadyRead();
private slots:
    void on_sendButton_clicked();
    void on_sendEnter_pressed();
    void on_textEdit_textChanged();
};

#endif // MESSENGER_H
