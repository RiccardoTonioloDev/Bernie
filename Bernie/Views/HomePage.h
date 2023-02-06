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

    void changeByVector(const std::vector<const SerializableObject *> &vec);

public:
    HomePage(Vault &v, QWidget *parent = 0);

    void refresh();

signals:

    void addDataSignal();

public slots:

    void filterAll();

    void filterAccount();

    void filterCrypto();

    void filterCreditCard();

    void filterNote();

    void filterContacts();

    void filterByName(const QString &name);

    void returnPressed();

    void addDataSlot();
};


#endif
