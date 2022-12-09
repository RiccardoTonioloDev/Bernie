//#notReviewed
#include "SerializableObject.h"

SerializableObject::SerializableObject(const std::string& n): name(n){
}
virtual SerializableObject* clone const{
    return new SerializableObject(*this);
}
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
static std::string SerializableObject::sanitize(const std::string &) {}
static std::string SerializableObject::deSanitize(const std::string &) {}
