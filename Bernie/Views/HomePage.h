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

    void watchDataSignal();

    void editDataSignal();

    void removeDataSignal();

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

    void watchDataSlot(const SerializableObject *);

    void editDataSlot(const SerializableObject *);

    void removeDataSlot(const SerializableObject *);
};


#endif
