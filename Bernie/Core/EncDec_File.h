#ifndef ENCDEC_FILE_H
#define ENCDEC_FILE_H

#include <string>
//#include "RBBSTree.h"
#include "RBBSTree2.h"
#include "../Models/SerializableObject.h"


class EncDec_File {
private:
    std::string key;
    std::string fileName;
public:
    EncDec_File(const std::string &k, const std::string &fN);

    bool encInFile(const RBBSTree<SerializableObject> &treeToEnc) const;

    std::vector<std::vector<std::string>> decFromFile() const;

    static bool verifyPassword(const EncDec_File &storage);
};


#endif //ENCDEC_FILE_H
