//#notReviewed

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <iostream>
#include "SerializableObject.h"

class Account: public SerializableObject{
private:
   std::string email;
   std::string username;
   std::string password;
public:
    Account(const std::string&, const std::string&, const std::string& = "", const std::string&);
    std::string serialize() const override;
    Account * clone() const override;
};


#endif //ACCOUNT_H
