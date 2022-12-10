//#notReviewed
#include "Telephone.h"

Telephone::Telephone(const std::string & p, const std::string & n): prefix(p), number(n) {}

std::string Telephone::getNumber() const {
    return prefix + " " + number;
}