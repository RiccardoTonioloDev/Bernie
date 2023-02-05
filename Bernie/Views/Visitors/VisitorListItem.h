#ifndef VISITORLISTITEM_H
#define VISITORLISTITEM_H

#include <QWidget>
#include "SerializableObjectsVisitor.h"
#include "ListCardItem.h"

class VisitorListItem : public SerializableObjectsVisitor {
public:
    virtual void visit(const CreditCard &crcard) override;

    virtual void visit(const Account &acc) override;

    virtual void visit(const CryptoWallet &cypt) override;

    virtual void visit(const Contact &cont) override;

    virtual void visit(const Note &note) override;

    ListCardItem *getWidget() override;
};


#endif
