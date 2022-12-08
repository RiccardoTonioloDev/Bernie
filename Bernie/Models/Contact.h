//#notReviewed
#ifndef CONTACTS.H
#define CONTACTS.H

#include <iostream>
#include "SerializableObject.h"
#include "Date.h"

class Contact : SerializableObject {
private:
    std::string contactName;
    std::string contatcSurname;
    Date birthday;
    Telephone telephone;
    std::string mail;
public:
    Contact(const std::string&, const std::string&, const std::string&, const Date&, const Telephone&, const std::string&);
    /*
    POST: restituisce la stringa composta da il tipo dell'oggetto e il valore dei suoi campi, usando come carattere di separazione ','
    */
    std::string serialize() const override;
    /*
    POST: resituisce una copia dell'oggetto costruita mediante costruttore di copia passando come parametro il puntatore implicito this deferenziato
    */
    Contact* clone() const override;
};

#endif