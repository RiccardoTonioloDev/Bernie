#include "VisitorListItem.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>

#include "../../Models/Account.h"
#include "../../Models/CryptoWallet.h"
#include "../../Models/Contact.h"
#include "../../Models/Note.h"
#include "../../Models/CreditCard.h"
#include "ListCardItem.h"


void VisitorListItem::visit(const Note &note) {
    widget = new ListCardItem(&note, note, ":/assets/Notes");
}

void VisitorListItem::visit(const Account &acc) {
    widget = new ListCardItem(&acc, acc, ":/assets/Account");
}

void VisitorListItem::visit(const CreditCard &crcard) {
    widget = new ListCardItem(&crcard, crcard, ":/assets/CreditCards");
}

void VisitorListItem::visit(const Contact &cont) {
    widget = new ListCardItem(&cont, cont, ":/assets/Contacts");
}

void VisitorListItem::visit(const CryptoWallet &crypt) {
    widget = new ListCardItem(&crypt, crypt, ":/assets/Crypto");
}

ListCardItem *VisitorListItem::getWidget() {
    return static_cast<ListCardItem *>(widget);
}