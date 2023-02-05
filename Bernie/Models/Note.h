#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include "SerializableObject.h"

class Note : public SerializableObject {
private:
    std::string text;
public:
    Note(const std::string &name, const std::string &text);

    Note(const std::vector<std::string> &serializedVectorized);

    /*
    POST: restituisce la stringa composta da il tipo dell'oggetto e il valore dei suoi campi, usando come carattere di separazione ','
    */
    std::string serialize() const override;

    virtual bool modify(const SerializableObject *) override;

    /*
    POST: resituisce una copia dell'oggetto costruita mediante costruttore di copia passando come parametro il puntatore implicito this deferenziato
    */
    Note *clone() const override;

    void accept(SerializableObjectsVisitor *visitor) const override;
};

#endif