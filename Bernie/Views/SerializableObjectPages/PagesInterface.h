#ifndef PAGESINTERFACE_H
#define PAGESINTERFACE_H

#include <QWidget>
#include <QLineEdit>
#include "../../Models/SerializableObject.h"

class PagesInterface : public QWidget {
Q_OBJECT
protected:
    const SerializableObject *objToManage;
    QLineEdit *nameField;
    bool toEdit;
public:
    PagesInterface(const SerializableObject * = nullptr, bool tE = false, QWidget *parent = 0);

signals:

    void returnTypeSelectionPageSignal();

    void addSerializableObjectSignal(const SerializableObject *newObject);

    virtual void editSerializableObjectSignal(const SerializableObject *toEdit, const SerializableObject *edited) = 0;

public slots:

    void returnTypeSelectionPageSlot();

    virtual void manageSerializableObjectSlot() = 0;

};

#endif
