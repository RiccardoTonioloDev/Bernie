//#notReviewed
#include "CreditCard.h"

CreditCard::CreditCard(const std::string& n,const std::string& num, const std::string& c, const Date& d) : SerializableObject(n), number(num), cvv(c), date(d) {}

std::string CreditCard::serialize() const {
    //controllare che nel name non ci sia , (o \) e in caso metterci un \ davanti (escape)
    //name = dsads\csd -> dsads\\csd
    //name = aaaa\\,aa,a -> aaaa\\\,aa\,a
    return "CREDITCARD," + name + "," + number + "," + cvv + "," + date.getData();
}

CreditCard* CreditCard::clone() const{
    return new CreditCard(*this);
}