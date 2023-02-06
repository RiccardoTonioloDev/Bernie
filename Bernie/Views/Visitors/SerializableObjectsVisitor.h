#ifndef SERIALIZABLEOBJECTSVISITOR_H
#define SERIALIZABLEOBJECTSVISITOR_H

#include <QWidget>

class Note;

class Contact;

class Account;

class CreditCard;

class CryptoWallet;

class SerializableObject;

class SerializableObjectsVisitor {
protected:
    QWidget *widget;
public:
    virtual void visit(const CreditCard &crcard, bool toEdit = false) = 0;

    virtual void visit(const Account &acc, bool toEdit = false) = 0;

    virtual void visit(const CryptoWallet &cypt, bool toEdit = false) = 0;

    virtual void visit(const Contact &cont, bool toEdit = false) = 0;

    virtual void visit(const Note &note, bool toEdit = false) = 0;

    virtual QWidget *getWidget() = 0;
};

#endif
