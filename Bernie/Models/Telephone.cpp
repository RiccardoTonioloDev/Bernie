#include "Telephone.h"

Telephone::Telephone(const std::string &p, const std::string &n) : prefix(p), number(n) {}

Telephone::Telephone(const std::string &strTelephone) {
    std::string strTelephoneCopy = strTelephone;
    std::string delimiter = " ";

    size_t pos = 0;
    int fieldNumber = 0;
    std::string field;
    std::string token;
    while ((pos = strTelephoneCopy.find(delimiter)) != std::string::npos) {
        token = strTelephoneCopy.substr(0, pos);
        field = token;
        fieldNumber++;
        strTelephoneCopy.erase(0, pos + delimiter.length());
    }
    prefix = field;
    number = strTelephoneCopy;
}

std::string Telephone::getNumber() const {
    return prefix + " " + number;
}