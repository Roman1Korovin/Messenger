#include "messengerform.h"
#include "ui_messengerform.h"

MessengerForm::MessengerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessengerForm)
{
    ui->setupUi(this);
}

MessengerForm::~MessengerForm()
{
    delete ui;
}
