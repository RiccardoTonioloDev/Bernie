#include "../Models/Account.h"
#include "../Models/CryptoWallet.h"
#include "../Models/CreditCard.h"
#include "../Models/Contact.h"
#include "../Models/Note.h"
#include <utility>
#include <vector>
#include <iostream>

void serializationTest(SerializableObject& input, const std::string& expected, const std::string& testName){
    std::string serializedObj = input.serialize();
    if(serializedObj == expected){
        std::cout << "TEST (" + testName + "): \033[32mPASSED\033[0m";
    }else std::cout << "TEST (" + testName + "): \033[31mNOT PASSED\033[0m";
    std::cout << std::endl;
}
void deSanitizationTest(std::string input, const std::pair<bool,std::vector<std::string>>& expected, const std::string& testName){
    std::pair<bool,std::vector<std::string>> couple = SerializableObject::deSanitize(input);
    if(expected.first != couple.first){
        std::cout << "TEST (" + testName + "): \033[31mNOT PASSED\033[0m";
    }else{
       std::vector<std::string>::const_iterator citExpected = expected.second.begin();
       std::vector<std::string>::const_iterator citCouple = couple.second.begin();
       bool areEqual = true;
       while(areEqual && citExpected!=expected.second.end() && citCouple != couple.second.end()){
           if(*citCouple != *citExpected){
               std::cout << std::endl;
               areEqual = false;
           }
           ++citCouple;
           ++citExpected;
       }
       if (areEqual){
           std::cout << "TEST (" + testName + "): \033[32mPASSED\033[0m";
       }else{
           std::cout << "TEST (" + testName + "): \033[31mNOT PASSED\033[0m";
       }
    }
    std::cout << std::endl;
}

int main(){
    std::cout << "//Account Unit Testing -------------------------------------------------------------------------------"<<std::endl;
    Account p1("NameProva1","EmailProva1","PasswordProva1","UsernameProva1");
    serializationTest(p1,std::string("ACCOUNT,NameProva1,EmailProva1,PasswordProva1,UsernameProva1"),std::string("serialization Account 1"));
    deSanitizationTest(p1.serialize(),std::make_pair<bool,std::vector<std::string>>(false,std::vector<std::string>{"ACCOUNT","NameProva1","EmailProva1","PasswordProva1","UsernameProva1"}),"deSanitization Account 1");
    Account pNotCorrupted("&,,",",&&&,","&&,&,&,","&&&&,&,&&,");
    serializationTest(pNotCorrupted,std::string("ACCOUNT,&&&,&,,&,&&&&&&&,,&&&&&,&&&,&&&,,&&&&&&&&&,&&&,&&&&&,"),std::string("serialization stressing on escape and commas"));
    deSanitizationTest(pNotCorrupted.serialize(),std::make_pair<bool,std::vector<std::string>>(false,std::vector<std::string>{"ACCOUNT","&,,",",&&&,","&&,&,&,","&&&&,&,&&,"}),"deSanitization Account notCorrupted");
    std::string corrupted("ACCOUNT,NameProva2,Email&Prova2,PasswordProva2,UsernameProva2");
    deSanitizationTest(corrupted,std::make_pair<bool,std::vector<std::string>>(true,std::vector<std::string>{}),"deSanitization Account Corrupted");
    std::cout << "//CreditCard Unit Testing ----------------------------------------------------------------------------"<<std::endl;
    std::cout << "//Contacts Unit Testing ------------------------------------------------------------------------------"<<std::endl;
    std::cout << "//CryptoWallet Unit Testing --------------------------------------------------------------------------"<<std::endl;
    std::cout << "//Note Unit Testing ----------------------------------------------------------------------------------"<<std::endl;
}