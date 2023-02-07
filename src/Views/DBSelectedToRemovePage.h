#ifndef BERNIE_DBSELECTEDTOREMOVEPAGE_H
#define BERNIE_DBSELECTEDTOREMOVEPAGE_H

#include <QWidget>
#include <QLineEdit>

class DBSelectedToRemovePage : public QWidget {
    Q_OBJECT
private:
    QLineEdit *dbName;
    QLineEdit *dbPassword;
public:
    DBSelectedToRemovePage(QWidget *parent = 0);

    void setName(const std::string &name);

signals:

    void returnSelectDBSignal();

    void removeDBSignal(const std::string &name, const std::string &password);

public slots:

    void returnSelectDBSlot();

    void removeDBSlot();
};


#endif