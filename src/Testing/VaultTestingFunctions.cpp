#include "VaultTestingFunctions.h"

void readFileNamesTest(const Vault &input, const std::vector<std::string> expected, const std::string &testName) {
    if (input.fetchDBNames() == expected) std::cout << "TEST (" + testName + "): \033[92mPASSED\033[0m";
    else std::cout << "TEST (" + testName + "): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void loadFromStorageTest(Vault &input, std::pair<std::string, std::string> nameAndPass,
                         std::pair<bool, const std::vector<std::string>> expected, const std::string &testName) {
    bool isLoadingFailed = input.loadStorage(nameAndPass.first, nameAndPass.second);
    if (isLoadingFailed != expected.first) {
        std::cout << "TEST (" + testName + "): \033[91mNOT PASSED\033[0m";
        return;
    }
    auto srlObjVec = input.vectorize();
    std::vector<std::string> serializedVec;
    for (auto &srlObj: srlObjVec) serializedVec.push_back(srlObj->serialize());
    if (expected.second == serializedVec) std::cout << "TEST (" + testName + "): \033[92mPASSED\033[0m";
    else std::cout << "TEST (" + testName + "): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void loadToStorageTest(Vault &input, std::pair<std::string, std::string> nameAndPass,
                       std::pair<bool, const std::vector<std::string>> expected, const std::string &testName) {
    loadFromStorageTest(input, nameAndPass, expected, testName);
}
