#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"



Registration::Registration(QWidget *parent, QSqlDatabase db ) :
    QDialog(parent),
    ui(new Ui::Registration),
    m_db(db)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_confirmButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    QString passwordConfirm = ui->password2Edit->text();

    if(!username.isEmpty() && !login.isEmpty() && !password.isEmpty() && password == passwordConfirm)
    {
        QSqlQuery query(m_db);
        query.prepare("INSERT INTO users (username, login, password) VALUES (:username, :login, :password)");
        query.bindValue(":username", username);
        query.bindValue(":login", login);
        query.bindValue(":password", password);

        if (!query.exec()) {
               qDebug() << "Ошибка вставки данных:" << query.lastError().text();
           } else {
               qDebug() << "Пользователь успешно зарегистрирован!";
               this->close();
           }
    }
}

void Registration::on_returnButton_clicked()
{
    this->close();
}
