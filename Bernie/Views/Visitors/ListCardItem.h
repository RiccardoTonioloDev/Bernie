#ifndef BERNIE_LISTCARDITEM_H
#define BERNIE_LISTCARDITEM_H

#include <QWidget>

class SerializableObject;

class ListCardItem : public QWidget {
Q_OBJECT
private:
    const SerializableObject *data;
public:
    ListCardItem(const SerializableObject *d, const std::string &name, const std::string &icon, QWidget *parent = 0);

signals:

    void watchSignal(const SerializableObject *data);

    void editSignal(const SerializableObject *data);

    void removeSignal(const SerializableObject *data);

public slots:

    void watchSlot();

    void editSlot();

    void removeSlot();
};


#endif
