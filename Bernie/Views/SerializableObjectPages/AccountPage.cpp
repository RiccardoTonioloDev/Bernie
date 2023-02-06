#include "AccountPage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include "../../Models/Account.h"

AccountPage::AccountPage(const SerializableObject *ptr, bool toEdit, QWidget *parent) : PagesInterface(ptr, toEdit,
                                                                                                       parent) {
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    const Account *ptrAccount = nullptr;
    if (ptr) ptrAccount = static_cast<const Account *>(ptr);

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
    if (!ptr) identifierLabel->setText("Insert Account identifier:");
    else identifierLabel->setText("Account identifier:");

    nameField = new QLineEdit();
    nameField->setEnabled(toEdit);
    if (ptr) nameField->setText(QString::fromStdString(*ptrAccount));

    //EMAIL
    QLabel *emailLabel = new QLabel();
    if (!ptr) identifierLabel->setText("Insert Email here:");
    else identifierLabel->setText("Email:");

    emailField = new QLineEdit();
    emailField->setEnabled(toEdit);
    if (ptr) emailField->setText(QString::fromStdString(ptrAccount->getEmail()));
    secondRow->addWidget(identifierLabel);
    secondRow->addWidget(nameField);
    secondRow->addWidget(emailLabel);
    secondRow->addWidget(emailField);

    //USERNAME
    QLabel *usernameLabel = new QLabel();
    if (!ptr) usernameLabel->setText("Insert Username here:");
    else usernameLabel->setText("Username:");

    usernameField = new QLineEdit();
    usernameField->setEnabled(toEdit);
    if (ptr) emailField->setText(QString::fromStdString(ptrAccount->getUsername()));

    //Password
    QLabel *passwordLabel = new QLabel();
    if (!ptr) passwordLabel->setText("Insert Password here:");
    else passwordLabel->setText("Password:");

    passwordField = new QLineEdit();
    passwordField->setEnabled(toEdit);
    if (ptr) passwordField->setText(QString::fromStdString(ptrAccount->getPassword()));

    QPushButton *manageButton = new QPushButton();
    if (!ptr) manageButton->setText("Create");
    else manageButton->setText("Update");
    manageButton->setVisible(ptr == nullptr || (ptr && toEdit));

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &AccountPage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &AccountPage::manageSerializableObjectSlot);
}

void AccountPage::manageSerializableObjectSlot() {
    if ((nameField->text().toStdString().size() == 0 ||
         passwordField->text().toStdString().size() == 0) && (objToManage == nullptr || toEdit)) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please insert at least the email and the password.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();

    }
    if (toEdit) emit editSerializableObjectSignal(objToManage, new Account(nameField->text().toStdString(),
                                                                           emailField->text().toStdString(),
                                                                           passwordField->text().toStdString(),
                                                                           usernameField->text().toStdString()));
    else emit new Account(nameField->text().toStdString(),
                          emailField->text().toStdString(),
                          passwordField->text().toStdString(),
                          usernameField->text().toStdString());
}