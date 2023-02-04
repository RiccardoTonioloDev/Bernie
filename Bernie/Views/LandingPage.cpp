#include <QVBoxLayout>
#include <QLabel>


#include "LandingPage.h"

LandingPage::LandingPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignCenter);

    QLabel *titleLabel = new QLabel("Welcome!");
    titleLabel->setObjectName("landingPageTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    vbox->addWidget(titleLabel);

    QPushButton *select = new QPushButton("Select existing database");
    QPushButton *createNew = new QPushButton("Create new database");

    vbox->addWidget(select);
    vbox->addWidget(createNew);

    connect(select, &QPushButton::clicked, this, &LandingPage::switchSelectSlot);
    connect(createNew, &QPushButton::clicked, this, &LandingPage::switchCreateSlot);
}

void LandingPage::switchCreateSlot() {
    emit switchCreateSignal();
}

void LandingPage::switchSelectSlot() {
    emit switchSelectSignal();
}
