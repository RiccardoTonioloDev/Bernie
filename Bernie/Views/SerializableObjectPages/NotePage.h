#ifndef NOTEPAGE_H
#define NOTEPAGE_H
#include "PagesInterface.h"
#include <QTextEdit>

class NotePage : public PagesInterface{

    Q_OBJECT
private:
    QTextEdit* textField;
public:
    NotePage(const SerializableObject* ptr = nullptr, bool toEdit = false, QWidget* parent = 0);
signals:
public slots:
    void manageSerializableObjectSlot();

};


#endif
