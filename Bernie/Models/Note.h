//#notReviewed
#ifndef NOTE.H
#define NOTE.H

#include <iostream>

class Note : public SerializableObject{
private:
    std::string text;
public:
    Note(const std::string&, const std::string&);
    /*
    POST: restituisce la stringa composta da il tipo dell'oggetto e il valore dei suoi campi, usando come carattere di separazione ','
    */
    std::string Serialize() const override;
    /*
    POST: resituisce una copia dell'oggetto costruita mediante costruttore di copia passando come parametro il puntatore implicito this deferenziato
    */
    Note* clone() const override;
};

#endif