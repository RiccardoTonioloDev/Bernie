//#notReviewed
#ifndef SERIALIZABLEOBJECT_H
#define SERIALIZABLEOBJECT_H
#include <string>


class SerializableObject {
protected:
    std::string name;
public:
    SerializableObject(const std::string&);
    /*
     * POST: va a serializzare in formato CSV il contenuto dell'oggetto
     */
    virtual std::string serialize() const = 0;
    /*
     * POST: va a creare un clone di se stesso, ritornando il puntatore ad esso
     */
    virtual SerializableObject* clone() const = 0;
    bool operator==(const SerializableObject&) const;
    bool operator<(const SerializableObject&) const;
    bool operator>(const SerializableObject&) const;
    virtual ~SerializableObject();
protected:
    /*
     * POST: va ad aggiungere caratteri di escape per evitare che l'utente corrompa accidentalmente
     * il file solo posizionando una virgola (che è il carattere separatore)
     */
    static std::string sanitize(const std::string&);
    static std::string deSanitize(const std::string&);
    static int wow;
};

#endif
