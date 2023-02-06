#ifndef VISITORMANAGEITEM_H
#define VISITORMANAGEITEM_H

#include "SerializableObjectsVisitor.h"


class VisitorManageItem : public SerializableObjectsVisitor {

    virtual void visit(const CreditCard &crcard) override;

    virtual void visit(const Account &acc) override;

    virtual void visit(const CryptoWallet &cypt) override;

    virtual void visit(const Contact &cont) override;

    virtual void visit(const Note &note) override;

};


#endif
