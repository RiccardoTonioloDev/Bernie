#include "HomePage.h"
#include <QVBoxLayout>
#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include "Visitors/VisitorListItem.h"
#include "Visitors/VisitorManageItem.h"
#include "Components/MenuButton.h"

HomePage::HomePage(Vault &v, QWidget *parent) : QWidget(parent), vault(v) {
    //Create outer layout
    QVBoxLayout *outerLayout = new QVBoxLayout(this);

    //FirstRow
    QHBoxLayout *upperRow = new QHBoxLayout;
    upperRow->setAlignment(Qt::AlignCenter);
    QPushButton *allButton = new QPushButton("All");
    allButton->setIcon(QIcon(":/assets/Home"));
    allButton->setIconSize(QSize(32, 32));

    searchBox = new QLineEdit();
    searchBox->setAlignment(Qt::AlignCenter);
    searchBox->setMinimumHeight(32);
    searchBox->setPlaceholderText("Search");
    searchBox->setObjectName("searchBox");
    QFont font = searchBox->font();
    font.setPointSize(15);
    searchBox->setFont(font);

    QPushButton *addButton = new QPushButton("Add");
    addButton->setIcon(QIcon(":/assets/Add"));
    addButton->setIconSize(QSize(32, 32));

    upperRow->addWidget(allButton);
    upperRow->addWidget(searchBox);
    upperRow->addWidget(addButton);

    //MiddleSpace
    listOfCards = new QListWidget();
    auto vectorSerializableObjects = vault.vectorize();
    for (auto so: vectorSerializableObjects) {
        VisitorListItem visitor;
        so->accept(&visitor);
        ListCardItem *cardLine = visitor.getWidget();
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 100));
        listOfCards->addItem(item);
        listOfCards->setItemWidget(item, cardLine);
        connect(cardLine, &ListCardItem::removeSignal, this, &HomePage::removeDataSlot);
        connect(cardLine, &ListCardItem::watchSignal, this, &HomePage::watchDataSlot);
        connect(cardLine, &ListCardItem::editSignal, this, &HomePage::editDataSlot);
    }

    //LowerRow
    QHBoxLayout *lowerRow = new QHBoxLayout();
    MenuButton *contactButton = new MenuButton("Contacts", ":/assets/Contacts");
    MenuButton *creditCardButton = new MenuButton("Credit Cards", ":/assets/CreditCards");
    MenuButton *accountButton = new MenuButton("Accounts", ":/assets/Account");
    MenuButton *cryptoButton = new MenuButton("Crypto Wallets", ":/assets/Crypto");
    MenuButton *noteButton = new MenuButton("Notes", ":/assets/Notes");

    lowerRow->addWidget(contactButton, 1);
    lowerRow->addWidget(creditCardButton, 1);
    lowerRow->addWidget(accountButton, 1);
    lowerRow->addWidget(cryptoButton, 1);
    lowerRow->addWidget(noteButton, 1);

    outerLayout->addLayout(upperRow);
    outerLayout->addWidget(listOfCards, 1);
    outerLayout->addLayout(lowerRow);

    connect(allButton, &QPushButton::clicked, this, &HomePage::filterAll);
    connect(contactButton, &MenuButton::clickedSignal, this, &HomePage::filterContacts);
    connect(creditCardButton, &MenuButton::clickedSignal, this, &HomePage::filterCreditCard);
    connect(accountButton, &MenuButton::clickedSignal, this, &HomePage::filterAccount);
    connect(cryptoButton, &MenuButton::clickedSignal, this, &HomePage::filterCrypto);
    connect(noteButton, &MenuButton::clickedSignal, this, &HomePage::filterNote);
    connect(allButton, &QPushButton::clicked, this, &HomePage::filterAll);
    connect(searchBox, &QLineEdit::textChanged, this, &HomePage::filterByName);
    connect(searchBox, &QLineEdit::returnPressed, this, &HomePage::returnPressed);
    connect(addButton, &QPushButton::clicked, this, &HomePage::addDataSlot);
}

void HomePage::addDataSlot() {
    emit addDataSignal();
    searchBox->setText("");
    searchBox->clearFocus();
}

void HomePage::changeByVector(const std::vector<const SerializableObject *> &vectorSerializableObjects) {
    listOfCards->clear();
    for (auto so: vectorSerializableObjects) {
        VisitorListItem visitor;
        so->accept(&visitor);
        ListCardItem *cardLine = visitor.getWidget();
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 100));
        listOfCards->addItem(item);
        listOfCards->setItemWidget(item, cardLine);
        connect(cardLine, &ListCardItem::removeSignal, this, &HomePage::removeDataSlot);
        connect(cardLine, &ListCardItem::watchSignal, this, &HomePage::watchDataSlot);
        connect(cardLine, &ListCardItem::editSignal, this, &HomePage::editDataSlot);
    }
}

void HomePage::refresh() {
    changeByVector(vault.vectorize());
}

void HomePage::filterAll() {
    searchBox->setText("");
    searchBox->clearFocus();
    refresh();
}

void HomePage::filterCreditCard() {
    changeByVector(vault.filteredVectorize<CreditCard>());
}

void HomePage::filterAccount() {
    changeByVector(vault.filteredVectorize<Account>());
}

void HomePage::filterContacts() {
    changeByVector(vault.filteredVectorize<Contact>());
}

void HomePage::filterNote() {
    changeByVector(vault.filteredVectorize<Note>());
}

void HomePage::filterCrypto() {
    changeByVector(vault.filteredVectorize<CryptoWallet>());
}

void HomePage::filterByName(const QString &name) {
    std::string upperName(name.toStdString());
    std::transform(upperName.begin(), upperName.end(), upperName.begin(), [](char &c) { return std::toupper(c); });
    changeByVector(vault.searchSerializableObjects(upperName));
}

void HomePage::returnPressed() {
    searchBox->clearFocus();
}

void HomePage::watchDataSlot(const SerializableObject *ptr) {
    VisitorManageItem visitor;
    ptr->accept(&visitor, false);
    emit createWatchPageSignal(visitor.getWidget());
    searchBox->setText("");
    searchBox->clearFocus();
}

void HomePage::editDataSlot(const SerializableObject *ptr) {
    VisitorManageItem visitor;
    ptr->accept(&visitor, true);
    emit createEditPageSignal(visitor.getWidget());
    searchBox->setText("");
    searchBox->clearFocus();
}

void HomePage::removeDataSlot(const SerializableObject *ptr) {
    if (ptr) {
        vault.deleteSerializableObject(*ptr);
        refresh();
    }
}
