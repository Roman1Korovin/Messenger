#include "authorization.h"
#include "ui_authorization.h"
#include "QMessageBox"
#include "registration.h"
#include "messenger.h"



Authorization::Authorization(NetworkManager *netManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , netManager(netManager)
{

    ui->setupUi(this);

    //пряче метки ошибок авторизации при инициализации формы
    ui->loginErrorLabel->hide();
    ui->passwordErrorLabel->hide();

    connect(this, &Authorization::signalSendToServer, netManager, &NetworkManager::slotSendToServer);
    connect(netManager, &NetworkManager::signalAuthError,this, &Authorization::slotAuthError);

}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::slotAuthError(const QString errorType)
{
    if(errorType == "logNotFound")
    {
        ui->loginErrorLabel->show();
    }
    else if(errorType == "invalidPass")
    {
        ui->passwordErrorLabel->show();
    }
}

//кнопка входа, проверяющая правильность введенных данных
void Authorization::on_authButton_clicked()
{

    QString login = ui->loginEdit->text().trimmed();
    QString password = ui->passwordEdit->text().trimmed();

    if(login.isEmpty())
    {
        ui->loginEdit->setStyleSheet("border: none; border-bottom: 2px solid red;");
        ui->loginErrorLabel->hide();
        ui->passwordErrorLabel->hide();
    }
    else
    {
        ui->loginEdit->setStyleSheet("");
    }

    if(password.isEmpty())
    {
        ui->passwordEdit->setStyleSheet("border: none; border-bottom: 2px solid red;");

    }
    else
    {
        ui->passwordEdit->setStyleSheet("");
    }

    if (!login.isEmpty() && !password.isEmpty())
    {

        ui->loginErrorLabel->hide();
        ui->passwordErrorLabel->hide();

        QVariantList loginParams;
        loginParams<<login <<password;

        emit signalSendToServer("login",loginParams);
    }
    else {
        ui->loginErrorLabel->hide();
        ui->passwordErrorLabel->hide();
    }
}


//кнопка для перехда на форму регитсрации
void Authorization::on_registerButton_clicked()
{
    this->reset();

    Registration *w = new Registration(netManager);
    w->setModal(true);
    w->exec();
    delete w;


}

void Authorization::reset()
{
    ui->loginEdit->clear();
    ui->loginEdit->setStyleSheet("");
    ui->passwordEdit->clear();
    ui->passwordEdit->setStyleSheet("");
    ui->loginErrorLabel->hide();
    ui->passwordErrorLabel->hide();
}
