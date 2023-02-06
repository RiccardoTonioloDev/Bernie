#ifndef TYPESELECTOINPAGE_H
#define TYPESELECTOINPAGE_H

#include "SerializableObjectPages/PagesInterface.h"
#include <QWidget>

class TypeSelectionPage : public QWidget {

Q_OBJECT
public:
    TypeSelectionPage(QWidget *parent = 0);

signals:

    void createAccountSignal(PagesInterface *);

    void createCreditCardSignal(PagesInterface *);

    void createContactSignal(PagesInterface *);

    void createNoteSignal(PagesInterface *);

    void createCryptoWalletSignal(PagesInterface *);

    void returnHomePageSignal();

public slots:

    void createAccountSlot();

    void createCreditCardSlot();

    void createContactSlot();

    void createNoteSlot();

    void createCryptoWalletSlot();

    void returnHomePageSlot();
};


#endif
