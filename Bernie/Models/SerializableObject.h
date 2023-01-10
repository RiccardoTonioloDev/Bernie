//#notReviewed
#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>


class SerializableObject {
    friend std::ostream &operator<<(std::ostream &, const SerializableObject &);

protected:
    std::string name;

    /*
     * POST: va ad aggiungere caratteri di escape per evitare che l'utente corrompa accidentalmente
     * il file solo posizionando una virgola (che è il carattere separatore).
     */
    static std::string sanitize(const std::string &);

public:
    explicit SerializableObject(const std::string &name);

    /*
     * POST: va a serializzare in formato CSV il contenuto dell'oggetto.
     */
    virtual std::string serialize() const = 0;

    /*
     * POST: va a creare un clone di se stesso, ritornando il puntatore a esso.
     */
    virtual SerializableObject *clone() const = 0;

    bool operator==(const SerializableObject &) const;

    bool operator==(const std::string &nameToCompare) const;

    bool operator<(const SerializableObject &) const;

    bool operator<(const std::string &nameToCompare) const;

    bool operator>(const SerializableObject &) const;

    bool operator>(const std::string &nameToCompare) const;

    bool operator<=(const SerializableObject &) const;

    virtual bool modify(const SerializableObject *) = 0;

    operator std::string() const;

    virtual ~SerializableObject();

    /*
     * POST: va a rimuovere i caratteri di escape e restituisce una coppia composta da un valore
     * booleano che indica se il file è stato compromesso, e in caso non sia compromesso contiene
     * come secondo valore le parole corrette estratte dal file per ricostruire l'oggetto da
     * recuperare.
     */
    static std::pair<bool, std::vector<std::string>> deSanitize(const std::string &);

    static char ESCAPE;
    static char SEPARATOR;
};

#endif
