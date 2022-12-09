//#notReviewed

#include "CryptoWallet.h"

CryptoWallet::CryptoWallet(const std::string &n, const std::string &bn, const std::vector <std::string> &w) {}

CryptoWallet *CryptoWallet::clone() const {
    return new CryptoWallet(*this);
}

std::string CryptoWallet::serialize() const {
    std::string serializedObj = "CRYPTOWALLET,";
    serializedObj = serializedObj + name + ",";
    serializedObj = serializedObj + blockchain_name;
    for (std::vector<std::string>::const_iterator cit = words.begin(); cit != words.end(); ++cit) {
       serializedObj = serializedObj + "," + (*cit);
    }
    return serializedObj;
}