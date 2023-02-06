#ifndef CREDITCARDPAGE_H
#define CREDITCARDPAGE_H
#include "PagesInterface.h"

class CreditCardPage : public PagesInterface{
    Q_OBJECT
private:
    QLineEdit *nameField;
    QLineEdit *numberField;
    QLineEdit *cvvField;
public:
    CreditCardPage(const SerializableObject* obj = nullptr, bool toEdit = false, QWidget* parent = 0){}
    signals:
public slots:
    void managerSerializableObjectSlot(){};

};


#endif
