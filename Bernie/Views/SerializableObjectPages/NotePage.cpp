#include "NotePage.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include "../../Models/Note.h"

NotePage::NotePage(const SerializableObject *ptr, bool toEdit, QWidget *parent) : PagesInterface(ptr, toEdit, parent){

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setAlignment(Qt::AlignCenter);
    const Note* ptrNote = nullptr;
    if(ptr) ptrNote = static_cast<const Note*>(ptr);

    //First row
    QHBoxLayout* firstRow = new QHBoxLayout();
    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/assets/Back"));
    backButton->setIconSize(QSize(32, 32));
    firstRow->addWidget(backButton, 0, Qt::AlignLeft);
    firstRow->addStretch();

    //second row
    //text field
    QLabel *nameLabel = new QLabel();
    if(!ptr) nameLabel->setText("Insert Note identifier:");
    else nameLabel->setText("Note identifier:");

    nameField = new QLineEdit();
    nameField->setEnabled(ptr == nullptr || toEdit);
    if(ptr) nameField->setText(QString::fromStdString(*ptrNote));

    QLabel *textLabel = new QLabel();
    if(!ptr) textLabel->setText("Insert text here:");
    else textLabel->setText("Text:");

    textField = new QTextEdit();
    textField->setEnabled(ptr == nullptr || toEdit);
    if(ptr) textField->setText(QString::fromStdString(ptrNote->getText()));

    //button create/edit
    QPushButton* manageButton = new QPushButton();
    if (!ptr) manageButton->setText("Create");
    else manageButton->setText("Update");
    manageButton->setVisible(toEdit || (ptr && toEdit));

    outerLayout->addLayout(firstRow);
    outerLayout->addWidget(nameLabel);
    outerLayout->addWidget(nameField);
    outerLayout->addWidget(textLabel);
    outerLayout->addWidget(textField);
    outerLayout->addWidget(manageButton);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &NotePage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &NotePage::manageSerializableObjectSlot);
}

void NotePage::manageSerializableObjectSlot() {
    if(nameField->text().isEmpty() || textField->toPlainText().isEmpty()){
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Name and Text field cannot be empty");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    if(toEdit){
        emit editSerializableObjectSignal(objToManage, new Note(nameField->text().toStdString(),
                                                                textField->toPlainText().toStdString()));
    }
    else emit addSerializableObjectSignal(new Note(nameField->text().toStdString(),
                       textField->toPlainText().toStdString()));
}