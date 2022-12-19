#ifndef ENCDEC_FILE_H
#define ENCDEC_FILE_H
#include <string>
#include "RBBSTree.h"


class EncDec_File {
private:
    std::string key;
    std::string fileName;
public:
    EncDec_File(const std::string& k, const std::string& fN);
    bool fileExists() const;
    void encInFile(std::string inputToEnc);
};


#endif //ENCDEC_FILE_H
