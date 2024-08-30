#ifndef MESSENGERFORM_H
#define MESSENGERFORM_H

#include <QWidget>

namespace Ui {
class MessengerForm;
}

class MessengerForm : public QWidget
{
    Q_OBJECT

public:
    explicit MessengerForm(QWidget *parent = nullptr);
    ~MessengerForm();

private:
    Ui::MessengerForm *ui;
};

#endif // MESSENGERFORM_H
