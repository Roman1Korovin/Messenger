#include "registration.h"
#include "ui_registration.h"
#include "authorization.h"
#include <QMessageBox>



Registration::Registration(QWidget *parent, QSqlDatabase db ) :
    QDialog(parent),
    ui(new Ui::Registration),
    m_db(db)
{
    ui->setupUi(this);

    //прячем метки ошибок регистрации при инициализации формы
    ui->matchErrorLabel->hide();
    ui->identityErrorLabel->hide();
}

Registration::~Registration()
{
    delete ui;
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
        ui->matchErrorLabel->show();
    }
    else
    {
        ui->matchErrorLabel->hide();
    }

    if(!username.isEmpty() && !login.isEmpty() && !password.isEmpty() && password == passwordConfirm)
    {

        QSqlQuery query;

        query.prepare("SELECT login FROM users WHERE login = :login");
        query.bindValue(":login", login);
        if(query.exec())
        {
            if(!query.next())
            {
                ui->identityErrorLabel->hide();

                query.prepare("INSERT INTO users (username, login, password) VALUES (:username, :login, :password)");
                query.bindValue(":username", username);
                query.bindValue(":login", login);
                query.bindValue(":password", password);

                if (!query.exec()) {
                    QMessageBox::critical(this, "Ошибка", "Ошибка обращения к базе данных!");
                       qDebug() << "Ошибка вставки данных:" << query.lastError().text();
                   } else {
                       QMessageBox::information(this, "Сообщение", "Регистрация успешна! Выполните вход в окне с авторизацией.");
                       qDebug() << "Пользователь успешно зарегистрирован!";
                       this->close();
                   }            
            }
            else
            {
                ui->identityErrorLabel->show();
                qDebug() <<"Пользователь есть уже";              
            }
        }
    }
}

//кнопка возвращения к авторизации
void Registration::on_returnButton_clicked()
{
    this->close();
}
