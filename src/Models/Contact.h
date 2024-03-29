#ifndef CONTACTS_H
#define CONTACTS_H

#include <iostream>
#include "SerializableObject.h"
#include "Date.h"
#include "Telephone.h"

class Contact : public SerializableObject {
private:
    std::string contactName;
    std::string contactSurname;
    Date birthday;
    Telephone telephone;
    std::string mail;
public:
    Contact(const std::string &name, const std::string &contactName, const std::string &contactSurname,
            const Date &birthdayDate, const Telephone &telephone, const std::string &email);

    Contact(const std::vector<std::string> &serializedVectorized);

    /*
    POST: restituisce la stringa composta da il tipo dell'oggetto e il valore dei suoi campi, usando come carattere di separazione ','
    */
    std::string serialize() const override;

    virtual bool modify(const SerializableObject *) override;

    /*
    POST: resituisce una copia dell'oggetto costruita mediante costruttore di copia passando come parametro il puntatore implicito this deferenziato
    */
    Contact *clone() const override;

    void accept(SerializableObjectsVisitor *visit, bool toEdit = false) const override;

    const std::string &getContactName() const;

    const std::string &getContactSurname() const;

    const Date &getBirthday() const;

    const Telephone &getTelephone() const;

    const std::string &getMail() const;
};

#endif