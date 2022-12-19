#include "CryptoWallet.h"

CryptoWallet::CryptoWallet(const std::string &n, const std::string &bn, const std::vector <std::string> &w): SerializableObject(n), blockchain_name(bn), words(w) {}

CryptoWallet *CryptoWallet::clone() const {
    return new CryptoWallet(*this);
}

std::string CryptoWallet::serialize() const {
    std::string serializedObj = "CRYPTOWALLET";
    serializedObj += SerializableObject::SEPARATOR;
    serializedObj = serializedObj + sanitize(name) + ",";
    serializedObj = serializedObj + sanitize(blockchain_name);
    for (std::vector<std::string>::const_iterator cit = words.begin(); cit != words.end(); ++cit) {
       serializedObj +=  SerializableObject::SEPARATOR + sanitize((*cit));
    }
    return serializedObj;
}