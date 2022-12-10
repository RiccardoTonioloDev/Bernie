//#notReviewed
#include "Contact.h" 

Contact::Contact(const std::string& n, const std::string& cn, const std::string& s, const Date& b, const Telephone& t, const std::string& m) : SerializableObject(n), contactName(cn), contatcSurname(s), birthday(b), telephone(t), mail(m) {} 

std::string Contact::serialize() const{
    return "CONTACT," + name + "," + contactName + "," + contatcSurname + "," + birthday.getData() + "," + telephone.getNumber() + "," + mail;
}

Contact* Contact::clone() const{
    return new Contact(*this);
}