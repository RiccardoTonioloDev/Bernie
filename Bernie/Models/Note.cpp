#include "Note.h"

Note::Note(const std::string& n, const std::string& t) : SerializableObject(n), text(t) {}

std::string Note::serialize() const {
    std::string serializedStr = "NOTE";
    serializedStr += SerializableObject::SEPARATOR + SerializableObject::sanitize(name) + SerializableObject::SEPARATOR + SerializableObject::sanitize(text);
    return serializedStr;
}

Note* Note::clone() const{
    return new Note(*this);
}