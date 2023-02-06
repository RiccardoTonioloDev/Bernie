#include "Account.h"

Account::Account(const std::string &n, const std::string &email, const std::string &pswd, const std::string &usrnm)
        : SerializableObject(n), email(email), username(usrnm), password(pswd) {}

Account::Account(const std::vector<std::string> &serializedVectorized) : SerializableObject(serializedVectorized[1]),
                                                                         email(serializedVectorized[2]),
                                                                         password(serializedVectorized[3]),
                                                                         username(serializedVectorized[4]) {}

std::string Account::serialize() const {
    std::string serializedObj = "ACCOUNT";
    serializedObj += SerializableObject::SEPARATOR;
    serializedObj = serializedObj + sanitize(name) + SerializableObject::SEPARATOR + sanitize(email) +
                    SerializableObject::SEPARATOR + sanitize(password) + SerializableObject::SEPARATOR +
                    sanitize(username);

    return serializedObj;
}

bool Account::modify(const SerializableObject *ptr) {
    if (dynamic_cast<const Account *>(ptr)) {
        *this = *(static_cast<const Account *>(ptr));
        return true;
    }
    return false;
}

void Account::accept(SerializableObjectsVisitor *visitor, bool toEdit) const {
    visitor->visit(*this, toEdit);
}

Account *Account::clone() const {
    return new Account(*this);
}

const std::string &Account::getEmail() const {
    return email;
}

const std::string &Account::getUsername() const {
    return username;
}

const std::string &Account::getPassword() const {
    return password;
}
