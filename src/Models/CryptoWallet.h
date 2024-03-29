#ifndef CRYPTOWALLET_H
#define CRYPTOWALLET_H

#include "SerializableObject.h"
#include <string>
#include <iostream>
#include <vector>

class CryptoWallet : public SerializableObject {
private:
    std::string blockchain_name;
    std::vector<std::string> words;

public:
    CryptoWallet(const std::string &name, const std::string &blockchainName, const std::vector<std::string> &words);

    CryptoWallet(const std::vector<std::string> &serializedVectorized);

    /*
     * POST: ritorna sotto forma di string l'oggetto CryptoWallet, usando come carattere separatore la ",".
     */
    std::string serialize() const override;

    virtual bool modify(const SerializableObject *) override;

    /*
     * POST: ritorna un puntatore a CryptoWallet essendo covariante come tipo di ritorno a un puntatore SerializableObject
     */
    CryptoWallet *clone() const override;

    void accept(SerializableObjectsVisitor *visit, bool toEdit = false) const override;

    const std::string &getBlockchainName() const;

    const std::vector<std::string> &getWords() const;
};


#endif //CRYPTOWALLET_H
