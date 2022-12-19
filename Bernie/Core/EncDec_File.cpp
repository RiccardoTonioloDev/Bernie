#include "EncDec_File.h"
#include <fstream>
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
   file << inputToEnc;
   file.close();
}
