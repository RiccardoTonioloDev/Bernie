//#notReviewed
#include "Account.h"

Account::Account(const std::string & n, const std::string & email, const std::string & usrnm, const std::string & pswd): SerializableObject(n), email(email), username(usrnm), password(pswd){}

std::string Account::serialize() const {
    std::string serializedObj = "ACCOUNT,";
    serializedObj = serializedObj + name + "," + email + "," + username + "," + password;
    return serializedObj;
}

Account* Account::clone() const {
    return new Account(*this);
}