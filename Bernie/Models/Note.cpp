#include "Note.h"

Note::Note(const std::string &n, const std::string &t) : SerializableObject(n), text(t) {}

Note::Note(const std::vector<std::string> &serializedVectorized) : SerializableObject(serializedVectorized[1]),
                                                                   text(serializedVectorized[2]) {}

std::string Note::serialize() const {
    std::string serializedStr = "NOTE";
    serializedStr +=
            SerializableObject::SEPARATOR + SerializableObject::sanitize(name) + SerializableObject::SEPARATOR +
            SerializableObject::sanitize(text);
    return serializedStr;
}

Note *Note::clone() const {
    return new Note(*this);
}

void Note::accept(SerializableObjectsVisitor *visitor, bool toEdit) const {
    visitor->visit(*this, toEdit);
}

bool Note::modify(const SerializableObject *ptr) {
    if (dynamic_cast<const Note *>(ptr)) {
        *this = *(static_cast<const Note *>(ptr));
        return true;
    }
    return false;
}

const std::string &Note::getText() const {
    return text;
}
