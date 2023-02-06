#ifndef TYPESELECTOINPAGE_H
#define TYPESELECTOINPAGE_H

#include <QWidget>

class TypeSelectionPage : public QWidget {

Q_OBJECT
public:
    TypeSelectionPage(QWidget *parent = 0);

signals:

    void createAccountSignal();

    void createCreditCardSignal();

    void createContactSignal();

    void createNoteSignal();

    void createCryptoWalletSignal();

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
