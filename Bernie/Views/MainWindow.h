#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>

#include "../Models/Vault.h"
#include "HomePage.h"
#include "SelectDBPage.h"
#include "DBSelectedPage.h"

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    QStackedWidget *stackedWidget;
    Vault &vault;
    SelectDBPage *sDBP;
    DBSelectedPage *DBsp;
    HomePage *hp;

public:
    explicit MainWindow(Vault &v, QWidget *parent = 0);

public slots:

    void switchCreateSlot();

    void switchSelectSlot();

    void switchHomePageSlot();

    void switchSelectedDBSlot(const std::string &name);

    void switchLendingSlot();

    void switchTypeSelectionSlot();

    void createDBAndSwitch(std::string name, std::string password);

    void readDBAndSwitch(const std::string &name, const std::string &password);
};


#endif
