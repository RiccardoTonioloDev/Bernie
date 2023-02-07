#include "NotePage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include "../../Models/Note.h"

NotePage::NotePage(const SerializableObject *ptr, bool toEdit, QWidget *parent) : PagesInterface(ptr, toEdit, parent) {

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setAlignment(Qt::AlignCenter);
    const Note *ptrNote = nullptr;
    if (ptr) ptrNote = static_cast<const Note *>(ptr);

    //First row
    QHBoxLayout *firstRow = new QHBoxLayout();
    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/assets/Back"));
    backButton->setIconSize(QSize(32, 32));
    firstRow->addWidget(backButton, 0, Qt::AlignLeft);
    firstRow->addStretch();

    //second row
    //text field
    QVBoxLayout *secondRow = new QVBoxLayout;
    secondRow->setAlignment(Qt::AlignCenter);
    QLabel *nameLabel = new QLabel();
    if (!ptr) nameLabel->setText("Insert Note identifier:");
    else nameLabel->setText("Note identifier:");

    nameField = new QLineEdit();
    nameField->setEnabled(ptr == nullptr);
    nameField->setMaxLength(50);
    nameField->setMaximumWidth(300);
    nameField->setMinimumHeight(25);
    nameField->setAlignment(Qt::AlignCenter);
    if (ptr) nameField->setText(QString::fromStdString(*ptrNote));

    //third row
    QHBoxLayout *thirdRow = new QHBoxLayout;
    thirdRow->setAlignment(Qt::AlignCenter);
    //textBox
    QVBoxLayout *textAreaBox = new QVBoxLayout;
    textAreaBox->setAlignment(Qt::AlignCenter);
    QLabel *textLabel = new QLabel();
    if (!ptr) textLabel->setText("Insert text here:");
    else textLabel->setText("Text:");

    textField = new QTextEdit();
    textField->setEnabled(ptr == nullptr || toEdit);
    if (ptr) textField->setText(QString::fromStdString(ptrNote->getText()));
    textField->setFixedWidth(400);
    textAreaBox->addWidget(textLabel);
    textAreaBox->addWidget(textField);

    //fourth row
    QHBoxLayout *fourthRow = new QHBoxLayout;
    fourthRow->setAlignment(Qt::AlignCenter);
    //button create/edit
    QPushButton *manageButton = new QPushButton();
    if (!ptr) manageButton->setText("Create");
    else manageButton->setText("Update");
    manageButton->setVisible(ptr == nullptr || toEdit);

    secondRow->addWidget(nameLabel);
    secondRow->addWidget(nameField);
    thirdRow->addStretch();
    thirdRow->addLayout(textAreaBox);
    thirdRow->addStretch();
    fourthRow->addWidget(manageButton);

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);
    outerLayout->addLayout(thirdRow);
    outerLayout->addLayout(fourthRow);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &NotePage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &NotePage::manageSerializableObjectSlot);
}

void NotePage::manageSerializableObjectSlot() {
    if (nameField->text().isEmpty() || textField->toPlainText().isEmpty()) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Name and Text field cannot be empty");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    if (toEdit) {
        emit editSerializableObjectSignal(objToManage, new Note(nameField->text().toStdString(),
                                                                textField->toPlainText().toStdString()));
    } else emit addSerializableObjectSignal(new Note(nameField->text().toStdString(),
                                                     textField->toPlainText().toStdString()));
}