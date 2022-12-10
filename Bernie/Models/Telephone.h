//#notReviewed
#ifndef TELEPHONE_H
#define TELEPHONE_H
#include <string>


class Telephone {
private:
    std::string prefix;
    std::string number;
public:
    Telephone(const std::string&,const std::string&);
    std::string getNumber() const;
};


#endif //TELEPHONE_H
