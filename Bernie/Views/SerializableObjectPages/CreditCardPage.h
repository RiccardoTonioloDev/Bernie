#ifndef CREDITCARDPAGE_H
#define CREDITCARDPAGE_H

#include "PagesInterface.h"
#include <QSpinBox>
#include "../Components/DateComponent.h"

class CreditCardPage : public PagesInterface {
Q_OBJECT
private:
    QLineEdit *ownerField;
    QLineEdit *numberField;
    QLineEdit *cvvField;
    DateComponent *dateField;
public:
    CreditCardPage(const SerializableObject *obj = nullptr, bool toEdit = false, QWidget *parent = 0);

signals:
public slots:

    void manageSerializableObjectSlot();

};


#endif
