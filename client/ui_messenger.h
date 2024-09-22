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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "textEdit.h"

QT_BEGIN_NAMESPACE

class Ui_messenger
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QPushButton *userButton;
    QStackedWidget *stackedWidget;
    QWidget *page2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *usernameLabel;
    QLabel *loginLabel;
    QLabel *passwordLabel;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QWidget *page1;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QLineEdit *lineEdit_2;
    QFrame *line;
    QFrame *frame_4;
    QGridLayout *gridLayout_3;
    QTextBrowser *textBrowser;
    QPushButton *sendButton;
    MyTextEdit *textEdit;

    void setupUi(QDialog *messenger)
    {
        if (messenger->objectName().isEmpty())
            messenger->setObjectName(QString::fromUtf8("messenger"));
        messenger->resize(981, 435);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(messenger->sizePolicy().hasHeightForWidth());
        messenger->setSizePolicy(sizePolicy);
        messenger->setBaseSize(QSize(1000, 500));
        horizontalLayout = new QHBoxLayout(messenger);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(messenger);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        userButton = new QPushButton(frame_3);
        userButton->setObjectName(QString::fromUtf8("userButton"));

        gridLayout_2->addWidget(userButton, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(frame_3);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        frame = new QFrame(page2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 346, 391));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy2);
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setMaximumSize(QSize(16777215, 200));
        frame_2->setBaseSize(QSize(0, 0));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        usernameLabel = new QLabel(frame_2);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(usernameLabel->sizePolicy().hasHeightForWidth());
        usernameLabel->setSizePolicy(sizePolicy3);
        usernameLabel->setMinimumSize(QSize(0, 40));
        usernameLabel->setMaximumSize(QSize(16777215, 16777215));
        usernameLabel->setBaseSize(QSize(0, 60));
        usernameLabel->setWordWrap(true);

        verticalLayout_4->addWidget(usernameLabel);

        loginLabel = new QLabel(frame_2);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));
        sizePolicy3.setHeightForWidth(loginLabel->sizePolicy().hasHeightForWidth());
        loginLabel->setSizePolicy(sizePolicy3);
        loginLabel->setMinimumSize(QSize(0, 40));
        loginLabel->setMaximumSize(QSize(16777215, 16777215));
        loginLabel->setBaseSize(QSize(0, 60));
        loginLabel->setWordWrap(true);

        verticalLayout_4->addWidget(loginLabel);

        passwordLabel = new QLabel(frame_2);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));
        sizePolicy3.setHeightForWidth(passwordLabel->sizePolicy().hasHeightForWidth());
        passwordLabel->setSizePolicy(sizePolicy3);
        passwordLabel->setMinimumSize(QSize(0, 40));
        passwordLabel->setMaximumSize(QSize(16777215, 16777215));
        passwordLabel->setBaseSize(QSize(0, 60));
        passwordLabel->setWordWrap(true);

        verticalLayout_4->addWidget(passwordLabel);


        verticalLayout_3->addWidget(frame_2);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_3->addWidget(pushButton);

        stackedWidget->addWidget(page2);
        page1 = new QWidget();
        page1->setObjectName(QString::fromUtf8("page1"));
        verticalLayout = new QVBoxLayout(page1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(page1);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        stackedWidget->addWidget(page1);

        gridLayout_2->addWidget(stackedWidget, 1, 0, 1, 2);

        lineEdit_2 = new QLineEdit(frame_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(lineEdit_2, 0, 1, 1, 1);


        horizontalLayout->addWidget(frame_3);

        line = new QFrame(messenger);
        line->setObjectName(QString::fromUtf8("line"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy5);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        frame_4 = new QFrame(messenger);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy1);
        frame_4->setMinimumSize(QSize(0, 0));
        frame_4->setBaseSize(QSize(0, 0));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_4);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        textBrowser = new QTextBrowser(frame_4);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMinimumSize(QSize(300, 0));

        gridLayout_3->addWidget(textBrowser, 0, 1, 1, 2);

        sendButton = new QPushButton(frame_4);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setEnabled(false);
        sendButton->setFocusPolicy(Qt::NoFocus);

        gridLayout_3->addWidget(sendButton, 1, 2, 1, 1);

        textEdit = new MyTextEdit(frame_4);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy6);
        textEdit->setMaximumSize(QSize(16777215, 23));
        textEdit->setBaseSize(QSize(0, 0));

        gridLayout_3->addWidget(textEdit, 1, 1, 1, 1);


        horizontalLayout->addWidget(frame_4);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(2, 3);

        retranslateUi(messenger);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(messenger);
    } // setupUi

    void retranslateUi(QDialog *messenger)
    {
        messenger->setWindowTitle(QCoreApplication::translate("messenger", "Dialog", nullptr));
        userButton->setText(QCoreApplication::translate("messenger", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214", nullptr));
        usernameLabel->setText(QCoreApplication::translate("messenger", "\320\222\320\260\321\210\320\265 \320\270\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217: ", nullptr));
        loginLabel->setText(QCoreApplication::translate("messenger", "\320\222\320\260\321\210 \320\273\320\276\320\263\320\270\320\275:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("messenger", "\320\222\320\260\321\210 \320\277\320\260\321\200\320\276\320\273\321\214:", nullptr));
        pushButton->setText(QCoreApplication::translate("messenger", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
        sendButton->setText(QCoreApplication::translate("messenger", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class messenger: public Ui_messenger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGER_H
