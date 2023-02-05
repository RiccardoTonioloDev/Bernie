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
    virtual void visit(const CreditCard &crcard) = 0;

    virtual void visit(const Account &acc) = 0;

    virtual void visit(const CryptoWallet &cypt) = 0;

    virtual void visit(const Contact &cont) = 0;

    virtual void visit(const Note &note) = 0;

    virtual QWidget *getWidget();
};

#endif
