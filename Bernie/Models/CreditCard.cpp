//#notReviewed
#include "CreditCard.h"

CreditCard::CreditCard(const std::string& n,const std::string& num, const std::string& c, const Date& d) : SerializableObject(n), number(num), cvv(c), date(d) {}

std::string CreditCard::serialize() const {
    return "CREDITCARD," + SerializableObject::sanitize(name) + "," + SerializableObject::sanitize(number) + "," + SerializableObject::sanitize(cvv) + "," + date.getData();
}

CreditCard* CreditCard::clone() const{
    return new CreditCard(*this);
}