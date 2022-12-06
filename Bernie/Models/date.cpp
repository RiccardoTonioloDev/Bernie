#include "date.h"

Date::Date(short unsigned int d, short unsigned int m, short unsigned int y): day(d), month(m), year(y) {}

std::string Date::getData() {
    return ""+std::to_string(day)+"/"+std::to_string(month)+"/"+std::to_string(year);
}