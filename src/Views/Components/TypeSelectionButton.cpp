#include "TypeSelectionButton.h"
#include <QHBoxLayout>
#include <QLabel>

TypeSelectionButton::TypeSelectionButton(const std::string &label, const std::string &icon) {
    QHBoxLayout *lyt = new QHBoxLayout();
    lyt->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//
    setMinimumHeight(50);//
    setFixedWidth(200);
    QLabel *iconButton = new QLabel();
    iconButton->setMinimumHeight(30);
    iconButton->setPixmap(QIcon(QString::fromStdString(icon)).pixmap(30, 30));
    iconButton->setAlignment(Qt::AlignCenter);//
    lyt->addWidget(iconButton);
    QLabel *lbl = new QLabel(QString::fromStdString(label));
    lyt->addStretch();
    lyt->addWidget(lbl);
    setLayout(lyt);

    connect(this, &QPushButton::clicked, this, &TypeSelectionButton::clickedSlot);
}

void TypeSelectionButton::clickedSlot() {
    emit clickedSignal();
}