#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "registration.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
    } else {
        qDebug() << "Соединение с базой данных успешно!";
    }

}

MainWindow::~MainWindow()
{
    delete ui; 
    db.close();
}


void MainWindow::on_pushButton_clicked()
{

    ui->statusbar->showMessage("dasfdwe421");
}

void MainWindow::on_registerButton_clicked()
{

    Registration *window = new Registration(this, db);
    window->setModal(true);
    window->exec();
    delete window;

}


