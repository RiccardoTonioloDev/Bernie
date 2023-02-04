#ifndef BERNIE_SELECTDBPAGE_H
#define BERNIE_SELECTDBPAGE_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>


class SelectDBPage : public QWidget {
Q_OBJECT
private:
    QLabel *noFiles;
    QComboBox *filesCombobox;
    QPushButton *selectButton;
public:
    SelectDBPage(std::vector<std::string> fN, QWidget *parent = 0);

    void refreshNameList(std::vector<std::string> fN);

signals:

    void returnLandingSignal();

public slots:

    void returnLandingSlot();

};


#endif
