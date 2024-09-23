#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "networkmanager.h"


namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT


public:
    explicit Registration(NetworkManager *netManager,QWidget *parent = nullptr);
    ~Registration();

public slots:
    void slotRegSuccess();
    void slotRegError();

private slots:
    void on_confirmButton_clicked();
    void on_returnButton_clicked();


private:
    Ui::Registration *ui;

signals:
    void signalSendToServer(const QString& messageType, const QVariantList& parameters);

};

#endif // REGISTRATION_H
