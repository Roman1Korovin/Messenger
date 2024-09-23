#include "authorization.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "registration.h"
#include "messenger.h"



Authorization::Authorization(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{



    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
    } else {
        qDebug() << "Соединение с базой данных успешно!";
    }

    ui->setupUi(this);

    //пряче метки ошибок авторизации при инициализации формы
    ui->loginErrorLabel->hide();
    ui->passwordErrorLabel->hide();

}

Authorization::~Authorization()
{
    delete ui; 
    db.close();
}

//кнопка входа, проверяющая правильность введенных данных
void Authorization::on_pushButton_clicked()
{


    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if(login.isEmpty())
    {
         ui->loginEdit->setStyleSheet("border: none; border-bottom: 2px solid red;");
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
        QSqlQuery query;
        query.prepare("SELECT login, password, username FROM users WHERE login = :login");
        query.bindValue(":login", login);

        if (query.exec()) {
            ui->loginErrorLabel->hide();
            ui->passwordErrorLabel->hide();
            if (query.next()) {



                receivedUser = new User(query.value("username").toString(),
                                  query.value("login").toString(),
                                  query.value("password").toString());
                qDebug() << "Login: " << receivedUser->getLogin();
                qDebug() << "Password: " << receivedUser->getPassword();
                qDebug() << "Username: " << receivedUser->getUsername();


                if (receivedUser->getPassword() == password) {

                    ui->passwordErrorLabel->hide();

                    emit signalAuthComplete(*receivedUser);



                } else {
                    ui->passwordErrorLabel->show();
                }

            } else {
                ui->loginErrorLabel->show();
            }
        } else {
            QMessageBox::critical(this, "Ошибка", "Ошибка обращения к базе данных!");
            qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        }
    }
}

//кнопка для перехда на форму регитсрации
void Authorization::on_registerButton_clicked()
{
    Registration *w = new Registration(this, db);
    w->setModal(true);
    w->exec();
    delete w;
}
