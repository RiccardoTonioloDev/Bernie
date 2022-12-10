//#notReviewed
#include "SerializableObject.h"

SerializableObject::SerializableObject(const std::string& n): name(n){}

char SerializableObject::SEPARATOR = '&';

bool SerializableObject::operator==(const SerializableObject & obj) const {
    return name == obj.name;
}
bool SerializableObject::operator<(const SerializableObject & obj) const {
    return name < obj.name;
}
bool SerializableObject::operator>(const SerializableObject & obj) const {
    return name > obj.name;
}
SerializableObject::~SerializableObject()= default;

std::string SerializableObject::sanitize(const std::string & text) {
    std::string temp;
    for(int i = 0; i < text.length(); i++){
        if(text[i] == ',' || text[i] == SerializableObject::SEPARATOR)
            temp+=SerializableObject::SEPARATOR;
        temp+=text[i];
    }
    return temp;
}

std::pair<bool, std::vector<std::string>> SerializableObject::deSanitize(const std::string & str) {
    std::vector<std::string> wordsInLine;
    std::string currentString;
    bool isCorrupted = false;
    for (int i = 0; i<str.length() && !isCorrupted; i++) {
       if(str[i] == SerializableObject::SEPARATOR) {
           if ((i + 1) < str.length() && (str[i + 1] == ',' || str[i + 1] == SerializableObject::SEPARATOR)){
               currentString += str[i + 1];
               i++;
           }
           else isCorrupted = true;
       }else if(str[i] == ',' ){
           if(str.empty()) isCorrupted = true;
           else{
               wordsInLine.push_back(currentString);
               currentString = "";
           }
       }else currentString += str[i];
    }
    if(!currentString.empty()) wordsInLine.push_back(currentString);
    return std::make_pair(isCorrupted,wordsInLine);
}