//#notReviewed
#include "Account.h"

Account::Account(const std::string & n, const std::string & email, const std::string & pswd, const std::string & usrnm): SerializableObject(n), email(email), username(usrnm), password(pswd){}

std::string Account::serialize() const {
    std::string serializedObj = "ACCOUNT,";
    serializedObj = serializedObj + sanitize(name) + "," + sanitize(email) + "," + sanitize(password) + "," + sanitize(username);
    return serializedObj;
}

Account* Account::clone() const {
    return new Account(*this);
}