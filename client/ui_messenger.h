/********************************************************************************
** Form generated from reading UI file 'messenger.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSENGER_H
#define UI_MESSENGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_messenger
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QPushButton *sendButton;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *messenger)
    {
        if (messenger->objectName().isEmpty())
            messenger->setObjectName(QString::fromUtf8("messenger"));
        messenger->resize(624, 493);
        gridLayout = new QGridLayout(messenger);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit = new QLineEdit(messenger);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        sendButton = new QPushButton(messenger);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        gridLayout->addWidget(sendButton, 1, 1, 1, 1);

        textBrowser = new QTextBrowser(messenger);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 2);


        retranslateUi(messenger);

        QMetaObject::connectSlotsByName(messenger);
    } // setupUi

    void retranslateUi(QDialog *messenger)
    {
        messenger->setWindowTitle(QCoreApplication::translate("messenger", "Dialog", nullptr));
        sendButton->setText(QCoreApplication::translate("messenger", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class messenger: public Ui_messenger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGER_H
