//#notReviewed
#include "Contact.h" 

Contact::Contact(const std::string& n, const std::string& cn, const std::string& s, const Date& b, const Telephone& t, const std::string& m) : SerializableObject(n), contactName(cn), contactSurname(s), birthday(b), telephone(t), mail(m) {}

std::string Contact::serialize() const{
    return "CONTACT," + SerializableObject::sanitize(name) + "," + SerializableObject::sanitize(contactName) + "," + SerializableObject::sanitize(contactSurname) + "," + birthday.getData() + "," + telephone.getNumber() + "," + mail;
}

Contact* Contact::clone() const{
    return new Contact(*this);
}