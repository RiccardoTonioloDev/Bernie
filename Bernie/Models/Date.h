#ifndef DATE
#define DATE

#include <iostream>

class Date {
private:
    unsigned short int day;
    unsigned short int month;
    unsigned short int year;
public:
    Date(short unsigned int d = 0, short unsigned int m = 0, short unsigned int y = 0);

    Date(const std::string &strDate);

    /*
    POST: si ritorna una stringa composta da tutti i campi della data nel formato gg/mm/aaaa
    */
    std::string getData() const;
};

#endif