#include "CreditCard.h"

CreditCard::CreditCard(const std::string &n, const std::string &own, const std::string &num, const std::string &c,
                       const Date &d) : SerializableObject(n), owner(own), number(num), cvv(c), date(d) {}

CreditCard::CreditCard(const std::vector<std::string> &serializedVectorized) : SerializableObject(
        serializedVectorized[1]), owner(serializedVectorized[2]), number(serializedVectorized[3]),
                                                                               cvv(serializedVectorized[4]),
                                                                               date(serializedVectorized[5]) {}

std::string CreditCard::serialize() const {
    std::string serializedStr = "CREDITCARD";
    serializedStr +=
            SerializableObject::SEPARATOR + SerializableObject::sanitize(name) + SerializableObject::SEPARATOR +
            SerializableObject::sanitize(owner) + SerializableObject::SEPARATOR + SerializableObject::sanitize(number) +
            SerializableObject::SEPARATOR + SerializableObject::sanitize(cvv) + SerializableObject::SEPARATOR +
            date.getData();
    return serializedStr;
}

bool CreditCard::modify(const SerializableObject *ptr) {
    if (dynamic_cast<const CreditCard *>(ptr)) {
        *this = *(static_cast<const CreditCard *>(ptr));
        return true;
    }
    return false;
}

void CreditCard::accept(SerializableObjectsVisitor *visit, bool toEdit) const {
    visit->visit(*this, toEdit);
}

CreditCard *CreditCard::clone() const {
    return new CreditCard(*this);
}

const std::string &CreditCard::getOwner() const {
    return owner;
}

const std::string &CreditCard::getNumber() const {
    return number;
}

const std::string &CreditCard::getCvv() const {
    return cvv;
}

const Date &CreditCard::getDate() const {
    return date;
}
