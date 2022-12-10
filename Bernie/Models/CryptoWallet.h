//#notReviewed

#ifndef CRYPTOWALLET_H
#define CRYPTOWALLET_H
#include "SerializableObject.h"
#include <string>
#include <iostream>
#include <vector>

class CryptoWallet: public SerializableObject {
private:
    std::string blockchain_name;
    std::vector<std::string> words;
public:
    CryptoWallet(const std::string&, const std::string&, const std::vector<std::string>&);
    /*
     * POST: ritorna sotto forma di string l'oggetto CryptoWallet, usando come carattere separatore la ",".
     */
    std::string serialize() const override;
    /*
     * POST: ritorna un puntatore a CryptoWallet essendo covariante come tipo di ritorno a un puntatore SerializableObject
     */
    CryptoWallet * clone() const override;
};


#endif //CRYPTOWALLET_H
