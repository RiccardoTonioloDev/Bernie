#include "PagesInterface.h"

PagesInterface::PagesInterface(const SerializableObject *ptr, bool tE, QWidget *parent) : QWidget(parent),
                                                                                          objToManage(ptr),
                                                                                          toEdit(tE) {}

void PagesInterface::returnTypeSelectionPageSlot() {
    emit returnTypeSelectionPageSignal();
}