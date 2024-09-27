#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "QDebug"

#include "networkmanager.h"
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Authorization : public QMainWindow
{
    Q_OBJECT


public:
    Authorization(NetworkManager *netManager,QWidget *parent = nullptr);
    ~Authorization();

    void reset();

public slots:
    void slotAuthError(const QString errorType);

signals:
    void signalSendToServer(const QString& messageType, const QVariantList& parameters);

private:
    Ui::MainWindow *ui;
    User* receivedUser;
    NetworkManager* netManager;

private slots:
    void on_registerButton_clicked();
    void on_authButton_clicked();
};
#endif // MAINWINDOW_H
