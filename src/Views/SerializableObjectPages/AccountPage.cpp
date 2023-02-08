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
    nameField->setEnabled(ptr == nullptr);
    nameField->setMaxLength(50);
    nameField->setMaximumWidth(300);
    nameField->setMinimumHeight(25);
    nameField->setAlignment(Qt::AlignCenter);
    if (ptr) nameField->setText(QString::fromStdString(*ptrAccount));

    //EMAIL
    QLabel *emailLabel = new QLabel();
    if (!ptr) emailLabel->setText("Insert Email here:");
    else emailLabel->setText("Email:");

    emailField = new QLineEdit();
    emailField->setReadOnly(ptr && !toEdit);
    emailField->setMaxLength(50);
    emailField->setMaximumWidth(300);
    emailField->setMinimumHeight(25);
    emailField->setAlignment(Qt::AlignCenter);
    if (ptr) emailField->setText(QString::fromStdString(ptrAccount->getEmail()));

    //USERNAME
    QLabel *usernameLabel = new QLabel();
    if (!ptr) usernameLabel->setText("Insert Username here:");
    else usernameLabel->setText("Username:");

    usernameField = new QLineEdit();
    usernameField->setReadOnly(ptr && !toEdit);
    usernameField->setMaxLength(50);
    usernameField->setMaximumWidth(300);
    usernameField->setMinimumHeight(25);
    usernameField->setAlignment(Qt::AlignCenter);
    if (ptr) usernameField->setText(QString::fromStdString(ptrAccount->getUsername()));

    //Password
    QLabel *passwordLabel = new QLabel();
    if (!ptr) passwordLabel->setText("Insert Password here:");
    else passwordLabel->setText("Password:");

    passwordField = new QLineEdit();
    passwordField->setReadOnly(ptr && !toEdit);
    passwordField->setMaxLength(50);
    passwordField->setMaximumWidth(300);
    passwordField->setMinimumHeight(25);
    passwordField->setAlignment(Qt::AlignCenter);
    if (ptr) passwordField->setText(QString::fromStdString(ptrAccount->getPassword()));

    QPushButton *manageButton = new QPushButton();
    if (!ptr) manageButton->setText("Create");
    else manageButton->setText("Update");
    manageButton->setVisible(ptr == nullptr || (ptr && toEdit));

    //Populating second row
    secondRow->addWidget(identifierLabel);
    secondRow->addWidget(nameField);
    secondRow->addWidget(emailLabel);
    secondRow->addWidget(emailField);
    secondRow->addWidget(usernameLabel);
    secondRow->addWidget(usernameField);
    secondRow->addWidget(passwordLabel);
    secondRow->addWidget(passwordField);
    secondRow->addWidget(manageButton);


    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &AccountPage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &AccountPage::manageSerializableObjectSlot);
}

void AccountPage::manageSerializableObjectSlot() {
    if ((nameField->text().toStdString().size() == 0 ||
         emailField->text().toStdString().size() == 0 ||
         passwordField->text().toStdString().size() == 0) && (objToManage == nullptr || toEdit)) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please insert at least the identifier, the email and the password.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    std::string upperName(nameField->text().toStdString());
    std::transform(upperName.begin(), upperName.end(), upperName.begin(), [](char &c) { return std::toupper(c); });
    if (toEdit) emit editSerializableObjectSignal(objToManage, new Account(upperName,
                                                                           emailField->text().toStdString(),
                                                                           passwordField->text().toStdString(),
                                                                           usernameField->text().toStdString()));
    else emit addSerializableObjectSignal(new Account(upperName,
                                                      emailField->text().toStdString(),
                                                      passwordField->text().toStdString(),
                                                      usernameField->text().toStdString()));
}