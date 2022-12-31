#include "Date.h"
#include <string>

Date::Date(short unsigned int d, short unsigned int m, short unsigned int y): day(d), month(m), year(y) {}
Date::Date(std::string& strDate) {
    std::string delimiter = "/";

    size_t pos = 0;
    int fieldNumber = 0;
    std::string fields[2];
    std::string token;
    while ((pos = strDate.find(delimiter)) != std::string::npos) {
        token = strDate.substr(0, pos);
        fields[fieldNumber] = token;
        fieldNumber++;
        strDate.erase(0, pos + delimiter.length());
    }
    day = std::stoi(fields[0]);
    month = std::stoi(fields[1]);
    year = std::stoi(strDate);
}

std::string Date::getData() const{
    return ""+std::to_string(day)+"/"+std::to_string(month)+"/"+std::to_string(year);
}