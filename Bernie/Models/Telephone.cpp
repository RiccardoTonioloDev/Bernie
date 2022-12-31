#include "Telephone.h"

Telephone::Telephone(const std::string & p, const std::string & n): prefix(p), number(n) {}
Telephone::Telephone(std::string &strTelephone) {
    std::string delimiter = " ";

    size_t pos = 0;
    int fieldNumber = 0;
    std::string field;
    std::string token;
    while ((pos = strTelephone.find(delimiter)) != std::string::npos) {
        token = strTelephone.substr(0, pos);
        field = token;
        fieldNumber++;
        strTelephone.erase(0, pos + delimiter.length());
    }
    prefix = field;
    number = strTelephone;
}

std::string Telephone::getNumber() const {
    return prefix + " " + number;
}