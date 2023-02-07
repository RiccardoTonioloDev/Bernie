#include "DBSelectedToRemovePage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>

DBSelectedToRemovePage::DBSelectedToRemovePage(QWidget *parent) : QWidget(parent) {
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
    QPushButton *removeButton = new QPushButton("Remove");
    secondRow->addWidget(namelbl);
    secondRow->addWidget(dbName);
    secondRow->addWidget(passwordlbl);
    secondRow->addWidget(dbPassword);
    secondRow->addWidget(removeButton);

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &DBSelectedToRemovePage::returnSelectDBSlot);
    connect(removeButton, &QPushButton::clicked, this, &DBSelectedToRemovePage::removeDBSlot);
    connect(dbPassword, &QLineEdit::returnPressed, this, &DBSelectedToRemovePage::removeDBSlot);
}

void DBSelectedToRemovePage::returnSelectDBSlot() {
    dbPassword->setText("");
    emit returnSelectDBSignal();
}

void DBSelectedToRemovePage::removeDBSlot() {
    if (dbPassword->text().toStdString().size() == 0) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please insert at least one char for the password.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    emit removeDBSignal(dbName->text().toStdString(), dbPassword->text().toStdString());
    dbPassword->setText("");
}

void DBSelectedToRemovePage::setName(const std::string &name) {
    dbName->setText(QString::fromStdString(name));
}