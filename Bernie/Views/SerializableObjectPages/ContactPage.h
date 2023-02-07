#ifndef BERNIE_CONTACTPAGE_H
#define BERNIE_CONTACTPAGE_H

#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include "PagesInterface.h"
#include "../../Models/Contact.h"
#include "../Components/DateComponent.h"

class ContactPage : public PagesInterface {
Q_OBJECT
private:
    QLineEdit *contactNameField;
    QLineEdit *contactSurnameField;
    QLineEdit *emailField;
    DateComponent *dateField;
    QSpinBox *prefixField;
    QLineEdit *numberField;

public:
    ContactPage(const SerializableObject *ptr = nullptr, bool toEdit = false, QWidget *parent = 0);

signals:
public slots:

    void manageSerializableObjectSlot();
};


#endif
