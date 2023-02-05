#include "ListCardItem.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "../../Models/SerializableObject.h"

ListCardItem::ListCardItem(const SerializableObject *d, const std::string &name, const std::string &icon,
                           QWidget *parent) : QWidget(parent), data(d) {
    QHBoxLayout *cardRow = new QHBoxLayout(this);
    QLabel *iconLabel = new QLabel;
    iconLabel->setPixmap(QIcon(QString::fromStdString(icon)).pixmap(64, 64));
    QLabel *objName = new QLabel(QString::fromStdString(name));
    QPushButton *viewButton = new QPushButton();
    viewButton->setFixedSize(40, 40);
    viewButton->setIcon(QIcon(":/assets/View"));
    viewButton->setIconSize(QSize(20, 20));
    QPushButton *editButton = new QPushButton();
    editButton->setFixedSize(40, 40);
    editButton->setIcon(QIcon(":/assets/Edit"));
    editButton->setIconSize(QSize(20, 20));
    QPushButton *removeButton = new QPushButton();
    removeButton->setFixedSize(40, 40);
    removeButton->setIcon(QIcon(":/assets/Remove"));
    removeButton->setIconSize(QSize(20, 20));
    removeButton->setObjectName("remove");

    cardRow->addWidget(iconLabel);
    cardRow->addWidget(objName);
    cardRow->addStretch();
    cardRow->addWidget(viewButton);
    cardRow->addWidget(editButton);
    cardRow->addWidget(removeButton);

    connect(viewButton, &QPushButton::clicked, this, &ListCardItem::watchSlot);
    connect(editButton, &QPushButton::clicked, this, &ListCardItem::editSlot);
    connect(removeButton, &QPushButton::clicked, this, &ListCardItem::removeSlot);
}

void ListCardItem::editSlot() {
    emit editSignal(data);
}

void ListCardItem::watchSlot() {
    emit watchSignal(data);
}

void ListCardItem::removeSlot() {
    emit removeSignal(data);
}
