#include <QVBoxLayout>
#include <QLabel>


#include "LandingPage.h"

LandingPage::LandingPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignCenter);

    QLabel *appIcon = new QLabel();
    appIcon->setAlignment(Qt::AlignCenter);
    appIcon->setPixmap(QIcon(":/assets/App_Icon").pixmap(192, 192));
    vbox->addWidget(appIcon);
    QLabel *titleLabel = new QLabel("Welcome to Bernie, your secure data storage!");
    titleLabel->setObjectName("landingPageTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    vbox->addWidget(titleLabel);

    QPushButton *select = new QPushButton("Select existing database");
    QPushButton *createNew = new QPushButton("Create new database");
    QPushButton *deleteDb = new QPushButton("Delete existing database");

    vbox->addWidget(select);
    vbox->addWidget(createNew);
    vbox->addWidget(deleteDb);

    connect(select, &QPushButton::clicked, this, &LandingPage::switchSelectSlot);
    connect(createNew, &QPushButton::clicked, this, &LandingPage::switchCreateSlot);
    connect(deleteDb, &QPushButton::clicked, this, &LandingPage::switchDeleteSlot);
}

void LandingPage::switchCreateSlot() {
    emit switchCreateSignal();
}

void LandingPage::switchSelectSlot() {
    emit switchSelectSignal();
}

void LandingPage::switchDeleteSlot() {
    emit switchDeleteSignal();
}
