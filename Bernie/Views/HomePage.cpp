#include "HomePage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
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
    QPushButton *contactButton = new QPushButton("Contact");
    contactButton->setIcon(QIcon(":/assets/Contacts"));
    contactButton->setIconSize(QSize(20, 20));
    QPushButton *creditCardButton = new QPushButton("Credit Card");
    creditCardButton->setIcon(QIcon(":/assets/CreditCards"));
    creditCardButton->setIconSize(QSize(20, 20));
    QPushButton *accountButton = new QPushButton("Account");
    accountButton->setIcon(QIcon(":/assets/Account"));
    accountButton->setIconSize(QSize(20, 20));
    QPushButton *cryptoButton = new QPushButton("Crypto Wallet");
    cryptoButton->setIcon(QIcon(":/assets/Crypto"));
    cryptoButton->setIconSize(QSize(20, 20));
    QPushButton *noteButton = new QPushButton("Note");
    noteButton->setIcon(QIcon(":/assets/Notes"));
    noteButton->setIconSize(QSize(20, 20));

    lowerRow->addWidget(contactButton, 1);
    lowerRow->addWidget(creditCardButton, 1);
    lowerRow->addWidget(accountButton, 1);
    lowerRow->addWidget(cryptoButton, 1);
    lowerRow->addWidget(noteButton, 1);

    outerLayout->addLayout(upperRow);
    outerLayout->addWidget(listOfCards, 1);
    outerLayout->addLayout(lowerRow);
}