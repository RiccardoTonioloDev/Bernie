#include "MenuButton.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>


MenuButton::MenuButton(const std::string &label, const std::string &icon) {
    QVBoxLayout *lyt = new QVBoxLayout();
    lyt->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//
    setMinimumHeight(70);//
    QLabel *iconButton = new QLabel();
    iconButton->setMinimumHeight(30);
    iconButton->setPixmap(QIcon(QString::fromStdString(icon)).pixmap(30, 30));
    iconButton->setAlignment(Qt::AlignCenter);//
    lyt->addWidget(iconButton);
    QLabel *lbl = new QLabel(QString::fromStdString(label));
    lyt->addWidget(lbl);
    setLayout(lyt);

    connect(this, &QPushButton::clicked, this, &MenuButton::clickedSlot);
}

void MenuButton::clickedSlot() {
    emit clickedSignal();
}