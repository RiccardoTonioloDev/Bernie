#ifndef VISITORMANAGEITEM_H
#define VISITORMANAGEITEM_H

#include "SerializableObjectsVisitor.h"
#include "../SerializableObjectPages/PagesInterface.h"


class VisitorManageItem : public SerializableObjectsVisitor {

    virtual void visit(const CreditCard &crcard, bool toEdit) override;

    virtual void visit(const Account &acc, bool toEdit) override;

    virtual void visit(const CryptoWallet &cypt, bool toEdit) override;

    virtual void visit(const Contact &cont, bool toEdit) override;

    virtual void visit(const Note &note, bool toEdit) override;

public:

    PagesInterface *getWidget() override;
};


#endif
