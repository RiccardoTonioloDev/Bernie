#include "../Models/Account.h"
#include "../Models/CryptoWallet.h"
#include "../Models/CreditCard.h"
#include "../Models/Contact.h"
#include "../Models/Note.h"
#include <utility>
#include <vector>
#include <iostream>
#include "../Core/RBBSTree.h"


void serializationTest(SerializableObject& input, const std::string& expected, const std::string& testName){
    std::string serializedObj = input.serialize();
    /*
    std::cout << input.serialize() << std::endl;
    std::cout << expected << std::endl;
     */
    if(serializedObj == expected){
        std::cout << "TEST (" + testName + "): \033[32mPASSED\033[0m";
    }else std::cout << "TEST (" + testName + "): \033[31mNOT PASSED\033[0m";
    std::cout << std::endl;
}
void deSanitizationTest(const std::string& input, const std::pair<bool,std::vector<std::string>>& expected, const std::string& testName){
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

void RBBSTreeTest(const RBBSTree<SerializableObject>& input, const std::string& expected, const std::string& testName){
    std::string saved("");
    RBBSTree<SerializableObject>::const_iterator cit;
    for(cit = input.begin();cit != input.end(); ++cit){
       saved = saved + cit->serialize();
    }
    if(saved == expected) std::cout << "TEST (" + testName + "): \033[32mPASSED\033[0m";
    else std::cout << "TEST (" + testName + "): \033[31mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void RBBSInsertionWhenEmptied(RBBSTree<SerializableObject>& tree,const SerializableObject& input,const std::string& expectedInside){
    tree.insert(&input);
    std::string saved("");
    RBBSTree<SerializableObject>::const_iterator cit = tree.begin();
    saved = cit->serialize();
    if(saved == expectedInside) std::cout << "TEST (insertion when emptied): \033[32mPASSED\033[0m";
    else std::cout << "TEST (insertion when emptied): \033[31mNOT PASSED\033[0m";
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
    std::string corruptedAccount("ACCOUNT,NameProva2,Email&Prova2,PasswordProva2,UsernameProva2");
    deSanitizationTest(corruptedAccount,std::make_pair<bool,std::vector<std::string>>(true,std::vector<std::string>{}),"deSanitization Account Corrupted");
    std::cout << std::endl;


    std::cout << "//CreditCard Unit Testing ----------------------------------------------------------------------------"<<std::endl;
    Date d1(1,1,1);
    CreditCard c1("NameProva","provaProva","prova",d1);
    serializationTest(c1,std::string("CREDITCARD,NameProva,provaProva,prova,1/1/1"),"serialization CreditCard 1");
    deSanitizationTest(c1.serialize(),std::make_pair(false,std::vector<std::string>{"CREDITCARD","NameProva","provaProva","prova",d1.getData()}),"deSanitization CreditCard 1");
    CreditCard cNotCorrupted("&,,",",&,&,","&&&,",d1);
    serializationTest(cNotCorrupted,std::string("CREDITCARD,&&&,&,,&,&&&,&&&,,&&&&&&&,,1/1/1"),"serialization CreditCard notCorrupted");
    deSanitizationTest(cNotCorrupted.serialize(),std::make_pair(false,std::vector<std::string>{"CREDITCARD","&,,",",&,&,","&&&,",d1.getData()}),"deSanitization CreditCard notCorrupted");
    std::string corruptedCreditCard("CREDITCARD,Nam&eProva,provaProva,prova,1/1/1");
    deSanitizationTest(corruptedCreditCard,std::make_pair(true,std::vector<std::string>{}),"deSanitization CreditCard Corrupted");
    std::cout << std::endl;


    std::cout << "//Contact Unit Testing ------------------------------------------------------------------------------"<<std::endl;
    Telephone t1("prova","prova2");
    Contact co1("NomeProva","Nome","Cognome",d1,t1,"Email");
    serializationTest(co1, std::string("CONTACT,NomeProva,Nome,Cognome,1/1/1,prova prova2,Email"),"serialization Contact 1");
    deSanitizationTest(co1.serialize(),std::make_pair(false,std::vector<std::string>{"CONTACT","NomeProva","Nome","Cognome",d1.getData(),t1.getNumber(),"Email"}),"deSanitization Contact 1");
    Contact coNotCorrupted("&,,",",&&,","&",d1,t1,"");
    serializationTest(coNotCorrupted,std::string("CONTACT,&&&,&,,&,&&&&&,,&&,1/1/1,prova prova2,"),"serialization Contact notCorrupted");
    deSanitizationTest(coNotCorrupted.serialize(),std::make_pair(false, std::vector<std::string>{"CONTACT","&,,",",&&,","&",d1.getData(),t1.getNumber(),""}),"deSanitization Contact notCorrupted");
    std::string corruptedContact("CONTACT,NomeProv&a,Nome,Cognome,1/1/1,prova prova2,Email");
    deSanitizationTest(corruptedContact,std::make_pair(true, std::vector<std::string>{}),"deSanitization Contact Corrupted");
    std::cout << std::endl;


    std::cout << "//CryptoWallet Unit Testing --------------------------------------------------------------------------"<<std::endl;
    CryptoWallet cr1("NomeProva","blockchainName",std::vector<std::string>{"1","2","3","4"});
    serializationTest(cr1,std::string("CRYPTOWALLET,NomeProva,blockchainName,1,2,3,4"),"serialization CryptoWallet 1");
    deSanitizationTest(cr1.serialize(), std::make_pair(false,std::vector<std::string>{"CRYPTOWALLET","NomeProva","blockchainName","1","2","3","4"}), "deSanitization CryptoWallet 1");
    CryptoWallet crNotCorrupted("&&,","",std::vector<std::string>{"&&,","",",,&"});
    serializationTest(crNotCorrupted,std::string("CRYPTOWALLET,&&&&&,,,&&&&&,,,&,&,&&"),"serialization CryptoWallet notCorrupted");
    deSanitizationTest(crNotCorrupted.serialize(),std::make_pair(false, std::vector<std::string>{"CRYPTOWALLET","&&,","","&&,","",",,&"}),"deSanitization CryptoWallet notCorrupted");
    std::string corruptedCryptoWallet("CRYPTOWAL&LET,NomeProva,blockchainName,1,2,3,4");
    deSanitizationTest(corruptedCryptoWallet, std::make_pair(true, std::vector<std::string>{}), "deSanitization CryptoWallet Corrupted");
    std::cout << std::endl;

    std::cout << "//Note Unit Testing ----------------------------------------------------------------------------------"<<std::endl;
    Note n1("NomeProva","Prova");
    serializationTest(n1,std::string("NOTE,NomeProva,Prova"),"serialization Note 1");
    deSanitizationTest(n1.serialize(), std::make_pair(false,std::vector<std::string>{"NOTE","NomeProva","Prova"}),"deSanitization Note 1");
    Note nNotCorrupted("","&&,&&");
    serializationTest(nNotCorrupted,std::string("NOTE,,&&&&&,&&&&"),"serialization Note notCorrupted");
    deSanitizationTest(nNotCorrupted.serialize(), std::make_pair(false,std::vector<std::string>{"NOTE","","&&,&&"}),"deSanitization Note notCorrupted");
    std::string corruptedNote("NOTE,pr&ova,prov&a");
    deSanitizationTest(corruptedNote,std::make_pair(true, std::vector<std::string>{}),"deSanitization Note Corrupted");
    std::cout << std::endl;

    std::cout << "//Tree Unit Testing ----------------------------------------------------------------------------------"<<std::endl;
    RBBSTree<SerializableObject> container;
    CryptoWallet* p5 = new CryptoWallet("5","blockchainName",std::vector<std::string>{"1","2","3","4"});;
    CreditCard* p3 = new CreditCard("3","provaProva","prova",d1);;
    Note* p7 = new Note("7","ciao7");
    Contact* p1p = new Contact("1","Nome","Cognome",d1,t1,"Email");
    Account* p4 = new Account("4","ciao4","come4","stai4");
    Account* p6 = new Account("6","ciao6","come6","stai6");
    Account* p8 = new Account("8","ciao8","come8","stai8");
    container.insert(p5);
    container.insert(p3);
    container.insert(p7);
    container.insert(p1p);
    container.insert(p4);
    container.insert(p6);
    container.insert(p8);
    RBBSTreeTest(container,"CONTACT,1,Nome,Cognome,1/1/1,prova prova2,Email"
                           "CREDITCARD,3,provaProva,prova,1/1/1"
                           "ACCOUNT,4,ciao4,come4,stai4"
                           "CRYPTOWALLET,5,blockchainName,1,2,3,4"
                           "ACCOUNT,6,ciao6,come6,stai6"
                           "NOTE,7,ciao7"
                           "ACCOUNT,8,ciao8,come8,stai8","tree insertion");
    container.deleteT("5");
    container.deleteT("1");
    container.deleteT("5");
    container.deleteT("8");
    RBBSTreeTest(container,"CREDITCARD,3,provaProva,prova,1/1/1"
                           "ACCOUNT,4,ciao4,come4,stai4"
                           "ACCOUNT,6,ciao6,come6,stai6"
                           "NOTE,7,ciao7", "tree deletion");
    container.deleteT("4");
    container.deleteT("3");
    container.deleteT("7");
    container.deleteT("6");
    RBBSTreeTest(container,"", "tree deletion (entire tree)");
    Account* p4new = new Account("4","ciao4","come4","stai4");
    RBBSInsertionWhenEmptied(container,*p4new,"ACCOUNT,4,ciao4,come4,stai4");
    std::cout << std::endl;

    std::cout << "//Garbage to get rid off -----------------------------------------------------------------------------"<<std::endl;
    std::cout << "risultato ricerca account 8:" << (container.search("8")? "PRESENTE" : "ASSENTE") << std::endl;
    std::cout << "risultato ricerca account 13:" << (container.search("13")? "PRESENTE" : "ASSENTE") << std::endl;
    std::cout << std::endl;
}