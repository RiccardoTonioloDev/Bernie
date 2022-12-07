//#notReviewed
#include "Contacts.h" 

Contacts::Contacts(const std::string& n, const std::string& cn, const std::string& s, const Date& b, const Telephone& t, const std::string& m) : SerializableObject(n), contactName(cn), surname(s), birthday(b), telephone(t), mail(m) {} 

std::string Contacts::Serialize(){
    return "CONTACTS," + name + "," + contactName + "," + surname + "," + birthday.getData() + "," + telephone.getNumber + "," + mail;
}

Contacts* Contacts::clone(){
    return new Note(*this);
}