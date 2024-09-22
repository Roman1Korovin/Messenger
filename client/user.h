#ifndef USER_H
#define USER_H

#include "QString"


class User
{
public:
    User(const QString &username, const QString &login, const QString &password)
        : username(username), login(login), password(password) {}

    QString getUsername() const { return username; }
    QString getLogin() const { return login; }
    QString getPassword() const { return password; }

private:
    QString username;
    QString login;
    QString password;
};

#endif // USER_H
