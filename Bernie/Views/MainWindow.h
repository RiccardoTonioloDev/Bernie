#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>

#include "../Models/Vault.h"

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    QStackedWidget *stackedWidget;
    Vault &vault;

public:
    explicit MainWindow(Vault &v, QWidget *parent = 0);

public slots:

    void switchCreateSlot();

    void switchSelectSlot();

    void switchLendingSlot();

    void createDBAndSwitch(std::string name, std::string password);
};


#endif
