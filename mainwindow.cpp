#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "registration.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    ui->statusbar->showMessage("dasfdwe421");
}

void MainWindow::on_registerButton_clicked()
{

    Registration *window = new Registration(this);
    window->setModal(true);
    window->exec();
    delete window;

}


