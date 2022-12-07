//#notReviewed
#include "Note.h"

Note::Note(const std::string& n, const std::string& t) : SerializableObject(n), text(t) {}

std::string Note::Serialize(){
    return "NOTE,"+text;
}

Note* Note::clone(){
    return new Note(*this);
}