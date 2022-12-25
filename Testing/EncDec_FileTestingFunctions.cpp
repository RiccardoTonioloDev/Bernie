#include "EncDec_FileTestingFunctions.h"
#include <iostream>

void encInFileTest(const RBBSTree<SerializableObject>& input, const std::string& expected, const std::string& testName){
    EncDec_File prova("1234","../prova.txt");
    bool isOpen = prova.encInFile(input);
    if(isOpen) std::cout << "TEST ("+testName+"): \033[92mSEE IN THE SAVINGS FOLDER\033[0m";
    else std::cout << "TEST ("+testName+"): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void VerifyPasswordInFileTest(const RBBSTree<SerializableObject>& input, bool expected,  const std::string& password, const std::string& testName){
    EncDec_File prova("1234","../prova.txt");
    if(EncDec_File::verifyPassword("../prova.txt", password) == expected) std::cout << "TEST ("+testName+"): \033[92mPASSED\033[0m";
    else std::cout << "TEST ("+testName+"): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void decFromFileTest(const RBBSTree<SerializableObject>& input,const std::string& expected, const std::string& testName){
    EncDec_File prova("1234", "../prova.txt");
    std::vector<std::vector<std::string>> result = prova.decFromFile();

    std::string readStr = "";
    for(auto ext = result.begin(); ext != result.end(); ++ext){
        for(auto it = ext[0].begin(); it != ext[0].end(); ++it){
            readStr+=*it + " ";
        }
        readStr+='\n';
    }
    if(readStr == expected) std::cout << "TEST ("+testName+"): \033[92mPASSED\033[0m";
    else std::cout << "TEST ("+testName+"): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}