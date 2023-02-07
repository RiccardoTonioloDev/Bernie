#include "Date.h"
#include <string>

Date::Date(short unsigned int d, short unsigned int m, short unsigned int y) : day(d), month(m), year(y) {}

Date::Date(const std::string &strDate) {
    std::string strDateCopy = strDate;
    std::string delimiter = "/";

    size_t pos = 0;
    int fieldNumber = 0;
    std::string fields[2];
    std::string token;
    while ((pos = strDateCopy.find(delimiter)) != std::string::npos) {
        token = strDateCopy.substr(0, pos);
        fields[fieldNumber] = token;
        fieldNumber++;
        strDateCopy.erase(0, pos + delimiter.length());
    }
    day = std::stoi(fields[0]);
    month = std::stoi(fields[1]);
    year = std::stoi(strDateCopy);
}

std::string Date::getData() const {
    return "" + std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}

unsigned short Date::getDay() const {
    return day;
}

unsigned short Date::getMonth() const {
    return month;
}

unsigned short Date::getYear() const {
    return year;
}
