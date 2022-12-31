#ifndef VAULTTESTINGFUNCTIONS_H
#define VAULTTESTINGFUNCTIONS_H
#include "../Bernie/Models/Vault.h"
#include "TreeTestingFunctions.h"

void readFileNamesTest(const Vault& input, const std::vector<std::string> expected, const std::string& testName);
void loadFromStorageTest(Vault& input, std::pair<std::string, std::string> nameAndPass, std::pair<bool,const std::vector<std::string>>  expected, const std::string& testName);
void loadToStorageTest(Vault& input, std::pair<std::string, std::string> nameAndPass, std::pair<bool,const std::vector<std::string>>  expected, const std::string& testName);

#endif //VAULTTESTINGFUNCTIONS_H
