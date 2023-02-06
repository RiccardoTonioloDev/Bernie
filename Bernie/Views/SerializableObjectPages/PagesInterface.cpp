#include "PagesInterface.h"

PagesInterface::PagesInterface(const SerializableObject *ptr, QWidget *parent) : toEdit(ptr), QWidget(parent) {}

void PagesInterface::returnTypeSelectionPageSlot() {
    emit returnTypeSelectionPageSignal();
}