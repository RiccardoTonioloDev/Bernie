#ifndef TELEPHONE_H
#define TELEPHONE_H
#include <string>


class Telephone {
private:
    std::string prefix;
    std::string number;
public:
    Telephone(const std::string& prefix,const std::string& number);
    /*
     * POST: restituisce il numero di telefono sotto forma di stringa.
     */
    std::string getNumber() const;
};


#endif //TELEPHONE_H
