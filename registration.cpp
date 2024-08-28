#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_confirmButton_clicked()
{


    this->close();
}

void Registration::on_pushButton_2_clicked()
{
    this->close();
}
