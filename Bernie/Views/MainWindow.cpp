#include "MainWindow.h"
#include <QDialog>
#include "LandingPage.h"
#include "CreateDBPage.h"
#include <QHBoxLayout>
#include <algorithm>

MainWindow::MainWindow(Vault &v, QWidget *parent) : vault(v), QMainWindow(parent) {
    stackedWidget = new QStackedWidget(this);
    LandingPage *lP = new LandingPage();
    CreateDBPage *cDBP = new CreateDBPage();
    stackedWidget->addWidget(lP); //0
    stackedWidget->addWidget(cDBP); //1

    setCentralWidget(stackedWidget);

    connect(lP, &LandingPage::switchSelectSignal, this, &MainWindow::switchSelectSlot);
    connect(lP, &LandingPage::switchCreateSignal, this, &MainWindow::switchCreateSlot);
    connect(cDBP, &CreateDBPage::returnLandingSignal, this, &MainWindow::switchLendingSlot);
    connect(cDBP, &CreateDBPage::createDBSignal, this, &MainWindow::createDBAndSwitch);
}

void MainWindow::switchCreateSlot() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::switchLendingSlot() {
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::switchSelectSlot() {
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
    stackedWidget->setCurrentIndex(0);
}