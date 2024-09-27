#include "messenger.h"
#include "ui_messenger.h"
#include "textEdit.h"
#include "QMessageBox"



Messenger::Messenger(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Messenger)


{
    ui->setupUi(this);

    netManager = new NetworkManager();
    netManager->connectToServer();


    auth = new Authorization(netManager);
    auth->show();


    ui->stackedWidget->setCurrentIndex(1);

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setFocus();

    ui->sendButton->setEnabled(false);

    QString message = "Добро пожаловать в мессенджер";
    QString formattedMessage = QString("<div style='text-align:center; font-size:24px;'>%1</div>").arg(message);
    ui->textBrowser->append(formattedMessage);






    connect(netManager, &NetworkManager::signalAuthComplete,this, &Messenger::slotAuthComplete);

    connect(netManager, &NetworkManager::signalMessageReceived, this, &Messenger::slotMessageReceived);
    connect(netManager, &NetworkManager::signalClientListUpdated, this, &Messenger::slotClientListUpdated);
    connect(netManager, &NetworkManager::signalErrorOccurred, this, &Messenger::slotErrorOccurred);
    connect(this, &Messenger::signalSendToServer, netManager, &NetworkManager::slotSendToServer);


    connect(ui->textEdit,&MyTextEdit::enterPressed, this, &Messenger::on_sendEnter_pressed);
    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &Messenger::slotItemSelectionChanged);
}

Messenger::~Messenger()
{
    delete ui;
}

void Messenger::slotErrorOccurred(QString errorMessage)
{
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



void Messenger::slotMessageReceived(const QString &senderLogin, const QString &timeStr, const QString &message, const bool &isMyselfMessage)
{

    MessageInfo newMessage(timeStr, message, isMyselfMessage);

    userMessages[senderLogin].append(newMessage);



    QListWidgetItem *selectedItem = ui->listWidget->currentItem();



    if (selectedItem) {
        // Получаем данные пользователя, выбранного в listWidget
        QVariantMap clientMap = selectedItem->data(Qt::UserRole).toMap();
        QString selectedLogin = clientMap.value("login").toString();


        if(isMyselfMessage){
            ui->textBrowser->append("[я]: " +timeStr + "  " + message);
        }

        // Сравниваем логин выбранного пользователя с логином отправителя сообщения
        else if (selectedLogin == senderLogin) {


            ui->textBrowser->append(timeStr + "  " + message);


        }

    }
}

void Messenger::slotClientListUpdated(const QVariantList &receivedClients)
{
    // Сохраняем логин выбранного пользователя, если он есть
    QString selectedLogin;
    if (ui->listWidget->currentItem()) {
        QVariantMap selectedClientMap = ui->listWidget->currentItem()->data(Qt::UserRole).toMap();
        selectedLogin = selectedClientMap.value("login").toString();
    }

    // Очищаем список
    ui->listWidget->clear();
    clients = receivedClients;

    for (const QVariant &client : clients) {
        QVariantMap clientMap = client.toMap();  // Преобразуем элемент списка в QVariantMap
        QString username = clientMap.value("username").toString();
        QString login = clientMap.value("login").toString();

        if (!userMessages.contains(login)) {
            userMessages[login] = QList<MessageInfo>();  // Добавляем пользователя с пустым списком сообщений
        }

        QListWidgetItem *item = new QListWidgetItem(username);  // Создаем новый элемент
        item->setData(Qt::UserRole, clientMap);  // Сохраняем QVariantMap в качестве пользовательских данных
        ui->listWidget->addItem(item);  // Добавляем элемент в listWidget

        // Если это ранее выбранный пользователь, восстанавливаем его выбор
        if (login == selectedLogin) {
            ui->listWidget->setCurrentItem(item);  // Выбираем этого пользователя
        }
    }
}
void Messenger::slotItemSelectionChanged()
{
    // Проверяем, есть ли выбранный элемент в списке
    if (ui->listWidget->selectedItems().count() > 0) {
        ui->textEdit->setReadOnly(false);  // Если есть выбранные элементы, делаем QTextEdit доступным

        // Получаем текущий выбранный элемент
        QListWidgetItem *selectedItem = ui->listWidget->currentItem();

        if (selectedItem) {
            // Получаем данные выбранного пользователя
            QVariantMap clientMap = selectedItem->data(Qt::UserRole).toMap();
            QString selectedLogin = clientMap.value("login").toString();

            // Очищаем textBrowser перед отображением новых сообщений
            ui->textBrowser->clear();

            // Проверяем, есть ли сообщения для данного логина
            if (userMessages.contains(selectedLogin)) {
                // Выводим все сообщения, связанные с этим пользователем
                for (const MessageInfo &messageInfo : userMessages[selectedLogin]) {
                    // Форматируем сообщение, включая время и текст
                    QString formattedMessage = messageInfo.timeStr + " " + messageInfo.messageText;


                    if (messageInfo.isMyselfMessage) {
                        formattedMessage = "[Я] " + formattedMessage;  // Помечаем сообщения от себя
                    }

                    ui->textBrowser->append(formattedMessage);  // Добавляем сообщение в textBrowser
                }
            }
        }
        ui->textEdit->setFocus();

    } else {
        ui->textEdit->setReadOnly(true);  // Если нет выбранных элементов, делаем QTextEdit недоступным
        ui->textBrowser->clear();  // Очищаем textBrowser, если ничего не выбрано
    }
}

void Messenger::on_sendButton_clicked()
{

    QVariantList messageParams;

    QListWidgetItem *selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        QVariantMap clientMap = selectedItem->data(Qt::UserRole).toMap();

        messageParams << currentUser->getLogin();
        messageParams << clientMap.value("login").toString();

        messageParams << ui->textEdit->toPlainText();
        emit signalSendToServer("message", messageParams);

        ui->textEdit->setFocus();
        ui->textEdit->clear();
    }
}
void Messenger::on_sendEnter_pressed()
{
    if(ui->textEdit->hasFocus() && !ui->textEdit->toPlainText().trimmed().isEmpty())
    {
        QVariantList messageParams;
        QListWidgetItem *selectedItem = ui->listWidget->currentItem();
        if (selectedItem) {
            QVariantMap clientMap = selectedItem->data(Qt::UserRole).toMap();


            messageParams << currentUser->getLogin();
            messageParams << clientMap.value("login").toString();


            messageParams << ui->textEdit->toPlainText();
            emit signalSendToServer("message", messageParams);


            ui->textEdit->setFocus();
            ui->textEdit->clear();
        }
    }
}


void Messenger::on_textEdit_textChanged()
{


    if(ui->textEdit->toPlainText().trimmed().isEmpty())
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




void Messenger::on_userSearchEdit_textChanged(const QString &searchText)
{
    // Перебираем все элементы в listWidget
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);

        // Получаем username из элемента списка
        QString username = item->text();

        // Проверяем, содержится ли введенный текст в username (без учета регистра)
        if (username.contains(searchText, Qt::CaseInsensitive)) {
            item->setHidden(false);  // Показываем элемент
        } else {
            item->setHidden(true);  // Скрываем элемент, если не совпадает
        }
    }
}
