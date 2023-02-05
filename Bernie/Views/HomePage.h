#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include "../Models/Vault.h"

class HomePage : public QWidget {
Q_OBJECT
private:
    Vault &vault;
    QLineEdit *searchBox;
    QListWidget *listOfCards;

public:
    HomePage(Vault &v, QWidget *parent = 0);

    void refresh();

signals:
public slots:

};


#endif
