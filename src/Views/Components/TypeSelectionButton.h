//
// Created by Riccardo Toniolo on 06/02/23.
//

#ifndef BERNIE_TYPESELECTIONBUTTON_H
#define BERNIE_TYPESELECTIONBUTTON_H


#include <QWidget>
#include <QPushButton>

class TypeSelectionButton : public QPushButton {
Q_OBJECT
public:
    TypeSelectionButton(const std::string &label, const std::string &icon);

signals:

    void clickedSignal();

public slots:

    void clickedSlot();
};


#endif //BERNIE_TYPESELECTIONBUTTON_H
