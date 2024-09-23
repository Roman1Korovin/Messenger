/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QFrame *frame_7;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_3;
    QLineEdit *passwordEdit;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QLineEdit *loginEdit;
    QLabel *identityLogErrorLabel;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QLineEdit *password2Edit;
    QLabel *matchPassErrorLabel;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QLineEdit *usernameEdit;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *confirmButton;
    QSpacerItem *verticalSpacer;
    QPushButton *returnButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->resize(650, 388);
        Registration->setMaximumSize(QSize(972, 578));
        Registration->setBaseSize(QSize(590, 410));
        Registration->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(Registration);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(Registration);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(16777215, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label, 0, Qt::AlignBottom);


        verticalLayout->addWidget(frame, 0, Qt::AlignHCenter);

        frame_2 = new QFrame(Registration);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame_7 = new QFrame(frame_2);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_7);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_3 = new QLabel(frame_7);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_8->addWidget(label_3);

        passwordEdit = new QLineEdit(frame_7);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setMinimumSize(QSize(150, 0));

        verticalLayout_8->addWidget(passwordEdit);


        gridLayout->addWidget(frame_7, 0, 1, 1, 1);

        frame_5 = new QFrame(frame_2);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_2 = new QLabel(frame_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_5->addWidget(label_2);

        loginEdit = new QLineEdit(frame_5);
        loginEdit->setObjectName(QString::fromUtf8("loginEdit"));

        verticalLayout_5->addWidget(loginEdit);

        identityLogErrorLabel = new QLabel(frame_5);
        identityLogErrorLabel->setObjectName(QString::fromUtf8("identityLogErrorLabel"));
        identityLogErrorLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        verticalLayout_5->addWidget(identityLogErrorLabel);


        gridLayout->addWidget(frame_5, 1, 0, 1, 1, Qt::AlignTop);

        frame_6 = new QFrame(frame_2);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_4 = new QLabel(frame_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_7->addWidget(label_4, 0, Qt::AlignTop);

        password2Edit = new QLineEdit(frame_6);
        password2Edit->setObjectName(QString::fromUtf8("password2Edit"));
        password2Edit->setMinimumSize(QSize(150, 0));

        verticalLayout_7->addWidget(password2Edit);

        matchPassErrorLabel = new QLabel(frame_6);
        matchPassErrorLabel->setObjectName(QString::fromUtf8("matchPassErrorLabel"));
        matchPassErrorLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        verticalLayout_7->addWidget(matchPassErrorLabel);


        gridLayout->addWidget(frame_6, 1, 1, 1, 1, Qt::AlignVCenter);

        frame_4 = new QFrame(frame_2);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame_4);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_5 = new QLabel(frame_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_6->addWidget(label_5);

        usernameEdit = new QLineEdit(frame_4);
        usernameEdit->setObjectName(QString::fromUtf8("usernameEdit"));
        usernameEdit->setMinimumSize(QSize(150, 0));

        verticalLayout_6->addWidget(usernameEdit);


        gridLayout->addWidget(frame_4, 0, 0, 1, 1);


        verticalLayout->addWidget(frame_2);

        frame_3 = new QFrame(Registration);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        confirmButton = new QPushButton(frame_3);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        confirmButton->setMinimumSize(QSize(200, 25));
        confirmButton->setMaximumSize(QSize(200, 16777215));

        verticalLayout_4->addWidget(confirmButton, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer);

        returnButton = new QPushButton(frame_3);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setMinimumSize(QSize(200, 25));
        returnButton->setMaximumSize(QSize(200, 16777215));

        verticalLayout_4->addWidget(returnButton, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(frame_3, 0, Qt::AlignTop);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QDialog *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Registration", "\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("Registration", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("Registration", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275", nullptr));
        identityLogErrorLabel->setText(QCoreApplication::translate("Registration", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214 \321\201 \321\202\320\260\320\272\320\270\320\274 \320\273\320\276\320\263\320\270\320\275\320\276\320\274 \321\203\320\266\320\265 \321\201\321\203\321\211\320\265\321\201\321\202\320\262\321\203\320\265\321\202", nullptr));
        label_4->setText(QCoreApplication::translate("Registration", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        matchPassErrorLabel->setText(QCoreApplication::translate("Registration", "\320\237\320\260\321\200\320\276\320\273\320\270 \320\275\320\265 \321\201\320\276\320\262\320\277\320\260\320\264\320\260\321\216\321\202", nullptr));
        label_5->setText(QCoreApplication::translate("Registration", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\270\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        confirmButton->setText(QCoreApplication::translate("Registration", "\320\237\320\276\320\264\321\202\320\262\320\265\321\200\320\264\320\270\321\202\321\214", nullptr));
        returnButton->setText(QCoreApplication::translate("Registration", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214\321\201\321\217 \320\272 \320\260\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
