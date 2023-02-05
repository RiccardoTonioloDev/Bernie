#ifndef VISITORLISTITEM_H
#define VISITORLISTITEM_H

#include <QWidget>
#include "SerializableObjectsVisitor.h"

class VisitorListItem : public SerializableObjectsVisitor {
public:
    virtual void visit(const CreditCard &crcard);

    virtual void visit(const Account &acc);

    virtual void visit(const CryptoWallet &cypt);

    virtual void visit(const Contact &cont);

    virtual void visit(const Note &note);
};


#endif
