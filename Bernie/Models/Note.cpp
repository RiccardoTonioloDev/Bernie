//#notReviewed
#include "Note.h"

Note::Note(const std::string& n, const std::string& t) : SerializableObject(n), text(t) {}

std::string Note::serialize() const {
    return "NOTE,"+text;
}

Note* Note::clone() const{
    return new Note(*this);
}