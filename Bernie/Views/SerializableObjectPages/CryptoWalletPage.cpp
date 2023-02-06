#include "CryptoWalletPage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../../Models/CryptoWallet.h"

CryptoWalletPage::CryptoWalletPage(const SerializableObject *ptr, bool toEdit, QWidget *parent) {
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    const CryptoWallet *ptrCrypto = nullptr;
    if (ptr) ptrCrypto = static_cast<const CryptoWallet *>(ptr);

    //First row
    QHBoxLayout *firstRow = new QHBoxLayout();
    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/assets/Back"));
    backButton->setIconSize(QSize(32, 32));
    firstRow->addWidget(backButton, 0, Qt::AlignLeft);


    //Second row
    QVBoxLayout *secondRow = new QVBoxLayout();
    secondRow->setAlignment(Qt::AlignCenter);
    //NAME
    QLabel *identifierLabel = new QLabel();
    if (!ptr) identifierLabel->setText("Insert Wallet identifier:");
    else identifierLabel->setText("Wallet identifier:");
    nameField = new QLineEdit();
    nameField->setEnabled(toEdit);
    if (ptr) nameField->setText(QString::fromStdString(*ptrCrypto));

    //Blockchain NAME
    QLabel *nameLabel = new QLabel();
    if (!ptr) nameLabel->setText("Insert Blockchain name here:");
    else nameLabel->setText("Blockchain name identifier:");
    blockchainNameField = new QLineEdit();
    blockchainNameField->setEnabled(toEdit);
    if (ptr) blockchainNameField->setText(QString::fromStdString(ptrCrypto->getBlockchainName()));

    //WORDS
}