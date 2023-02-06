#include "VisitorManageItem.h"
#include "../../Models/Note.h"
#include "../../Models/Contact.h"
#include "../../Models/CreditCard.h"
#include "../../Models/Account.h"
#include "../../Models/CryptoWallet.h"
#include "../SerializableObjectPages/NotePage.h"
#include "../SerializableObjectPages/CryptoWalletPage.h"
#include "../SerializableObjectPages/AccountPage.h"
#include "../SerializableObjectPages/CreditCardPage.h"

void VisitorManageItem::visit(const Note &note, bool toEdit) {
    widget = new NotePage(&note, toEdit);
}

void VisitorManageItem::visit(const Contact &cont, bool toEdit) {
    widget = nullptr;
}

void VisitorManageItem::visit(const CreditCard &crcard, bool toEdit) {
    widget = new CreditCardPage(&crcard, toEdit);
}

void VisitorManageItem::visit(const CryptoWallet &cryp, bool toEdit) {
    widget = new CryptoWalletPage(&cryp, toEdit);
}

void VisitorManageItem::visit(const Account &acc, bool toEdit) {
    widget = new AccountPage(&acc, toEdit);
}

PagesInterface *VisitorManageItem::getWidget() {
    return static_cast<PagesInterface *>(widget);
}