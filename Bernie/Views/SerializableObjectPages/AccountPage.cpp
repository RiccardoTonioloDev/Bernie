#include "AccountPage.h"
#include <QVBoxLayout>
#include <QPushButton>
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

    connect(backButton, &QPushButton::clicked, this, &AccountPage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &AccountPage::manageSerializableObjectSlot);
}

void AccountPage::manageSerializableObjectSlot() {
    if (toEdit) emit editSerializableObjectSignal(objToManage, new Account(nameField->text().toStdString(),
                                                                           emailField->text().toStdString(),
                                                                           passwordField->text().toStdString(),
                                                                           usernameField->text().toStdString()));
}