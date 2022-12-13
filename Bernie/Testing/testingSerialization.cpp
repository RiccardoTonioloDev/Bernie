#include "../Models/Account.h"
#include "../Models/CryptoWallet.h"
#include "../Models/CreditCard.h"
#include "../Models/Contact.h"
#include "../Models/Note.h"
#include <utility>
#include <vector>

void serializationTest(SerializableObject& input, const std::string& expected, const std::string& testName){
    std::string serializedObj = input.serialize();
    if(serializedObj == expected){
        std::cout << "TEST (" + testName + "): PASSED";
    }else std::cout << "TEST (" + testName + "): NOT PASSED";
    std::cout << std::endl;
}
void deSanitizationTest(std::string input, const std::pair<bool,std::vector<std::string>>& expected, const std::string& testName){
    std::pair<bool,std::vector<std::string>> couple = SerializableObject::deSanitize(input);
    if(expected.first != couple.first){
        std::cout << "TEST (" + testName + "): NOT PASSED";
    }else{
       std::vector<std::string>::const_iterator citExpected = expected.second.begin();
       std::vector<std::string>::const_iterator citCouple = couple.second.begin();
       bool areEqual = true;
       while(areEqual && citExpected!=expected.second.end() && citCouple != couple.second.end()){
           if(citCouple != citExpected) areEqual = false;
       }
       if (areEqual){
           std::cout << "TEST (" + testName + "): NOT PASSED";
       }else{
            std::cout << "TEST (" + testName + "): NOT PASSED";
       }
    }
}

int main(){
    Account p1("NameProva1","EmailProva1","PasswordProva1","UsernameProva1");
    serializationTest(p1,std::string("ACCOUNT,NameProva1,EmailProva1,PasswordProva1,UsernameProva1"),std::string("Account 1"));
    deSanitizationTest(p1.serialize(),std::make_pair<bool,std::vector<std::string>>())
    /*
    std::cout << p1.serialize() << std::endl;
    std::pair<bool, std::vector<std::string>> tuple = SerializableObject::deSanitize(p1.serialize());
    std::cout << "Is corrupted? ";
    std::cout << (std::get<0>(tuple) ? "True" : "False") << std::endl;
    std::cout << "VALUES:" << std::endl;
    for(std::vector<std::string>::const_iterator cit = std::get<1>(tuple).begin();cit != std::get<1>(tuple).end();++cit){
        std::cout << *cit << std::endl;
    }
     */
    std::cout << "###################################################################################" << std::endl;
    Account pNotCorrupted("&,,",",&&&,","&&,&,&,","&&&&,&,&&,");
    serializationTest(pNotCorrupted,std::string("ACCOUNT,&&&,&,,&,&&&&&&&,,&&&&&,&&&,&&&,,&&&&&&&&&,&&&,&&&&&,"),std::string("Stressing on escape and commas"));
    std::cout << pNotCorrupted.serialize() << std::endl;
    std::pair<bool, std::vector<std::string>> tupleNotCorrupted = SerializableObject::deSanitize(pNotCorrupted.serialize());
    std::cout << "Is corrupted? ";
    std::cout << (std::get<0>(tupleNotCorrupted) ? "True" : "False") << std::endl;
    std::cout << "VALUES:" << std::endl;
    for(std::vector<std::string>::const_iterator cit = std::get<1>(tupleNotCorrupted).begin();cit != std::get<1>(tupleNotCorrupted).end();++cit){
        std::cout << *cit << std::endl;
    }
    std::cout << "###################################################################################" << std::endl;
    std::string corrupted("ACCOUNT,NameProva2,Email&Prova2,PasswordProva2,UsernameProva2");
    std::pair<bool, std::vector<std::string>> tupleCorrupted = SerializableObject::deSanitize(corrupted);
    std::cout << "Is corrupted? ";
    std::cout << (std::get<0>(tupleCorrupted) ? "True" : "False") << std::endl;
    std::cout << "VALUES:" << std::endl;
    for(std::vector<std::string>::const_iterator cit = std::get<1>(tupleCorrupted).begin();cit != std::get<1>(tupleCorrupted).end();++cit){
        std::cout << *cit << std::endl;
    }
}