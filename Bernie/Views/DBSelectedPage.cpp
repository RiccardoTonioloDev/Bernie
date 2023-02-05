#include "DBSelectedPage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

DBSelectedPage::DBSelectedPage(QWidget *parent) : QWidget(parent) {
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
    QLabel *namelbl = new QLabel("Database name:");
    dbName = new QLineEdit();
    dbName->setMaxLength(50);
    dbName->setMaximumWidth(300);
    dbName->setMinimumHeight(25);
    dbName->setDisabled(true);
    QLabel *passwordlbl = new QLabel("Insert database password:");
    dbPassword = new QLineEdit();
    dbPassword->setMaxLength(50);
    dbPassword->setMaximumWidth(300);
    dbPassword->setMinimumHeight(25);
    dbPassword->setEchoMode(QLineEdit::Password);
    dbName->setAlignment(Qt::AlignCenter);
    dbPassword->setAlignment(Qt::AlignCenter);
    QPushButton *decryptButton = new QPushButton("Decrypt");
    secondRow->addWidget(namelbl);
    secondRow->addWidget(dbName);
    secondRow->addWidget(passwordlbl);
    secondRow->addWidget(dbPassword);
    secondRow->addWidget(decryptButton);

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &DBSelectedPage::returnSelectDBSlot);
    connect(decryptButton, &QPushButton::clicked, this, &DBSelectedPage::decryptDBSlot);
}

void DBSelectedPage::returnSelectDBSlot() {
    dbPassword->setText("");
    emit returnSelectDBSignal();
}

void DBSelectedPage::decryptDBSlot() {
    emit decryptDBSignal(dbName->text().toStdString(), dbPassword->text().toStdString());
}

void DBSelectedPage::setName(const std::string &name) {
    dbName->setText(QString::fromStdString(name));
}