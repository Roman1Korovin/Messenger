#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSqlDatabase"
#include "QSqlError"
#include "QSqlQuery"
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
    Authorization(QWidget *parent = nullptr);
    ~Authorization();

private slots:
    void on_pushButton_clicked();
    void on_registerButton_clicked();




private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    User* receivedUser;

signals:
    void signalAuthComplete(const User &user);




};
#endif // MAINWINDOW_H
