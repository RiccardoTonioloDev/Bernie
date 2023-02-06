#include "PagesInterface.h"

PagesInterface::PagesInterface(const SerializableObject *ptr, bool tE, QWidget *parent) : objToManage(ptr), toEdit(tE),
                                                                                          QWidget(parent) {}

void PagesInterface::returnTypeSelectionPageSlot() {
    emit returnTypeSelectionPageSignal();
}