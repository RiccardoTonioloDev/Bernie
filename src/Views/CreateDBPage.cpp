#include "CreateDBPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

CreateDBPage::CreateDBPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *outerLayout = new QVBoxLayout(this);

    //First row
    QHBoxLayout *firstRow = new QHBoxLayout();
    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/assets/Back"));
    backButton->setIconSize(QSize(32, 32));
    firstRow->addWidget(backButton, 0, Qt::AlignLeft);

    //Second row
    QVBoxLayout *secondRow = new QVBoxLayout();
    secondRow->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QLabel *lbName = new QLabel("Insert database name:");
    name = new QLineEdit();
    name->setMaxLength(50);
    name->setMaximumWidth(300);
    name->setMinimumHeight(25);
    QLabel *nameDisclamer = new QLabel(
            "NOTE: don't use the following list of chars in the name. \nList: /,\\,:,*,?,\",<,>,|,#,%,&.");
    nameDisclamer->setMaximumWidth(300);
    QFont font = nameDisclamer->font();
    font.setPointSize(11);
    nameDisclamer->setFont(font);
    nameDisclamer->setMaximumWidth(300);
    nameDisclamer->setWordWrap(true);
    QLabel *lbPassword1 = new QLabel("Insert database password:");
    password1 = new QLineEdit();
    password1->setMaxLength(50);
    password1->setMaximumWidth(300);
    password1->setMinimumHeight(25);
    QLabel *lbPassword2 = new QLabel("Confirm database password:");
    password2 = new QLineEdit();
    password2->setMaxLength(50);
    password2->setMaximumWidth(300);
    password2->setMinimumHeight(25);
    QPushButton *createButton = new QPushButton("Create");
    name->setAlignment(Qt::AlignCenter);
    password1->setAlignment(Qt::AlignCenter);
    password2->setAlignment(Qt::AlignCenter);
    secondRow->addWidget(lbName);
    secondRow->addWidget(name);
    secondRow->addWidget(nameDisclamer);
    secondRow->addWidget(lbPassword1);
    secondRow->addWidget(password1);
    secondRow->addWidget(lbPassword2);
    secondRow->addWidget(password2);
    secondRow->addWidget(createButton);
    secondRow->addStretch(1);

    //Combining different layouts
    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);

    connect(backButton, &QPushButton::clicked, this, &CreateDBPage::returnLandingSlot);
    connect(createButton, &QPushButton::clicked, this, &CreateDBPage::createDBSlot);
}

void CreateDBPage::resetFields() {
    name->setText("");
    password1->setText("");
    password2->setText("");
}

void CreateDBPage::spawnAlertDialog(std::string text) const {
    QDialog dialog;
    QLabel *dialogLabel = new QLabel(QString::fromStdString(text));
    QHBoxLayout *dialogLayout = new QHBoxLayout;
    dialogLayout->addWidget(dialogLabel);
    dialog.setLayout(dialogLayout);
    dialog.exec();
}

void CreateDBPage::createDBSlot() {
    std::string textName = name->text().trimmed().toStdString();
    std::string filteredTextName("");
    for (auto ch: textName)
        if (ch != '/' && ch != '\\' && ch != ':' && ch != '*' && ch != '?' && ch != '"' && ch != '<' && ch != '>' &&
            ch != '|' && ch != '#' && ch != '%' && ch != '&')
            filteredTextName.push_back(ch);
    if (textName.size() == 0) {
        spawnAlertDialog("Please, the name can't be empty.");
        return;
    } else if (textName.size() != filteredTextName.size()) {
        spawnAlertDialog("Please, input only valid character for the database name.");
        return;
    } else if (password1->text() != password2->text()) {
        spawnAlertDialog("The two passwords are not equal. Please confirm using the same password.");
        return;
    } else if (password1->text().toStdString().size() == 0) {
        spawnAlertDialog("Please, the password can't be empty.");
        return;
    }
    emit createDBSignal(name->text().toStdString(), password1->text().toStdString());
    resetFields();
}

void CreateDBPage::returnLandingSlot() {
    resetFields();
    emit returnLandingSignal();
}