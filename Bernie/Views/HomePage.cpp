#include "HomePage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include "Visitors/VisitorListItem.h"

HomePage::HomePage(Vault &v, QWidget *parent) : vault(v), QWidget(parent) {
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
    searchBox->setPlaceholderText("Search");

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
        QWidget *cardLine = visitor.getWidget();
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 100));
        listOfCards->addItem(item);
        listOfCards->setItemWidget(item, cardLine);
    }

    //LowerRow
    QHBoxLayout *lowerRow = new QHBoxLayout();
    //Contact - COMPLETAMENTE FUNZIONANTE
    QVBoxLayout *lytContact = new QVBoxLayout();
    lytContact->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QPushButton *contactButton = new QPushButton();
    contactButton->setMinimumHeight(70);
    QLabel *iconContact = new QLabel();
    iconContact->setPixmap(QIcon(":/assets/Contacts").pixmap(30, 30));
    iconContact->setAlignment(Qt::AlignCenter);
    lytContact->addWidget(iconContact);
    lytContact->addWidget(new QLabel("Contact"));
    contactButton->setLayout(lytContact);

    //CreditCard
    QVBoxLayout *lytCredit = new QVBoxLayout();
    QPushButton *creditCardButton = new QPushButton();
    QLabel *iconCredit = new QLabel();
    iconCredit->setPixmap(QIcon(":/assets/CreditCards").pixmap(30, 30));
    lytCredit->addWidget(iconCredit);
    lytCredit->addWidget(new QLabel("Credit Card"));
    creditCardButton->setLayout(lytCredit);

    //Account
    QVBoxLayout *lytAccount = new QVBoxLayout();
    QPushButton *accountButton = new QPushButton();
    QLabel *iconAccount = new QLabel();
    iconAccount->setPixmap(QIcon(":/assets/Account").pixmap(30, 30));
    lytAccount->addWidget(iconAccount);
    lytAccount->addWidget(new QLabel("Account"));
    accountButton->setLayout(lytCredit);

    //Crypto
    QVBoxLayout *lytCrypto = new QVBoxLayout();
    QPushButton *cryptoButton = new QPushButton();
    QLabel *iconCrypto = new QLabel();
    iconCrypto->setPixmap(QIcon(":/assets/Crypto").pixmap(30, 30));
    lytCrypto->addWidget(iconCrypto);
    lytCrypto->addWidget(new QLabel("Crypto Wallet"));
    cryptoButton->setLayout(lytCrypto);

    //Note
    QVBoxLayout *lytNote = new QVBoxLayout();
    QPushButton *noteButton = new QPushButton();
    QLabel *iconNote = new QLabel();
    iconNote->setPixmap(QIcon(":/assets/Notes").pixmap(30, 30));
    lytNote->addWidget(iconNote);
    lytNote->addWidget(new QLabel("Note"));
    noteButton->setLayout(lytCrypto);

    lowerRow->addWidget(contactButton, 1);
    lowerRow->addWidget(creditCardButton, 1);
    lowerRow->addWidget(accountButton, 1);
    lowerRow->addWidget(cryptoButton, 1);
    lowerRow->addWidget(noteButton, 1);

    outerLayout->addLayout(upperRow);
    outerLayout->addWidget(listOfCards, 1);
    outerLayout->addLayout(lowerRow);
}

void HomePage::refresh() {
    listOfCards->clear();
    auto vectorSerializableObjects = vault.vectorize();
    for (auto so: vectorSerializableObjects) {
        VisitorListItem visitor;
        so->accept(&visitor);
        QWidget *cardLine = visitor.getWidget();
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(0, 100));
        listOfCards->addItem(item);
        listOfCards->setItemWidget(item, cardLine);
    }
}