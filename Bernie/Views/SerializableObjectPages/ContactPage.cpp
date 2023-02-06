#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include "ContactPage.h"
ContactPage::ContactPage(const SerializableObject *ptr, bool toEdit, QWidget *parent) : PagesInterface(ptr, toEdit, parent) {

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    const Contact *ptrContact = nullptr;
    if (ptr) ptrContact = static_cast<const Contact *>(ptr);

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
    if (!ptr) identifierLabel->setText("Insert contact identifier:");
    else identifierLabel->setText("Contact identifier:");

    nameField = new QLineEdit();
    nameField->setEnabled(ptr == nullptr || toEdit);
    nameField->setMaxLength(50);
    nameField->setMaximumWidth(300);
    nameField->setMinimumHeight(25);
    nameField->setAlignment(Qt::AlignCenter);
    if (ptr) nameField->setText(QString::fromStdString(*ptrContact));

    //CONTACT NAME
    QLabel *contactNameLabel = new QLabel();
    if (!ptr) contactNameLabel->setText("Insert contact name:");
    else contactNameLabel->setText("Contact name:");

    contactNameField = new QLineEdit();
    contactNameField->setEnabled(ptr == nullptr || toEdit);
    contactNameField->setMaxLength(50);
    contactNameField->setMaximumWidth(300);
    contactNameField->setMinimumHeight(25);
    contactNameField->setAlignment(Qt::AlignCenter);
    if (ptr) contactNameField->setText(QString::fromStdString(ptrContact->getContactName()));

    //CONTACT NAME
    QLabel *contactSurnameLabel = new QLabel();
    if (!ptr) contactSurnameLabel->setText("Insert contact surname:");
    else contactSurnameLabel->setText("Contact surname:");

    contactSurnameField = new QLineEdit();
    contactSurnameField->setEnabled(ptr == nullptr || toEdit);
    contactSurnameField->setMaxLength(50);
    contactSurnameField->setMaximumWidth(300);
    contactSurnameField->setMinimumHeight(25);
    contactSurnameField->setAlignment(Qt::AlignCenter);
    if (ptr) contactSurnameField->setText(QString::fromStdString(ptrContact->getContactSurname()));

    //EMAIL
    QLabel *emailLabel = new QLabel();
    if (!ptr) emailLabel->setText("Insert Email here:");
    else emailLabel->setText("Email:");

    emailField = new QLineEdit();
    emailField->setEnabled(ptr == nullptr || toEdit);
    emailField->setMaxLength(50);
    emailField->setMaximumWidth(300);
    emailField->setMinimumHeight(25);
    emailField->setAlignment(Qt::AlignCenter);
    if (ptr) emailField->setText(QString::fromStdString(ptrContact->getMail()));

    //BIRTHDAY DATE
    QLabel *birthdayDateLabel = new QLabel();
    if (!ptr) birthdayDateLabel->setText("Insert contact birthday date here:");
    else birthdayDateLabel->setText("Contact birthday:");

    Date *birthdayDate = nullptr;
    if(ptr) birthdayDate = new Date(ptrContact->getBirthday());
    dateField = new DateComponent(birthdayDate, toEdit, 0);

    //third row
    QHBoxLayout *thirdRow = new QHBoxLayout();
    thirdRow->setAlignment(Qt::AlignHCenter);

    //layout for prefix
    QVBoxLayout *prefixBox = new QVBoxLayout();
    prefixBox->setAlignment(Qt::AlignCenter);
    //Prefix
    QLabel *prefixLabel = new QLabel();
    if (!ptr) prefixLabel->setText("Insert prefix here:");
    else prefixLabel->setText("Prefix:");

    prefixField = new QComboBox();
    if(ptr) prefixField->setCurrentText(QString::fromStdString(ptrContact->getTelephone().getPrefix()));
    prefixBox->addWidget(prefixLabel);
    prefixBox->addWidget(prefixField);

    //layout for number
    QVBoxLayout *numberBox = new QVBoxLayout();
    numberBox->setAlignment(Qt::AlignCenter);
    //NUMBER
    QLabel *numberLabel = new QLabel();
    if (!ptr) numberLabel->setText("Insert phone number here:");
    else numberLabel->setText("Phone number:");

    numberField = new QLineEdit();
    numberField->setMaxLength(50);
    numberField->setMaximumWidth(300);
    numberField->setMinimumHeight(25);
    numberField->setAlignment(Qt::AlignCenter);
    if(ptr) numberField->setText(QString::fromStdString(ptrContact->getTelephone().getNumberOnly()));
    numberBox->addWidget(numberLabel);
    numberBox->addWidget(numberField);

    QPushButton *manageButton = new QPushButton();
    if (!ptr) manageButton->setText("Create");
    else manageButton->setText("Update");
    manageButton->setVisible(ptr == nullptr || (ptr && toEdit));

    //LAYOUT
    secondRow->addWidget(identifierLabel);
    secondRow->addWidget(nameField);
    secondRow->addWidget(contactNameLabel);
    secondRow->addWidget(contactNameField);
    secondRow->addWidget(contactSurnameLabel);
    secondRow->addWidget(contactSurnameField);

    thirdRow->addLayout(prefixBox);
    thirdRow->addLayout(numberBox);

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);
    outerLayout->addWidget(birthdayDateLabel);
    outerLayout->addWidget(dateField);
    outerLayout->addLayout(thirdRow);
    outerLayout->addWidget(manageButton);

    connect(backButton, &QPushButton::clicked, this, &ContactPage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &ContactPage::manageSerializableObjectSlot);
}

void ContactPage::manageSerializableObjectSlot() {
    if(nameField->text().toStdString().size() == 0 ||
        contactNameField->text().toStdString().size() == 0 ||
        contactSurnameField->text().toStdString().size() == 0 ||
        emailField->text().toStdString().size() == 0 ||
        prefixField->currentText().toStdString().size() == 0 ||
        numberField->text().toStdString().size() == 0 ||
        !dateField->isValid()
        ){
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please contacts fields cannot be empty and the date has to be valid");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    std::string upperName(nameField->text().toStdString());
    std::transform(upperName.begin(), upperName.end(), upperName.begin(), [](char &c) { return std::toupper(c); });
    if (toEdit) emit editSerializableObjectSignal(objToManage, new Contact(upperName,
                                                                           contactNameField->text().toStdString(),
                                                                           contactSurnameField->text().toStdString(),
                                                                           *dateField->getDate(),
                                                                           Telephone(prefixField->currentText().toStdString() + " " + numberField->text().toStdString()),
                                                                           emailField->text().toStdString()));
    else emit addSerializableObjectSignal(new Contact(upperName,
                                                                   contactNameField->text().toStdString(),
                                                                   contactSurnameField->text().toStdString(),
                                                                   *dateField->getDate(),
                                                                   Telephone(prefixField->currentText().toStdString() + " " + numberField->text().toStdString()),
                                                                   emailField->text().toStdString()));

}