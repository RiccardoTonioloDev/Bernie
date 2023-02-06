#ifndef BERNIE_DATECOMPONENT_H
#define BERNIE_DATECOMPONENT_H
#include <QWidget>
#include <QLineEdit>
#include "../../Models/Date.h"

class DateComponent : public QWidget{
    Q_OBJECT
private:
    QLineEdit* dayField;
    QLineEdit* monthField;
    QLineEdit* yearField;
    Date *date;
public:
    DateComponent(Date *d = nullptr, bool toEdit = false, QWidget *parent = 0);
    bool isValid() const;
    Date* getDate() const;
};


#endif //BERNIE_DATECOMPONENT_H
