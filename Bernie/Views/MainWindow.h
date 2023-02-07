#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>

#include "../Models/Vault.h"
#include "HomePage.h"
#include "SelectDBPage.h"
#include "DBSelectedPage.h"
#include "SerializableObjectPages/PagesInterface.h"
#include "SelectDBToRemove.h"
#include "DBSelectedToRemovePage.h"

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    QStackedWidget *stackedWidget;
    Vault &vault;
    SelectDBPage *sDBP;
    DBSelectedPage *DBsp;
    HomePage *hp;
    SelectDBToRemove *sDBTR;
    DBSelectedToRemovePage *DBstr;

public:
    explicit MainWindow(Vault &v, QWidget *parent = 0);

public slots:

    void switchCreateSlot();

    void switchSelectSlot();

    void switchDeleteSlot();

    void switchHomePageSlot();

    void switchSelectedDBSlot(const std::string &name);

    void switchLendingSlot();

    void switchTypeSelectionSlot();

    void switchSelectDBToRemoveSlot();

    void switchDBSelectedToRemoveSlot(const std::string&);

    void removeDBSlot(const std::string&, const std::string&);

    void createAddPage(PagesInterface *);

    void createEditPage(PagesInterface *);

    void createWatchPage(PagesInterface *);

    void returnSelectionFromCreate();

    void addSerializableObjectSlot(const SerializableObject *);

    void editSerializableObjectSlot(const SerializableObject *toEdit, const SerializableObject *Edited);

    void createDBAndSwitch(std::string name, std::string password);

    void readDBAndSwitch(const std::string &name, const std::string &password);

    void manualSlot();

    void logoutSlot();

    void decryptSlot();
};


#endif
