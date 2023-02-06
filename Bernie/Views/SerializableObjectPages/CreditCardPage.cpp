#include "CreditCardPage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include "../../Models/CreditCard.h"


CreditCardPage::CreditCardPage(const SerializableObject *ptr, bool toEdit, QWidget *parent) : PagesInterface(ptr,
                                                                                                             toEdit,
                                                                                                             parent) {

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setAlignment(Qt::AlignHCenter);
    const CreditCard *ptrCreditCard = nullptr;
    if (ptr) ptrCreditCard = static_cast<const CreditCard *>(ptr);

    //First row
    QHBoxLayout *firstRow = new QHBoxLayout();
    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/assets/Back"));
    backButton->setIconSize(QSize(32, 32));
    firstRow->addWidget(backButton, 0, Qt::AlignLeft);
    firstRow->addStretch();

    //Second row
    //NAME
    QLabel *nameLabel = new QLabel();
    if (!ptr) nameLabel->setText("Insert credit card identifier:");
    else nameLabel->setText("Credit card identifier:");

    nameField = new QLineEdit();
    nameField->setEnabled(ptr == nullptr || toEdit);
    nameField->setMaxLength(50);
    nameField->setMaximumWidth(300);
    nameField->setMinimumHeight(25);
    nameField->setAlignment(Qt::AlignCenter);
    if (ptr) nameField->setText(QString::fromStdString(*ptrCreditCard));

    //OWNER
    QLabel *ownerLabel = new QLabel();
    if (!ptr) ownerLabel->setText("Insert the owner:");
    else ownerLabel->setText("Owner:");

    ownerField = new QLineEdit();
    ownerField->setEnabled(ptr == nullptr || toEdit);
    ownerField->setMaxLength(50);
    ownerField->setMaximumWidth(300);
    ownerField->setMinimumHeight(25);
    ownerField->setAlignment(Qt::AlignCenter);
    if (ptr) ownerField->setText(QString::fromStdString(ptrCreditCard->getOwner()));

    //NUMBER
    QLabel *numberLabel = new QLabel();
    if (!ptr) numberLabel->setText("Insert credit card number:");
    else numberLabel->setText("Credit card number:");

    numberField = new QLineEdit();
    numberField->setEnabled(ptr == nullptr || toEdit);
    //numberField->setInputMask("9999 9999 9999 9999");
    QRegularExpression numberRx("[0-9]\\d{0,16}");
    QValidator *numberValidator = new QRegularExpressionValidator(numberRx, this);
    numberField->setValidator(numberValidator);
    numberField->setMaxLength(50);
    numberField->setMaximumWidth(300);
    numberField->setMinimumHeight(25);
    numberField->setAlignment(Qt::AlignCenter);
    if (ptr) numberField->setText(QString::fromStdString(ptrCreditCard->getNumber()));

    //CVV
    QLabel *cvvLabel = new QLabel();
    if (!ptr) cvvLabel->setText("Insert cvv:");
    else cvvLabel->setText("Cvv:");

    cvvField = new QLineEdit();
    cvvField->setEnabled(ptr == nullptr || toEdit);
    //cvvField->setInputMask("999");
    QRegularExpression cvvRx("[0-9]\\d{0,3}");
    QValidator *cvvValidator = new QRegularExpressionValidator(cvvRx, this);
    cvvField->setValidator(cvvValidator);
    cvvField->setCursorPosition(0);
    cvvField->setText("");
    cvvField->setMaxLength(50);
    cvvField->setMaximumWidth(300);
    cvvField->setMinimumHeight(25);
    cvvField->setAlignment(Qt::AlignCenter);
    if (ptr) cvvField->setText(QString::fromStdString(ptrCreditCard->getCvv()));

    //DATE
    QLabel *dateLabel = new QLabel();
    if (!ptr) dateLabel->setText("Set expire date:");
    else dateLabel->setText("Expire date:");

    Date *date = nullptr;
    if (ptrCreditCard) date = new Date(ptrCreditCard->getDate());
    dateField = new DateComponent(date, ptr == nullptr || toEdit, 0);

    //BUTTON
    QPushButton *manageButton = new QPushButton();
    if (!ptr) manageButton->setText("Create");
    else manageButton->setText("Update");
    manageButton->setVisible(ptr == nullptr || (ptr && toEdit));

    //LAYOUT
    outerLayout->addLayout(firstRow);
    outerLayout->addWidget(nameLabel);
    outerLayout->addWidget(nameField);
    outerLayout->addWidget(ownerLabel);
    outerLayout->addWidget(ownerField);
    outerLayout->addWidget(numberLabel);
    outerLayout->addWidget(numberField);
    outerLayout->addWidget(cvvLabel);
    outerLayout->addWidget(cvvField);
    outerLayout->addWidget(dateLabel);
    outerLayout->addWidget(dateField);
    outerLayout->addWidget(manageButton);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &CreditCardPage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &CreditCardPage::manageSerializableObjectSlot);
}

void CreditCardPage::manageSerializableObjectSlot() {
    if (nameField->text().isEmpty() || numberField->text().isEmpty() || cvvField->text().isEmpty() ||
        !dateField->isValid()) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please insert an identifier, a card number, a cvv and a valid date");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    if (toEdit) emit editSerializableObjectSignal(objToManage, new CreditCard(nameField->text().toStdString(),
                                                                              ownerField->text().toStdString(),
                                                                              numberField->text().toStdString(),
                                                                              cvvField->text().toStdString(),
                                                                              *(dateField->getDate())));
    else emit addSerializableObjectSignal(new CreditCard(nameField->text().toStdString(),
                                                         ownerField->text().toStdString(),
                                                         numberField->text().toStdString(),
                                                         cvvField->text().toStdString(),
                                                         *(dateField->getDate())));
}