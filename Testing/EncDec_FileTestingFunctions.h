#ifndef ENCDEC_FILETESTINGFUNCTIONS_H
#define ENCDEC_FILETESTINGFUNCTIONS_H

#include "../Bernie/Core/RBBSTree.h"
#include "../Bernie/Core/EncDec_File.h"
#include "../Bernie/Models/SerializableObject.h"

void encInFileTest(const RBBSTree<SerializableObject> &input, const std::string &expected, const std::string &testName);

void VerifyPasswordInFileTest(const std::string &fileName, bool expected, const std::string &password,
                              const std::string &testName);

void
decFromFileTest(const RBBSTree<SerializableObject> &input, const std::string &expected, const std::string &testName);

#endif //ENCDEC_FILETESTINGFUNCTIONS_H
