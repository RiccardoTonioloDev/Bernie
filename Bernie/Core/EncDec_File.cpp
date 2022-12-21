#include "EncDec_File.h"
#include <fstream>
#include <sstream>
EncDec_File::EncDec_File(const std::string &k, const std::string &fN): key(k), fileName(fN){}

bool EncDec_File::fileExists() const {
    if (FILE *file = fopen(fileName.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void EncDec_File::encInFile(std::string inputToEnc) {
   std::ofstream file;
   int i = 0;
   for(std::string::iterator it = inputToEnc.begin();it != inputToEnc.end(); ++it, ++i){
        *it += key[i%key.length()];
   }
   file.open(fileName);
   file << "[correct]\n";
   file << inputToEnc;
   file.close();
}

std::vector<std::vector<std::string>> EncDec_File::decFromFile() const{
    std::ifstream file;
    file.open(fileName);
    std::string currentLine;
    std::getline(file, currentLine); //ignoring the first line containing "correct" string
    std::vector<std::vector<std::string>> result;
    int i = 0;
    while(std::getline(file, currentLine)){ //reading the line
        for(std::string::iterator it = currentLine.begin();it != currentLine.end(); ++it, ++i)
            *it -= key[i%key.length()]; //decryption of the line
        std::vector<std::string> currentLineVector;
        std::pair<bool, std::vector<std::string>> currentPair = SerializableObject::deSanitize(currentLine); //after decryption I have to deSanitize the string
        if(currentPair.first)
            result.push_back(currentLineVector);
        }
    return result;
}
