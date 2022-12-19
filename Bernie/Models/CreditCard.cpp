#include "CreditCard.h"

CreditCard::CreditCard(const std::string& n,const std::string& num, const std::string& c, const Date& d) : SerializableObject(n), number(num), cvv(c), date(d) {}

std::string CreditCard::serialize() const {
    std::string serializedStr = "CREDITCARD";
    serializedStr += SerializableObject::SEPARATOR + SerializableObject::sanitize(name) + SerializableObject::SEPARATOR + SerializableObject::sanitize(number) + SerializableObject::SEPARATOR + SerializableObject::sanitize(cvv) + SerializableObject::SEPARATOR + date.getData();
    return serializedStr;
}

CreditCard* CreditCard::clone() const{
    return new CreditCard(*this);
}