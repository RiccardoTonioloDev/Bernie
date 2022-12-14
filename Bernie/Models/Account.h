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
    Account(const std::string& name, const std::string& email,  const std::string& password,const std::string& username = "");
    /*
     * POST: ritorna sotto forma di string l'oggetto Account, usando come carattere separatore la ",".
     */
    std::string serialize() const override;
    /*
     * POST: ritorna un puntatore ad Account essendo covariante come tipo di ritorno a un puntatore SerializableObject
     */
    Account * clone() const override;
};


#endif //ACCOUNT_H
