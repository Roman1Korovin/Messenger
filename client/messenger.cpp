#include "messenger.h"
#include "ui_messenger.h"
#include "textEdit.h"
#include "QMessageBox"



Messenger::Messenger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Messenger)

//    currentUser(user)

{   netManager = new NetworkManager();
    netManager->connectToServer();

    ui->setupUi(this);
    auth = new Authorization(netManager);
    auth->show();



    ui->stackedWidget->setCurrentIndex(1);



    //замена элемента textEdit
    ui->sendButton->setEnabled(false);
    ui->textEdit->setFocus();


    connect(netManager, &NetworkManager::signalAuthComplete,this, &Messenger::slotAuthComplete);

    connect(netManager, &NetworkManager::signalMessageReceived, this, &Messenger::slotMessageReceived);
    connect(netManager, &NetworkManager::signalClientListUpdated, this, &Messenger::slotClientListUpdated);
    connect(netManager, &NetworkManager::signalErrorOccurred, this, &Messenger::slotErrorOccurred);
    connect(this, &Messenger::signalSendToServer, netManager, &NetworkManager::slotSendToServer);
    connect(ui->textEdit,&MyTextEdit::enterPressed, this, &Messenger::on_sendEnter_pressed);
}

Messenger::~Messenger()
{
    delete ui;
}

void Messenger::slotErrorOccurred(QString errorMessage)
{
    qDebug() <<"fsafs";
    QMessageBox::critical(this, "Ошибка", errorMessage);
    QApplication::exit();
}

void Messenger::slotAuthComplete(const QVariantList userParams)
{

    currentUser = new User(userParams.value(0).toString(),
                           userParams.value(1).toString(),
                           userParams.value(2).toString());  // Сохраняем информацию о текущем пользователе

    // Обновляем элементы интерфейса
    ui->userButton->setText(currentUser->getUsername());
    ui->usernameLabel->setText(ui->usernameLabel->text() + "\n" + currentUser->getUsername());
    ui->loginLabel->setText(ui->loginLabel->text() + "\n" + currentUser->getLogin());
    ui->passwordLabel->setText(ui->passwordLabel->text() + "\n" + currentUser->getPassword());

    auth->close();
    auth->reset();
    this->show();
}



void Messenger::slotMessageReceived(const QString &timeStr, const QString &message)
{
    ui->textBrowser->append(timeStr + "  " + message);
}

void Messenger::slotClientListUpdated(const QStringList &clients)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(clients);

}

void Messenger::on_sendButton_clicked()
{
    QVariantList message;
    message<<ui->textEdit->toPlainText();
    emit signalSendToServer("message",  message);
      ui->textEdit->setFocus();
      ui->textEdit->clear();
}

void Messenger::on_sendEnter_pressed()
{
    if(ui->textEdit->hasFocus())
    {
        QVariantList messageParams;
        messageParams<<ui->textEdit->toPlainText();
        emit signalSendToServer("message",  messageParams);
        ui->textEdit->clear();
    }
}


void Messenger::on_textEdit_textChanged()
{
    if(ui->textEdit->toPlainText().isEmpty())
    {
        ui->sendButton->setEnabled(false);
    }
    else
    {
       ui->sendButton->setEnabled(true);
    }
}



void Messenger::on_userButton_clicked()
{
    if(ui->stackedWidget->currentIndex()==0)
        ui->stackedWidget->setCurrentIndex(1);
    else
        ui->stackedWidget->setCurrentIndex(0);
}

void Messenger::on_exitButton_clicked()
{
    auth->show();
    this->close();
    this->reset();
}

void Messenger::reset()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->textEdit->clear();
    ui->textBrowser->clear();
    ui->userSearchEdit->clear();

    ui->usernameLabel->setText("Ваше имя пользователя:");
    ui->loginLabel->setText("Ваш логин:");
    ui->passwordLabel->setText("Ваш пароль:");
}



