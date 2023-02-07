#include <QApplication>
#include <QFile>
#include <QIcon>
#include "Views/MainWindow.h"

#include "./Models/Vault.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/assets/App_Icon"));
    QFile stylesheet(":/assets/stylesheet");
    stylesheet.open(QFile::ReadOnly);
    app.setStyleSheet(QLatin1String(stylesheet.readAll()));

    Vault vault("./Savings/Databases");
    MainWindow window(vault);
    window.resize(800, 600);
    window.setMinimumHeight(600);
    window.setMinimumWidth(800);
    window.show();

    return app.exec();
}