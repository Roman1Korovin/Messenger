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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include "textEdit.h"

QT_BEGIN_NAMESPACE

class Ui_messenger
{
public:
    QGridLayout *gridLayout;
    QListView *listView;
    QToolButton *toolButton;
    QLineEdit *lineEdit_2;
    QPushButton *sendButton;
    QFrame *line;
    QTextBrowser *textBrowser;
    MyTextEdit *textEdit;

    void setupUi(QDialog *messenger)
    {
        if (messenger->objectName().isEmpty())
            messenger->setObjectName(QString::fromUtf8("messenger"));
        messenger->resize(624, 493);
        gridLayout = new QGridLayout(messenger);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listView = new QListView(messenger);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout->addWidget(listView, 1, 0, 4, 3);

        toolButton = new QToolButton(messenger);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);

        lineEdit_2 = new QLineEdit(messenger);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 0, 1, 1, 1);

        sendButton = new QPushButton(messenger);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setEnabled(false);
        sendButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(sendButton, 4, 5, 1, 1);

        line = new QFrame(messenger);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 3, 5, 1);

        textBrowser = new QTextBrowser(messenger);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 4, 4, 2);

        textEdit = new MyTextEdit(messenger);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(textEdit, 4, 4, 1, 1);


        retranslateUi(messenger);

        QMetaObject::connectSlotsByName(messenger);
    } // setupUi

    void retranslateUi(QDialog *messenger)
    {
        messenger->setWindowTitle(QCoreApplication::translate("messenger", "Dialog", nullptr));
        toolButton->setText(QCoreApplication::translate("messenger", "...", nullptr));
        sendButton->setText(QCoreApplication::translate("messenger", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class messenger: public Ui_messenger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGER_H
