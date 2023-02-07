#ifndef BERNIE_MENUBUTTON_H
#define BERNIE_MENUBUTTON_H

#include <QWidget>
#include <QPushButton>

class MenuButton : public QPushButton {
Q_OBJECT
public:
    MenuButton(const std::string &label, const std::string &icon);

signals:

    void clickedSignal();

public slots:

    void clickedSlot();
};


#endif
