//#notReviewed
#ifndef CONTACTS.H
#define CONTACTS.H

#include <iostream>
#include "Date.h"

class Contacts : SerializableObject {
private:
    std::string contactName;
    std::string surname;
    Date birthday;
    Telephone telephone;
    std::string mail;
public:
    Contacts(const std::string&, const std::string&, const std::string&, const Date&, const Telephone&, const std::string&);
    /*
    POST: restituisce la stringa composta da il tipo dell'oggetto e il valore dei suoi campi, usando come carattere di separazione ','
    */
    std::string Serialize() const override;
    /*
    POST: resituisce una copia dell'oggetto costruita mediante costruttore di copia passando come parametro il puntatore implicito this deferenziato
    */
    Contacts* clone() const override;
};

#endif