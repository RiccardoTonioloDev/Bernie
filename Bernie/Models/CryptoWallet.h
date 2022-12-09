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
    std::string serialize() const override;
    CryptoWallet * clone() const override;
};


#endif //CRYPTOWALLET_H
