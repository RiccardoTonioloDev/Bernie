#include "MainWindow.h"
#include <QDialog>
#include "LandingPage.h"
#include "CreateDBPage.h"
#include "SelectDBPage.h"
#include "TypeSelectionPage.h"

#include <QHBoxLayout>
#include <algorithm>

MainWindow::MainWindow(Vault &v, QWidget *parent) : vault(v), QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);
    LandingPage *lP = new LandingPage();
    CreateDBPage *cDBP = new CreateDBPage();
    sDBP = new SelectDBPage(vault.fetchDBNames());
    hp = new HomePage(vault);
    DBsp = new DBSelectedPage();
    TypeSelectionPage *Tsp = new TypeSelectionPage();
    stackedWidget->addWidget(lP); //0
    stackedWidget->addWidget(cDBP); //1
    stackedWidget->addWidget(sDBP); //2
    stackedWidget->addWidget(hp); //3
    stackedWidget->addWidget(DBsp); //4
    stackedWidget->addWidget(Tsp); //5

    setCentralWidget(stackedWidget);

    connect(lP, &LandingPage::switchSelectSignal, this, &MainWindow::switchSelectSlot);
    connect(lP, &LandingPage::switchCreateSignal, this, &MainWindow::switchCreateSlot);
    connect(cDBP, &CreateDBPage::returnLandingSignal, this, &MainWindow::switchLendingSlot);
    connect(cDBP, &CreateDBPage::createDBSignal, this, &MainWindow::createDBAndSwitch);
    connect(sDBP, &SelectDBPage::returnLandingSignal, this, &MainWindow::switchLendingSlot);
    connect(sDBP, &SelectDBPage::dbSelectedSignal, this, &MainWindow::switchSelectedDBSlot);
    connect(DBsp, &DBSelectedPage::returnSelectDBSignal, this, &MainWindow::switchSelectSlot);
    connect(DBsp, &DBSelectedPage::decryptDBSignal, this, &MainWindow::readDBAndSwitch);
    connect(Tsp, &TypeSelectionPage::returnHomePageSignal, this, &MainWindow::switchHomePageSlot);
    connect(hp, &HomePage::addDataSignal, this, &MainWindow::switchTypeSelectionSlot);
}

void MainWindow::switchCreateSlot() {
    stackedWidget->setCurrentIndex(1);
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
        QLabel *dialogLabel = new QLabel("Incorrect password. Please retry with the correct password.");
        QHBoxLayout *dialogLayout = new QHBoxLayout;
        dialogLayout->addWidget(dialogLabel);
        dialog.setLayout(dialogLayout);
        dialog.exec();
        return;
    }
    hp->refresh();
    stackedWidget->setCurrentIndex(3);
}