#ifndef VISITORLISTITEM_H
#define VISITORLISTITEM_H

#include <QWidget>
#include "SerializableObjectsVisitor.h"
#include "ListCardItem.h"

class VisitorListItem : public SerializableObjectsVisitor {
public:
    virtual void
    visit(const CreditCard &crcard, bool toEdit = false) override;

    virtual void visit(const Account &acc, bool toEdit = false) override;

    virtual void visit(const CryptoWallet &cypt, bool toEdit = false) override;

    virtual void visit(const Contact &cont, bool toEdit = false) override;

    virtual void visit(const Note &note, bool toEdit = false) override;

    ListCardItem *getWidget() override;
};


#endif
