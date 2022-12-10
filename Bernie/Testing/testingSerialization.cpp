#include "../Models/Account.h"
#include <utility>
#include <vector>

int main(){
    Account p1("NameProva1","EmailProva1","PasswordProva1","UsernameProva1");
    std::cout << p1.serialize() << std::endl;
    std::pair<bool, std::vector<std::string>> tuple = SerializableObject::deSanitize(p1.serialize());
    std::cout << "Is corrupted? ";
    std::cout << (std::get<0>(tuple) ? "True" : "False") << std::endl;
    std::cout << "VALUES:" << std::endl;
    for(std::vector<std::string>::const_iterator cit = std::get<1>(tuple).begin();cit != std::get<1>(tuple).end();++cit){
        std::cout << *cit << std::endl;
    }
    std::cout << "###################################################################################" << std::endl;
    Account pNotCorrupted("&,,",",&&&,","&&,&,&,","&&&&,&,&&,");
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