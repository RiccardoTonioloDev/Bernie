#include "Contact.h"

Contact::Contact(const std::string &n, const std::string &cn, const std::string &s, const Date &b, const Telephone &t,
                 const std::string &m) : SerializableObject(n), contactName(cn), contactSurname(s), birthday(b),
                                         telephone(t), mail(m) {}

Contact::Contact(const std::vector<std::string> &serializedVectorized) : SerializableObject(serializedVectorized[1]),
                                                                         contactName(serializedVectorized[2]),
                                                                         contactSurname(serializedVectorized[3]),
                                                                         birthday(serializedVectorized[4]),
                                                                         telephone(serializedVectorized[5]),
                                                                         mail(serializedVectorized[6]) {}

std::string Contact::serialize() const {
    std::string serializedStr = "CONTACT";
    serializedStr +=
            SerializableObject::SEPARATOR + SerializableObject::sanitize(name) + SerializableObject::SEPARATOR +
            SerializableObject::sanitize(contactName) + SerializableObject::SEPARATOR +
            SerializableObject::sanitize(contactSurname) + SerializableObject::SEPARATOR + birthday.getData() +
            SerializableObject::SEPARATOR + telephone.getNumber() + SerializableObject::SEPARATOR + mail;
    return serializedStr;
}

bool Contact::modify(const SerializableObject *ptr) {
    if (dynamic_cast<const Contact *>(ptr)) {
        *this = *(static_cast<const Contact *>(ptr));
        return true;
    }
    return false;
}

void Contact::accept(SerializableObjectsVisitor *visit) const {
    visit->visit(*this);
}

Contact *Contact::clone() const {
    return new Contact(*this);
}