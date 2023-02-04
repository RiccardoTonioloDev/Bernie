#include "SelectDBPage.h"
#include <QVBoxLayout>
#include <QPushButton>

SelectDBPage::SelectDBPage(std::vector<std::string> fN, QWidget *parent) : QWidget(parent) {
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
    QLabel *titleLabel = new QLabel("Select your encrypted database:");
    titleLabel->setAlignment(Qt::AlignCenter);
    noFiles = new QLabel("You never created a database. Please, create one first.");
    filesCombobox = new QComboBox();
    for (auto fn: fN)
        filesCombobox->addItem(QString::fromStdString(fn));
    selectButton = new QPushButton("Select DB");
    secondRow->addWidget(titleLabel);
    secondRow->addWidget(noFiles);
    secondRow->addWidget(filesCombobox);
    secondRow->addWidget(selectButton);
    secondRow->addStretch();

    if (fN.size() == 0) {
        noFiles->show();
        filesCombobox->hide();
        selectButton->hide();
    } else {
        noFiles->hide();
        filesCombobox->show();
        selectButton->show();
    }

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(secondRow);

    connect(backButton, &QPushButton::clicked, this, &SelectDBPage::returnLandingSlot);
}

void SelectDBPage::refreshNameList(std::vector<std::string> fN) {
    filesCombobox->clear();
    for (auto fn: fN)
        filesCombobox->addItem(QString::fromStdString(fn));
    if (fN.size() == 0) {
        noFiles->show();
        filesCombobox->hide();
        selectButton->hide();
    } else {
        noFiles->hide();
        filesCombobox->show();
        selectButton->show();
    }
}


void SelectDBPage::returnLandingSlot() {
    emit returnLandingSignal();
}
