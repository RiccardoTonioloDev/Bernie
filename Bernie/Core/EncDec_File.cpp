#include "EncDec_File.h"
#include <iostream>
#include <fstream>
#include <sstream>
EncDec_File::EncDec_File(const std::string &k, const std::string &fN): key(k), fileName(fN){}

bool EncDec_File::encInFile(const RBBSTree<SerializableObject>& treeToEnc) const{
   std::ofstream file(fileName, std::ios::trunc);
   if(file.is_open() != true){
       return false;
   }
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
           *it += key[i%key.length()]+11; //Added 11 to escape the situation where the char with ASCII value 0 is inserted
           //and with a combination of key, the '\n' char is generated, corrupting the file as a result.
       }
       inputOnFile += currentSerialized + '\n';
   }
   //file.open(fileName);
   file << inputOnFile;
   file.close();
   return true;
}

bool EncDec_File::verifyPassword(const std::string& fileName, const std::string& insertedPassword) {
    std::ifstream file;
    file.open(fileName);
    std::string firstLine;
    std::getline(file, firstLine);
    file.close();
    int i = 0;
    for(std::string::iterator it = firstLine.begin(); it != firstLine.end(); ++it,++i){
        *it -= (insertedPassword[i%insertedPassword.length()]);
    }
    return firstLine == "[correct]";
}

std::vector<std::vector<std::string>> EncDec_File::decFromFile() const{
    std::ifstream file;
    file.open(fileName);
    std::string currentLine;
    std::getline(file, currentLine); //ignoring the first line containing "correct" string
    std::vector<std::vector<std::string>> result;
    int i = 9; //during encryption first 9 character of the string "[correct]" increment the value of i... so now that I ignore the first line I have to start with i = 9
    while(std::getline(file, currentLine)){ //reading the line
        for(std::string::iterator it = currentLine.begin();it != currentLine.end(); ++it, ++i)
            *it -= (key[i%key.length()]+11); //decryption of the line
        std::pair<bool, std::vector<std::string>> currentPair = SerializableObject::deSanitize(currentLine); //after decryption I have to deSanitize the string
        result.push_back(currentPair.second);
    }
    file.close();
    return result;
}

