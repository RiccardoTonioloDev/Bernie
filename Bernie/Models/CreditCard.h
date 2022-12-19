#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <iostream>
#include "SerializableObject.h"
#include "Date.h"

class CreditCard : public SerializableObject{
private:
    std::string number;
    std::string cvv;
    Date date;
public:
    CreditCard(const std::string& name, const std::string& cardNumber, const std::string& cvv, const Date& expirationDate);
    /*
    POST: restituisce la stringa composta da il tipo dell'oggetto e il valore dei suoi campi, usando come carattere di separazione ','
    */
    std::string serialize() const override;
    /*
    POST: resituisce una copia dell'oggetto costruita mediante costruttore di copia passando come parametro il puntatore implicito this deferenziato
    */  
    CreditCard* clone() const override;
};

#endif