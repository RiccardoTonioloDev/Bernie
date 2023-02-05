#include "CryptoWallet.h"

CryptoWallet::CryptoWallet(const std::string &n, const std::string &bn, const std::vector<std::string> &w)
        : SerializableObject(n), blockchain_name(bn), words(w) {}

CryptoWallet::CryptoWallet(const std::vector<std::string> &serializedVectorized) : SerializableObject(
        serializedVectorized[1]), blockchain_name(serializedVectorized[2]), words(serializedVectorized.begin() + 3,
                                                                                  serializedVectorized.end()) {}

CryptoWallet *CryptoWallet::clone() const {
    return new CryptoWallet(*this);
}

std::string CryptoWallet::serialize() const {
    std::string serializedObj = "CRYPTOWALLET";
    serializedObj += SerializableObject::SEPARATOR;
    serializedObj = serializedObj + sanitize(name) + SerializableObject::SEPARATOR;
    serializedObj = serializedObj + sanitize(blockchain_name);
    for (std::vector<std::string>::const_iterator cit = words.begin(); cit != words.end(); ++cit) {
        serializedObj += SerializableObject::SEPARATOR + sanitize((*cit));
    }
    return serializedObj;
}

void CryptoWallet::accept(SerializableObjectsVisitor *visit) const {
    visit->visit(*this);
}

bool CryptoWallet::modify(const SerializableObject *ptr) {
    if (dynamic_cast<const CryptoWallet *>(ptr)) {
        *this = *(static_cast<const CryptoWallet *>(ptr));
        return true;
    }
    return false;
}