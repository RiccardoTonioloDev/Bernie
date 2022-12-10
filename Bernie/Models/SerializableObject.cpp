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
SerializableObject::~SerializableObject()= default;

std::string SerializableObject::sanitize(const std::string & text) {
    std::string temp;
    for(int i = 0; i < text.length(); i++){
        if(text[i] == ',' || text[i] == '\\')
            temp+='\\';
        temp+=text[i];
    }
    return temp;
}

std::pair<bool, std::vector<std::string>> SerializableObject::deSanitize(const std::string & str) {
    std::vector<std::string> wordsInLine;
    std::string currentString;
    bool isNotCorrupted = true;
    for (int i = 0; i<str.length() && isNotCorrupted; i++) {
       if(str[i] == '\\' ) {
           if ((i + 1) < str.length() && (str[i + 1] == ',' || str[i + 1] == '\\')) currentString += str[i + 1];
           else isNotCorrupted = false;
       }else if(str[i] == ',' ){
           if(str.empty()) isNotCorrupted = false;
           else{
               wordsInLine.push_back(currentString);
               currentString = "";
           }
       }else{
           currentString += str[i];
       }
    }
    if(!currentString.empty()) wordsInLine.push_back(currentString);
    return std::make_pair(isNotCorrupted,wordsInLine);
}