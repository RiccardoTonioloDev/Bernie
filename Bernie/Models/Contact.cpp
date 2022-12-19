#include "Contact.h"

Contact::Contact(const std::string& n, const std::string& cn, const std::string& s, const Date& b, const Telephone& t, const std::string& m) : SerializableObject(n), contactName(cn), contactSurname(s), birthday(b), telephone(t), mail(m) {}

std::string Contact::serialize() const{
    std::string serializedStr = "CONTACT";
    serializedStr += SerializableObject::SEPARATOR + SerializableObject::sanitize(name) + SerializableObject::SEPARATOR + SerializableObject::sanitize(contactName) + SerializableObject::SEPARATOR + SerializableObject::sanitize(contactSurname) + SerializableObject::SEPARATOR + birthday.getData() + SerializableObject::SEPARATOR + telephone.getNumber() + SerializableObject::SEPARATOR + mail;
    return serializedStr;
}

Contact* Contact::clone() const{
    return new Contact(*this);
}