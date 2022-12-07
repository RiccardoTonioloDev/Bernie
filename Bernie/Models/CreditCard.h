//#notReviewed
#ifndef CREDITCARD.H
#define CREDITCARD.H

#include <iostream>
#include "Date.h"

class CreditCard : SerializableObject{
private:
    std::string number;
    std::string cvv;
    Date date;
public:
    CreditCard(const std::string&, const std::string&, const std::string&, const Date&);
    /*
    POST: restituisce la stringa composta da il tipo dell'oggetto e il valore dei suoi campi, usando come carattere di separazione ','
    */
    std::string Serialize() const override;
    /*
    POST: resituisce una copia dell'oggetto costruita mediante costruttore di copia passando come parametro il puntatore implicito this deferenziato
    */  
    CreditCard* clone() const override;
};

#endif