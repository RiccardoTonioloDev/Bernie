#include "EncDec_FileTestingFunctions.h"
#include <iostream>

void encInFileTest(const RBBSTree<SerializableObject>& input, const std::string& expected, const std::string& testName){
    EncDec_File prova("1234","prova.txt");
    bool isOpen = prova.encInFile(input);
    if(isOpen) std::cout << "TEST ("+testName+"): \033[92mSEE IN THE SAVINGS FOLDER\033[0m";
    else std::cout << "TEST ("+testName+"): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}
