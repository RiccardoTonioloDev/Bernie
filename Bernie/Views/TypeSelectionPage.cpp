#include "TypeSelectionPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Components/TypeSelectionButton.h"
#include "SerializableObjectPages/AccountPage.h"
#include "SerializableObjectPages/CryptoWalletPage.h"

TypeSelectionPage::TypeSelectionPage(QWidget *parent) {
    QVBoxLayout *outerLayout = new QVBoxLayout(this);

    //First row
    QHBoxLayout *firstRow = new QHBoxLayout();
    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/assets/Back"));
    backButton->setIconSize(QSize(32, 32));
    firstRow->addWidget(backButton, 0, Qt::AlignLeft);

    //Second row
    QVBoxLayout *secondRow = new QVBoxLayout;
    secondRow->setAlignment(Qt::AlignCenter);
    QLabel *titleLabel = new QLabel("Select the type of data you want to add:");
    titleLabel->setAlignment(Qt::AlignCenter);
    TypeSelectionButton *accountButton = new TypeSelectionButton("Account", ":/assets/Account");
    TypeSelectionButton *contactButton = new TypeSelectionButton("Contact", ":/assets/Contacts");
    TypeSelectionButton *cryptoButton = new TypeSelectionButton("Crypto Wallet", ":/assets/Crypto");
    TypeSelectionButton *noteButton = new TypeSelectionButton("Note", ":/assets/Notes");
    TypeSelectionButton *creditCardButton = new TypeSelectionButton("Credit Card", ":/assets/CreditCards");

    secondRow->addWidget(accountButton);
    secondRow->addWidget(contactButton);
    secondRow->addWidget(cryptoButton);
    secondRow->addWidget(noteButton);
    secondRow->addWidget(creditCardButton);

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);
    outerLayout->addStretch();

    connect(accountButton, &TypeSelectionButton::clickedSignal, this, &TypeSelectionPage::createAccountSlot);
    connect(contactButton, &TypeSelectionButton::clickedSignal, this, &TypeSelectionPage::createContactSlot);
    connect(cryptoButton, &TypeSelectionButton::clickedSignal, this, &TypeSelectionPage::createCryptoWalletSlot);
    connect(noteButton, &TypeSelectionButton::clickedSignal, this, &TypeSelectionPage::createNoteSlot);
    connect(creditCardButton, &TypeSelectionButton::clickedSignal, this, &TypeSelectionPage::createCreditCardSlot);
    connect(backButton, &QPushButton::clicked, this, &TypeSelectionPage::returnHomePageSlot);
}

void TypeSelectionPage::createCreditCardSlot() {
    emit createCreditCardSignal(nullptr);
}

void TypeSelectionPage::createNoteSlot() {
    emit createNoteSignal(nullptr);
}

void TypeSelectionPage::createCryptoWalletSlot() {
    emit createCryptoWalletSignal(new CryptoWalletPage());

}

void TypeSelectionPage::createContactSlot() {
    emit createContactSignal(nullptr);

}

void TypeSelectionPage::createAccountSlot() {
    emit createAccountSignal(new AccountPage());
}

void TypeSelectionPage::returnHomePageSlot() {
    emit returnHomePageSignal();
}
