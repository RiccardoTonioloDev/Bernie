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

void EncDec_File::encInFile(const RBBSTree<SerializableObject>& treeToEnc) const{
   std::ofstream file;
   int i = 0;
   std::string correctFlag("[correct]");
   for(std::string::iterator it = correctFlag.begin();it != correctFlag.end(); ++it, ++i){
       *it += key[i%key.length()];
   }
   std::string inputOnFile("");
   inputOnFile += correctFlag + '\n';
   for(RBBSTree<SerializableObject>::const_iterator cit = treeToEnc.begin();cit != treeToEnc.end(); ++cit){
       std::string currentSerialized = cit->serialize();
       for(std::string::iterator it = currentSerialized.begin(); it != currentSerialized.end();++it, i++){
           *it += key[i%key.length() + 11]; //Added 11 to escape the situation where the char with ASCII value 0 is inserted
           //and with a combination of key, the '\n' char is generated, corrupting the file as a result.
       }
       inputOnFile += currentSerialized + '\n';
   }
   file.open(fileName);
   file << inputOnFile;
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
