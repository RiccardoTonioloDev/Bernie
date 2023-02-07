#ifndef CREATEDBPAGE_H
#define CREATEDBPAGE_H

#include <QWidget>
#include <QLineEdit>

class CreateDBPage : public QWidget {
Q_OBJECT
private:
    QLineEdit *name;
    QLineEdit *password1;
    QLineEdit *password2;
public:
    CreateDBPage(QWidget *parent = 0);

    void resetFields();

    void spawnAlertDialog(std::string text) const ;

signals:

    void returnLandingSignal();

    void createDBSignal(std::string dbName, std::string password);

public slots:

    void returnLandingSlot();

    void createDBSlot();

};


#endif
