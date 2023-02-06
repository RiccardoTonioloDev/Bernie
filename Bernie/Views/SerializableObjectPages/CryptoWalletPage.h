#ifndef BERNIE_CRYPTOWALLETPAGE_H
#define BERNIE_CRYPTOWALLETPAGE_H

#include "PagesInterface.h"

class CryptoWalletPage : public PagesInterface {
Q_OBJECT
private:
    QLineEdit *blockchainNameField;
    std::vector<QLineEdit *> words;

public:
    CryptoWalletPage(const SerializableObject *ptr = nullptr, bool toEdit = false, QWidget *parent = 0);

signals:
public slots:

    void manageSerializableObjectSlot();
};


#endif
