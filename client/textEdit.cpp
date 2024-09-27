#include "textEdit.h"
#include <QDebug>

MyTextEdit::MyTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
}

void MyTextEdit::keyPressEvent(QKeyEvent *e)
{

    if(e->key() == Qt::Key_Return)
    {
        qDebug() <<"Enter key pressed in MyTextEdit";
        emit enterPressed();
    }
    else
    {
        QTextEdit::keyPressEvent(e); // Передача другим клавишам
    }
}
