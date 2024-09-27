#include "registration.h"
#include "ui_registration.h"
#include "authorization.h"
#include <QMessageBox>



Registration::Registration(NetworkManager *netManager, QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::Registration)

{
    ui->setupUi(this);

    //прячем метки ошибок регистрации при инициализации формы
    ui->matchPassErrorLabel->hide();
    ui->identityLogErrorLabel->hide();

    connect(this, &Registration::signalSendToServer, netManager, &NetworkManager::slotSendToServer);
    connect(netManager, &NetworkManager::signalRegSuccess,this, &Registration::slotRegSuccess);
    connect(netManager, &NetworkManager::signalRegError,this, &Registration::slotRegError);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::slotRegSuccess()
{
    QMessageBox::information(this, "Сообщение", "Регистрация успешна! Выполните вход в окне с авторизацией.");
    qDebug() << "Пользователь успешно зарегистрирован!";
    this->close();
}
void Registration::slotRegError()
{
    ui->identityLogErrorLabel->show();
    qDebug() <<"Пользователь есть уже";
}
//кнопка регистрации, проверяющая приавильность введенных данных
void Registration::on_confirmButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    QString passwordConfirm = ui->password2Edit->text();

    if(username.isEmpty())
    {
        ui->usernameEdit->setStyleSheet("border: none; border-bottom: 2px solid red;");
    }
    else
    {
        ui->usernameEdit->setStyleSheet("");
    }

    if(login.isEmpty())
    {
        ui->loginEdit->setStyleSheet("border: none; border-bottom: 2px solid red;");
    }
    else
    {
        ui->loginEdit->setStyleSheet("");
    }

    if(password.isEmpty() || passwordConfirm.isEmpty() || password!=passwordConfirm )
    {
        ui->passwordEdit->setStyleSheet("border: none; border-bottom: 2px solid red;");
        ui->password2Edit->setStyleSheet("border: none; border-bottom: 2px solid red;");
    }
    else
    {
        ui->passwordEdit->setStyleSheet("");
        ui->password2Edit->setStyleSheet("");
    }

    if(password!=passwordConfirm )
    {
        ui->matchPassErrorLabel->show();
    }
    else
    {
        ui->matchPassErrorLabel->hide();
    }

    if(!username.isEmpty() && !login.isEmpty() && !password.isEmpty() && password == passwordConfirm)
    {

        QVariantList registerParams;

        registerParams << username << login << password;

        emit signalSendToServer("register", registerParams);

    }
}

void Registration::on_returnButton_clicked()
{
    this->close();
}
