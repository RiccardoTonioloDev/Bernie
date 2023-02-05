#ifndef DBSELECTEDPAGE_H
#define DBSELECTEDPAGE_H

#include <QWidget>
#include <QLineEdit>


class DBSelectedPage : public QWidget {
Q_OBJECT
private:
    QLineEdit *dbName;
    QLineEdit *dbPassword;
public:
    DBSelectedPage(QWidget *parent = 0);

    void setName(const std::string &name);

signals:

    void returnSelectDBSignal();

    void decryptDBSignal(const std::string &name, const std::string &password);

public slots:

    void returnSelectDBSlot();

    void decryptDBSlot();
};


#endif
