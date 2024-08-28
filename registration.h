#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~Registration();

private slots:
    void on_confirmButton_clicked();

    void on_returnButton_clicked();

private:
    Ui::Registration *ui;
    QSqlDatabase m_db;
};

#endif // REGISTRATION_H
