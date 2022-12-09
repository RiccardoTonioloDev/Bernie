//#notReviewed
#include "SerializableObject.h"

SerializableObject::SerializableObject(const std::string& n): name(n){}

bool SerializableObject::operator==(const SerializableObject & obj) const {
    return name == obj.name;
}
bool SerializableObject::operator<(const SerializableObject & obj) const {
    return name < obj.name;
}
bool SerializableObject::operator>(const SerializableObject & obj) const {
    return name > obj.name;
}
SerializableObject::~SerializableObject(){}

std::string SerializableObject::sanitize(const std::string & text) {
    std::string temp = "";
    for(int i = 0; i < text.length(); i++){
        if(text[i] == ',' || text[i] == '\\')
            temp+='\\';
        temp+=text[i];
    }
    return temp;
}

std::string SerializableObject::deSanitize(const std::string &) {}
