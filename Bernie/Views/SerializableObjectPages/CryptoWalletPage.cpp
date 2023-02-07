#include "CryptoWalletPage.h"
#include <QVBoxLayout>
#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
#include <algorithm>
#include <QLabel>
#include "../../Models/CryptoWallet.h"

CryptoWalletPage::CryptoWalletPage(const SerializableObject *ptr, bool toEdit, QWidget *parent) : PagesInterface(ptr,
                                                                                                                 toEdit,
                                                                                                                 parent) {
    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    const CryptoWallet *ptrCrypto = nullptr;
    if (ptr) ptrCrypto = static_cast<const CryptoWallet *>(ptr);

    //First row
    QHBoxLayout *firstRow = new QHBoxLayout();
    QPushButton *backButton = new QPushButton();
    backButton->setIcon(QIcon(":/assets/Back"));
    backButton->setIconSize(QSize(32, 32));
    firstRow->addWidget(backButton, 0, Qt::AlignLeft);


    //Second row
    QVBoxLayout *middleRow = new QVBoxLayout();
    middleRow->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    //NAME
    QLabel *identifierLabel = new QLabel();
    if (!ptr) identifierLabel->setText("Insert Wallet identifier:");
    else identifierLabel->setText("Wallet identifier:");
    nameField = new QLineEdit();
    nameField->setEnabled(ptr == nullptr);
    nameField->setMaxLength(50);
    nameField->setMaximumWidth(300);
    nameField->setMinimumHeight(25);
    nameField->setAlignment(Qt::AlignCenter);
    if (ptr) nameField->setText(QString::fromStdString(*ptrCrypto));

    //Blockchain NAME
    QLabel *nameLabel = new QLabel();
    if (!ptr) nameLabel->setText("Insert Blockchain name here:");
    else nameLabel->setText("Blockchain name identifier:");
    blockchainNameField = new QLineEdit();
    blockchainNameField->setEnabled(ptr == nullptr || toEdit);
    blockchainNameField->setMaxLength(50);
    blockchainNameField->setMaximumWidth(300);
    blockchainNameField->setMinimumHeight(25);
    blockchainNameField->setAlignment(Qt::AlignCenter);
    if (ptr) blockchainNameField->setText(QString::fromStdString(ptrCrypto->getBlockchainName()));

    //WORDS
    QVBoxLayout *thirdRow = new QVBoxLayout();
    thirdRow->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    QLabel *wordsLabel = new QLabel("Insert wallet words here (empty if unused):");
    wordsLabel->setAlignment(Qt::AlignCenter);
    if (ptr)
        for (auto word: ptrCrypto->getWords()) {
            QLineEdit *wordEdit = new QLineEdit(QString::fromStdString(word));
            wordEdit->setMaxLength(50);
            wordEdit->setMaximumWidth(300);
            wordEdit->setMinimumHeight(25);
            words.push_back(wordEdit);
            wordEdit->setAlignment(Qt::AlignCenter);
        }
    else
        for (int i = 0; i < 24; ++i) {
            QLineEdit *wordEdit = new QLineEdit();
            wordEdit->setMaxLength(50);
            wordEdit->setMaximumWidth(300);
            wordEdit->setMinimumHeight(25);
            words.push_back(wordEdit);
            wordEdit->setAlignment(Qt::AlignCenter);
        }
    if (ptr && !toEdit) for (auto ptrQLineEdit: words) ptrQLineEdit->setEnabled(false);

    QGridLayout * wordsLayout = new QGridLayout();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 6; ++j) {
            QVBoxLayout *wordBox = new QVBoxLayout();
            std::string insideLabel = "" + std::to_string((i * 5) + i + j + 1) + ".";
            QLabel *wordLabel = new QLabel(QString::fromStdString(insideLabel));
            wordBox->setAlignment(Qt::AlignLeft);
            wordBox->addWidget(wordLabel);
            wordBox->addWidget(words[(i * 5) + i + j]);
            wordsLayout->addLayout(wordBox, i, j);
        }
    }

    QPushButton *manageButton = new QPushButton();
    if (!ptr) manageButton->setText("Create");
    else manageButton->setText("Update");
    manageButton->setVisible(ptr == nullptr || toEdit);

    middleRow->addWidget(identifierLabel);
    middleRow->addWidget(nameField);
    middleRow->addWidget(nameLabel);
    middleRow->addWidget(blockchainNameField);
    thirdRow->addWidget(wordsLabel);
    thirdRow->addLayout(wordsLayout);
    thirdRow->addWidget(manageButton);

    outerLayout->addLayout(firstRow);
    outerLayout->addLayout(middleRow);
    outerLayout->addLayout(thirdRow);
    outerLayout->addStretch();

    connect(backButton, &QPushButton::clicked, this, &CryptoWalletPage::returnTypeSelectionPageSlot);
    connect(manageButton, &QPushButton::clicked, this, &CryptoWalletPage::manageSerializableObjectSlot);
}

void CryptoWalletPage::manageSerializableObjectSlot() {
    if ((nameField->text().toStdString().size() == 0 ||
         blockchainNameField->text().toStdString().size() == 0) && (objToManage == nullptr || toEdit)) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please insert at least the identifier and the blockchain name.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    std::string upperName(nameField->text().toStdString());
    std::transform(upperName.begin(), upperName.end(), upperName.begin(), [](char &c) { return std::toupper(c); });
    std::vector<std::string> wordsSaved;
    for (auto word: words) wordsSaved.push_back(word->text().toStdString());
    if (objToManage && toEdit) {
        emit editSerializableObjectSignal(objToManage, new CryptoWallet(upperName,
                                                                        blockchainNameField->text().toStdString(),
                                                                        wordsSaved));
    } else {
        emit addSerializableObjectSignal(new CryptoWallet(upperName,
                                                          blockchainNameField->text().toStdString(),
                                                          wordsSaved));
    }
}