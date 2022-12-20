#include "Account.h"
#include "CryptoWallet.h"
#include "CreditCard.h"
#include "Contact.h"
#include "Note.h"
#include <utility>
#include <vector>
#include <iostream>
#include "RBBSTree.h"
#include "TreeTestingFunctions.h"
#include "SerializationTestingFunctions.h"

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
    RBBSTreeSearchTest(container,"1",true,"search an existing value (1)");
    RBBSTreeSearchTest(container,"prova",false,"search a non existing value (prova)");
    RBBSTreeTest(container,"CONTACT,1,Nome,Cognome,1/1/1,prova prova2,Email"
                           "CREDITCARD,3,provaProva,prova,1/1/1"
                           "ACCOUNT,4,ciao4,come4,stai4"
                           "CRYPTOWALLET,5,blockchainName,1,2,3,4"
                           "ACCOUNT,6,ciao6,come6,stai6"
                           "NOTE,7,ciao7"
                           "ACCOUNT,8,ciao8,come8,stai8","tree insertion");
    RBBSTreeFilterTest<Account>(container,"ACCOUNT,4,ciao4,come4,stai4"
                                          "ACCOUNT,6,ciao6,come6,stai6"
                                          "ACCOUNT,8,ciao8,come8,stai8","filtering tree (multiple account)(ACCOUNT)");
    RBBSTreeFilterTest<CryptoWallet>(container,"CRYPTOWALLET,5,blockchainName,1,2,3,4","filtering tree (CRYPTOWALLET)");
    RBBSTreeFilterTest<Contact>(container,"CONTACT,1,Nome,Cognome,1/1/1,prova prova2,Email","filtering tree (CONTACT)");
    RBBSTreeFilterTest<CreditCard>(container,"CREDITCARD,3,provaProva,prova,1/1/1","filtering tree (CREDITCARD)");
    RBBSTreeFilterTest<Note>(container,"NOTE,7,ciao7","filtering tree (NOTE)");
    container.deleteT("5");
    container.deleteT("1");
    container.deleteT("5");
    container.deleteT("8");
    RBBSTreeFilterTest<SerializableObject>(container,"CREDITCARD,3,provaProva,prova,1/1/1"
                                                     "ACCOUNT,4,ciao4,come4,stai4"
                                                     "ACCOUNT,6,ciao6,come6,stai6"
                                                     "NOTE,7,ciao7","filtering tree (SerializableObject)");
    RBBSTreeSearchTest(container,"1",false,"search a non existing value (1)");
    RBBSTreeTest(container,"CREDITCARD,3,provaProva,prova,1/1/1"
                           "ACCOUNT,4,ciao4,come4,stai4"
                           "ACCOUNT,6,ciao6,come6,stai6"
                           "NOTE,7,ciao7", "tree deletion");
    container.deleteT("4");
    container.deleteT("3");
    container.deleteT("7");
    container.deleteT("6");
    RBBSTreeTest(container,"", "tree deletion (entire tree)");
    RBBSTreeSearchTest(container,"prova",false,"search a non existing value (prova)");
    Account* p4new = new Account("4","ciao4","come4","stai4");
    RBBSInsertionWhenEmptiedTest(container,*p4new,"ACCOUNT,4,ciao4,come4,stai4");
    RBBSTreeDeletionWhenEmptiedTest(container);
    RBBSTreeSearchTest(container,"1",false,"search a non existing value (1)");
    RBBSTreeFilterTest<Account>(container,"ACCOUNT,4,ciao4,come4,stai4","filtering tree (ACCOUNT)");
    RBBSTreeFilterTest<CryptoWallet>(container,"","filtering tree (no CryptoWallet elements)(CRYPTOWALLET)");
    RBBSTreeFilterTest<Contact>(container,"","filtering tree (no Contact elements)(CONTACT)");
    RBBSTreeFilterTest<CreditCard>(container,"","filtering tree (no CreditCard elements)(CREDITCARD)");
    RBBSTreeFilterTest<Note>(container,"","filtering tree (no NOTE elements)(NOTE)");
    std::cout << std::endl;
}