#ifndef BERNIE_SELECTDBTOREMOVE_H
#define BERNIE_SELECTDBTOREMOVE_H
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class SelectDBToRemove: public QWidget  {
Q_OBJECT
private:
    QLabel *noFiles;
    QComboBox *filesCombobox;
    QPushButton *selectButton;
public:
    SelectDBToRemove(std::vector<std::string> fN, QWidget *parent = 0);

    void refreshNameList(std::vector<std::string> fN);

signals:

    void returnLandingSignal();

    void dbSelectedToRemoveSignal(const std::string &name);

public slots:

    void returnLandingSlot();

    void dbSelectedToRemoveSlot();

};


#endif //BERNIE_SELECTDBTOREMOVE_H
