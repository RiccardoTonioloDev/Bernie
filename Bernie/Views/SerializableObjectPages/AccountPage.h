#ifndef ACCOUNTPAGE_H
#define ACCOUNTPAGE_H

#include "PagesInterface.h"
#include <QLineEdit>


class AccountPage : public PagesInterface {
Q_OBJECT
private:
    QLineEdit *emailField;
    QLineEdit *usernameField;
    QLineEdit *passwordField;

public:
    AccountPage(const SerializableObject *ptr = nullptr, bool toEdit = false, QWidget *parent = 0);

signals:
public slots:
};


#endif
