#include "MainWindow.h"
#include <QDialog>
#include <QFile>
#include <QMenuBar>
#include <QAction>
#include "LandingPage.h"
#include "CreateDBPage.h"
#include "SelectDBPage.h"
#include "TypeSelectionPage.h"
#include "../Models/SerializableObject.h"
#include <QHBoxLayout>
#include <QTextEdit>
#include <algorithm>
#include <QMessageBox>

MainWindow::MainWindow(Vault &v, QWidget *parent) : vault(v), QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);
    LandingPage *lP = new LandingPage();
    CreateDBPage *cDBP = new CreateDBPage();
    sDBP = new SelectDBPage(vault.fetchDBNames());
    hp = new HomePage(vault);
    DBsp = new DBSelectedPage();
    TypeSelectionPage *Tsp = new TypeSelectionPage();
    sDBTR = new SelectDBToRemove(vault.fetchDBNames());
    DBstr = new DBSelectedToRemovePage();
    stackedWidget->addWidget(lP); //0
    stackedWidget->addWidget(cDBP); //1
    stackedWidget->addWidget(sDBP); //2
    stackedWidget->addWidget(hp); //3
    stackedWidget->addWidget(DBsp); //4
    stackedWidget->addWidget(Tsp); //5
    stackedWidget->addWidget(sDBTR); //6
    stackedWidget->addWidget(DBstr); //7


    QMenu *file = menuBar()->addMenu("&File");
    QAction *logoutAction = new QAction("Logout");
    QAction *manual = new QAction("Manual");
    QAction *decryptedFile = new QAction("See decrypted database");
    file->addAction(logoutAction);
    file->addAction(manual);
    file->addAction(decryptedFile);


    setCentralWidget(stackedWidget);

    connect(lP, &LandingPage::switchSelectSignal, this, &MainWindow::switchSelectSlot);
    connect(lP, &LandingPage::switchCreateSignal, this, &MainWindow::switchCreateSlot);
    connect(lP, &LandingPage::switchDeleteSignal, this, &MainWindow::switchDeleteSlot);
    connect(cDBP, &CreateDBPage::returnLandingSignal, this, &MainWindow::switchLendingSlot);
    connect(cDBP, &CreateDBPage::createDBSignal, this, &MainWindow::createDBAndSwitch);
    connect(sDBP, &SelectDBPage::returnLandingSignal, this, &MainWindow::switchLendingSlot);
    connect(sDBP, &SelectDBPage::dbSelectedSignal, this, &MainWindow::switchSelectedDBSlot);
    connect(DBsp, &DBSelectedPage::returnSelectDBSignal, this, &MainWindow::switchSelectSlot);
    connect(DBsp, &DBSelectedPage::decryptDBSignal, this, &MainWindow::readDBAndSwitch);
    connect(Tsp, &TypeSelectionPage::returnHomePageSignal, this, &MainWindow::switchHomePageSlot);
    connect(Tsp, &TypeSelectionPage::createCryptoWalletSignal, this, &MainWindow::createAddPage);
    connect(Tsp, &TypeSelectionPage::createNoteSignal, this, &MainWindow::createAddPage);
    connect(Tsp, &TypeSelectionPage::createAccountSignal, this, &MainWindow::createAddPage);
    connect(Tsp, &TypeSelectionPage::createCreditCardSignal, this, &MainWindow::createAddPage);
    connect(Tsp, &TypeSelectionPage::createContactSignal, this, &MainWindow::createAddPage);
    connect(hp, &HomePage::addDataSignal, this, &MainWindow::switchTypeSelectionSlot);
    connect(hp, &HomePage::createEditPageSignal, this, &MainWindow::createEditPage);
    connect(hp, &HomePage::createWatchPageSignal, this, &MainWindow::createWatchPage);
    connect(logoutAction, &QAction::triggered, this, &MainWindow::logoutSlot);
    connect(manual, &QAction::triggered, this, &MainWindow::manualSlot);
    connect(decryptedFile, &QAction::triggered, this, &MainWindow::decryptSlot);
    connect(sDBTR, &SelectDBToRemove::returnLandingSignal, this, &MainWindow::switchLendingSlot);
    connect(DBstr, &DBSelectedToRemovePage::returnSelectDBSignal, this, &MainWindow::switchSelectDBToRemoveSlot);
    connect(sDBTR, &SelectDBToRemove::dbSelectedToRemoveSignal, this, &MainWindow::switchDBSelectedToRemoveSlot);
    connect(DBstr, &DBSelectedToRemovePage::removeDBSignal, this, &MainWindow::removeDBSlot);
}

void MainWindow::logoutSlot() {
    if (vault.isInitialized()) {
        vault.reset();
        hp->refresh();
        stackedWidget->setCurrentIndex(0);
        return;
    }
    QDialog dialog;
    QLabel *dialogLabel = new QLabel("Please access a database first.");
    QHBoxLayout *dialogLayout = new QHBoxLayout;
    dialogLayout->addWidget(dialogLabel);
    dialog.setLayout(dialogLayout);
    dialog.exec();
}

void MainWindow::manualSlot() {
    QDialog dialog;
    QVBoxLayout *dialogLyt = new QVBoxLayout;
    dialog.setFixedSize(800, 600);
    QTextEdit *dialogTextArea = new QTextEdit();
    dialogTextArea->setReadOnly(true);
    dialogTextArea->setObjectName("Manual");
    dialogLyt->setAlignment(Qt::AlignCenter);
    QLabel *manualText = new QLabel("Application manual");
    manualText->setObjectName("landingPageTitle");

    QFile manual(":/assets/Manual");
    manual.open(QFile::ReadOnly);
    dialogTextArea->append(manual.readAll());

    dialogLyt->addWidget(manualText);
    dialogLyt->addWidget(dialogTextArea);
    dialog.setLayout(dialogLyt);
    dialog.exec();
}

void MainWindow::decryptSlot() {
    QDialog dialog;
    QHBoxLayout *dialogLyt = new QHBoxLayout;
    dialogLyt->setAlignment(Qt::AlignCenter);
    if (vault.isInitialized()) {
        dialog.setMinimumSize(1600, 600);
        QTextEdit *dialogTextArea = new QTextEdit();
        dialogTextArea->setReadOnly(true);
        std::vector<const SerializableObject *> v = vault.vectorize();
        for (auto cit = v.begin(); cit != v.end(); ++cit) {
            dialogTextArea->append(QString::fromStdString((*cit)->serialize()));
        }
        dialogLyt->addWidget(dialogTextArea);
    } else {
        QLabel *dialogLabel = new QLabel("Please first select a database in order to see its content.");
        dialogLyt->addWidget(dialogLabel);
    }
    dialog.setLayout(dialogLyt);
    dialog.exec();
}

void MainWindow::switchCreateSlot() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::switchDeleteSlot() {
    sDBTR->refreshNameList(vault.fetchDBNames());
    stackedWidget->setCurrentIndex(6);
}

void MainWindow::switchHomePageSlot() {
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::switchTypeSelectionSlot() {
    stackedWidget->setCurrentIndex(5);
}

void MainWindow::switchLendingSlot() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::switchSelectSlot() {
    sDBP->refreshNameList(vault.fetchDBNames());
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::createAddPage(PagesInterface *pageToAdd) {
    if (pageToAdd) {
        stackedWidget->addWidget(pageToAdd);
        connect(pageToAdd, &PagesInterface::addSerializableObjectSignal, this, &MainWindow::addSerializableObjectSlot);
        connect(pageToAdd, &PagesInterface::returnTypeSelectionPageSignal, this,
                &MainWindow::returnSelectionFromCreate);
        stackedWidget->setCurrentIndex(stackedWidget->count() - 1);
    }
}

void MainWindow::createEditPage(PagesInterface *pageToAdd) {
    if (pageToAdd) {
        stackedWidget->addWidget(pageToAdd);
        connect(pageToAdd, &PagesInterface::editSerializableObjectSignal, this,
                &MainWindow::editSerializableObjectSlot);
        connect(pageToAdd, &PagesInterface::returnTypeSelectionPageSignal, this,
                &MainWindow::returnSelectionFromCreate);
        stackedWidget->setCurrentIndex(stackedWidget->count() - 1);
    }
}

void MainWindow::createWatchPage(PagesInterface *pageToAdd) {
    if (pageToAdd) {
        stackedWidget->addWidget(pageToAdd);
        connect(pageToAdd, &PagesInterface::returnTypeSelectionPageSignal, this,
                &MainWindow::returnSelectionFromCreate);
        stackedWidget->setCurrentIndex(stackedWidget->count() - 1);
    }
}

void MainWindow::returnSelectionFromCreate() {
    stackedWidget->setCurrentIndex(3);
    QWidget * lastPage = stackedWidget->widget(stackedWidget->count() - 1);
    stackedWidget->removeWidget(lastPage);
    delete lastPage;
}

void MainWindow::addSerializableObjectSlot(const SerializableObject *ptr) {
    if (!vault.addSerializableObject(ptr)) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please, use an identifier that was never used before.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    hp->refresh();
    stackedWidget->setCurrentIndex(3);
    QWidget * lastPage = stackedWidget->widget(stackedWidget->count() - 1);
    stackedWidget->removeWidget(lastPage);
    delete lastPage;
}

void MainWindow::editSerializableObjectSlot(const SerializableObject *toEdit, const SerializableObject *Edited) {
    vault.modifyTreeObj(toEdit, Edited);
    hp->refresh();
    stackedWidget->setCurrentIndex(3);
    QWidget * lastPage = stackedWidget->widget(stackedWidget->count() - 1);
    stackedWidget->removeWidget(lastPage);
    delete lastPage;
}

void MainWindow::createDBAndSwitch(std::string name, std::string password) {
    auto fileNames = vault.fetchDBNames();
    if (fileNames.size() > 0 && std::find(fileNames.begin(), fileNames.end(), name + ".txt") != fileNames.end()) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel("Please, insert a name of a non existing database.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    vault.loadStorage(name + ".txt", password);
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::switchSelectedDBSlot(const std::string &name) {
    DBsp->setName(name);
    stackedWidget->setCurrentIndex(4);
}

void MainWindow::readDBAndSwitch(const std::string &name, const std::string &password) {
    bool isCorrect = vault.loadStorage(name + ".txt", password);
    if (isCorrect == false) {
        QDialog dialog;
        QLabel *dialogLabel = new QLabel(
                "Incorrect password or damaged database. If you know you inserted the correct password, the database is damaged.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    hp->refresh();
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::switchSelectDBToRemoveSlot() {
    sDBTR->refreshNameList(vault.fetchDBNames());
    stackedWidget->setCurrentIndex(6);
}

void MainWindow::switchDBSelectedToRemoveSlot(const std::string &name) {
    DBstr->setName(name);
    stackedWidget->setCurrentIndex(7);
}

void MainWindow::removeDBSlot(const std::string &name, const std::string &password) {
    QDialog dialog;
    QHBoxLayout *dialogLayout = new QHBoxLayout;
    if (!vault.loadStorage(name + ".txt", password)) {
        QLabel *dialogLabel = new QLabel("Invalid access credentials.");
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }

    QMessageBox reply;
    reply.setWindowTitle("ATTENTION");
    reply.setText(QString::fromStdString("Are you sure you want to delete " + name + " database?"));
    reply.addButton(QMessageBox::Yes);
    reply.addButton(QMessageBox::No);
    if (reply.exec() == QMessageBox::Yes) {
        vault.deleteDB(name + ".txt", password);
        QLabel *dialogLabel = new QLabel("Database removed correctly.");
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        stackedWidget->setCurrentIndex(0);
    }
}