#include "../Models/Account.h"
#include <utility>
#include <vector>

int main(){
    Account p1("NameProva1","EmailProva1","PasswordProva1","UsernameProva1");
    std::cout << p1.serialize() << std::endl;
    std::pair<bool, std::vector<std::string>> tuple = SerializableObject::deSanitize(p1.serialize());
    std::cout << "Is corrupted? ";
    std::cout << ((std::get<0>(tuple) = true) ? "False" : "True") << std::endl;
    std::cout << "VALUES:" << std::endl;
    for(std::vector<std::string>::const_iterator cit = std::get<1>(tuple).begin();cit != std::get<1>(tuple).end();++cit){
        std::cout << *cit << std::endl;
    }
}