#include <QLabel>
#include <QDialog>
#include "DateComponent.h"
#include "QHBoxLayout"

DateComponent::DateComponent(Date* d, bool toEdit, QWidget *parent): QWidget(parent), date(d){
    QHBoxLayout *lyt = new QHBoxLayout();

    dayField = new QLineEdit();
    dayField->setEnabled(toEdit);
    dayField->setAlignment(Qt::AlignCenter);
    if(date) dayField->setText(QString::fromStdString(std::to_string(date->getDay())));

    monthField = new QLineEdit();
    monthField->setEnabled(toEdit);
    monthField->setAlignment(Qt::AlignCenter);
    if(date) monthField->setText(QString::fromStdString(std::to_string(date->getMonth())));

    yearField = new QLineEdit();
    yearField->setEnabled(toEdit);
    yearField->setAlignment(Qt::AlignCenter);
    if(date) yearField->setText(QString::fromStdString(std::to_string(date->getYear())));

    lyt->addWidget(dayField);
    lyt->addWidget(monthField);
    lyt->addWidget(yearField);
    setLayout(lyt);
}

bool DateComponent::isValid() const{
    if(std::stoi(monthField->text().toStdString()) == 2) {
        if ((std::stoi(dayField->text().toStdString()) == 29 && std::stoi(yearField->text().toStdString()) % 4 != 0) || std::stoi(dayField->text().toStdString()) > 29) return false;
    }

    if(std::stoi(dayField->text().toStdString()) == 31 && (std::stoi(monthField->text().toStdString()) == 11 ||
                                                                std::stoi(monthField->text().toStdString()) == 4 ||
                                                                std::stoi(monthField->text().toStdString()) == 6 ||
                                                                std::stoi(monthField->text().toStdString()) == 9)) return false;

    return true;
}

Date* DateComponent::getDate() const {
    return new Date(std::stoi(dayField->text().toStdString()),std::stoi(monthField->text().toStdString()),std::stoi(yearField->text().toStdString()));
}