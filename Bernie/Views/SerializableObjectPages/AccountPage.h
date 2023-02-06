#ifndef ACCOUNTPAGE_H
#define ACCOUNTPAGE_H

#include "PagesInterface.h"


class AccountPage : public PagesInterface {
Q_OBJECT
private:
public:
    AccountPage(const SerializableObject *ptr = nullptr, bool toEdit = false, QWidget *parent = 0);

signals:
public slots:
};


#endif
