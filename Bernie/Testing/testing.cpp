#include "Vault.h"
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
#include "EncDec_FileTestingFunctions.h"
#include "VaultTestingFunctions.h"

int main() {
    std::cout
            << "//Account Unit Testing -------------------------------------------------------------------------------"
            << std::endl;
    Account p1("NameProva1", "EmailProva1", "PasswordProva1", "UsernameProva1");
    serializationTest(p1, std::string("ACCOUNT,NameProva1,EmailProva1,PasswordProva1,UsernameProva1"),
                      std::string("serialization Account 1"));
    deSanitizationTest(p1.serialize(), std::make_pair<bool, std::vector<std::string>>(false, std::vector<std::string>{
            "ACCOUNT", "NameProva1", "EmailProva1", "PasswordProva1", "UsernameProva1"}), "deSanitization Account 1");
    deSanitizationTest(Account(std::vector<std::string>{"ACCOUNT", "NameProva1", "EmailProva1", "PasswordProva1",
                                                        "UsernameProva1"}).serialize(),
                       std::make_pair<bool, std::vector<std::string>>(false,
                                                                      std::vector<std::string>{"ACCOUNT", "NameProva1",
                                                                                               "EmailProva1",
                                                                                               "PasswordProva1",
                                                                                               "UsernameProva1"}),
                       "Creating Account with vector");
    Account pNotCorrupted("&,,", ",&&&,", "&&,&,&,", "&&&&,&,&&,");
    serializationTest(pNotCorrupted, std::string("ACCOUNT,&&&,&,,&,&&&&&&&,,&&&&&,&&&,&&&,,&&&&&&&&&,&&&,&&&&&,"),
                      std::string("serialization stressing on escape and commas"));
    deSanitizationTest(pNotCorrupted.serialize(), std::make_pair<bool, std::vector<std::string>>(false,
                                                                                                 std::vector<std::string>{
                                                                                                         "ACCOUNT",
                                                                                                         "&,,", ",&&&,",
                                                                                                         "&&,&,&,",
                                                                                                         "&&&&,&,&&,"}),
                       "deSanitization Account notCorrupted");
    std::string corruptedAccount("ACCOUNT,NameProva2,Email&Prova2,PasswordProva2,UsernameProva2");
    deSanitizationTest(corruptedAccount,
                       std::make_pair<bool, std::vector<std::string>>(true, std::vector<std::string>{}),
                       "deSanitization Account Corrupted");
    std::cout << std::endl;


    std::cout
            << "//CreditCard Unit Testing ----------------------------------------------------------------------------"
            << std::endl;
    Date d1(1, 1, 1);
    CreditCard c1("NameProva", "OwnerProva", "provaProva", "prova", d1);
    serializationTest(c1, std::string("CREDITCARD,NameProva,OwnerProva,provaProva,prova,1/1/1"),
                      "serialization CreditCard 1");
    deSanitizationTest(c1.serialize(), std::make_pair(false,
                                                      std::vector<std::string>{"CREDITCARD", "NameProva", "OwnerProva",
                                                                               "provaProva", "prova", d1.getData()}),
                       "deSanitization CreditCard 1");
    CreditCard cNotCorrupted("&,,", "OwnerProva", ",&,&,", "&&&,", d1);
    serializationTest(cNotCorrupted, std::string("CREDITCARD,&&&,&,,OwnerProva,&,&&&,&&&,,&&&&&&&,,1/1/1"),
                      "serialization CreditCard notCorrupted");
    deSanitizationTest(cNotCorrupted.serialize(), std::make_pair(false, std::vector<std::string>{"CREDITCARD", "&,,",
                                                                                                 "OwnerProva", ",&,&,",
                                                                                                 "&&&,", d1.getData()}),
                       "deSanitization CreditCard notCorrupted");
    deSanitizationTest(CreditCard(
                               std::vector<std::string>{"CREDITCARD", "&,,", "OwnerProva", ",&,&,", "&&&,", d1.getData()}).serialize(),
                       std::make_pair(false,
                                      std::vector<std::string>{"CREDITCARD", "&,,", "OwnerProva", ",&,&,", "&&&,",
                                                               d1.getData()}),
                       "Creating CreditCard with string vector");
    std::string corruptedCreditCard("CREDITCARD,Nam&eProva,OwnerProva,provaProva,prova,1/1/1");
    deSanitizationTest(corruptedCreditCard, std::make_pair(true, std::vector<std::string>{}),
                       "deSanitization CreditCard Corrupted");
    std::cout << std::endl;


    std::cout << "//Contact Unit Testing ------------------------------------------------------------------------------"
              << std::endl;
    Telephone t1("prova", "prova2");
    Contact co1("NomeProva", "Nome", "Cognome", d1, t1, "Email");
    serializationTest(co1, std::string("CONTACT,NomeProva,Nome,Cognome,1/1/1,prova prova2,Email"),
                      "serialization Contact 1");
    deSanitizationTest(co1.serialize(), std::make_pair(false, std::vector<std::string>{"CONTACT", "NomeProva", "Nome",
                                                                                       "Cognome", d1.getData(),
                                                                                       t1.getNumber(), "Email"}),
                       "deSanitization Contact 1");
    Contact coNotCorrupted("&,,", ",&&,", "&", d1, t1, "");
    serializationTest(coNotCorrupted, std::string("CONTACT,&&&,&,,&,&&&&&,,&&,1/1/1,prova prova2,"),
                      "serialization Contact notCorrupted");
    deSanitizationTest(coNotCorrupted.serialize(), std::make_pair(false,
                                                                  std::vector<std::string>{"CONTACT", "&,,", ",&&,",
                                                                                           "&", d1.getData(),
                                                                                           t1.getNumber(), ""}),
                       "deSanitization Contact notCorrupted");
    deSanitizationTest(Contact(std::vector<std::string>{"CONTACT", "&,,", ",&&,", "&", d1.getData(), t1.getNumber(),
                                                        ""}).serialize(), std::make_pair(false,
                                                                                         std::vector<std::string>{
                                                                                                 "CONTACT", "&,,",
                                                                                                 ",&&,", "&",
                                                                                                 d1.getData(),
                                                                                                 t1.getNumber(), ""}),
                       "Creating Contact with string vector");
    std::string corruptedContact("CONTACT,NomeProv&a,Nome,Cognome,1/1/1,prova prova2,Email");
    deSanitizationTest(corruptedContact, std::make_pair(true, std::vector<std::string>{}),
                       "deSanitization Contact Corrupted");
    std::cout << std::endl;


    std::cout
            << "//CryptoWallet Unit Testing --------------------------------------------------------------------------"
            << std::endl;
    CryptoWallet cr1("NomeProva", "blockchainName", std::vector<std::string>{"1", "2", "3", "4"});
    serializationTest(cr1, std::string("CRYPTOWALLET,NomeProva,blockchainName,1,2,3,4"),
                      "serialization CryptoWallet 1");
    deSanitizationTest(cr1.serialize(), std::make_pair(false, std::vector<std::string>{"CRYPTOWALLET", "NomeProva",
                                                                                       "blockchainName", "1", "2", "3",
                                                                                       "4"}),
                       "deSanitization CryptoWallet 1");
    CryptoWallet crNotCorrupted("&&,", "", std::vector<std::string>{"&&,", "", ",,&"});
    serializationTest(crNotCorrupted, std::string("CRYPTOWALLET,&&&&&,,,&&&&&,,,&,&,&&"),
                      "serialization CryptoWallet notCorrupted");
    deSanitizationTest(crNotCorrupted.serialize(),
                       std::make_pair(false, std::vector<std::string>{"CRYPTOWALLET", "&&,", "", "&&,", "", ",,&"}),
                       "deSanitization CryptoWallet notCorrupted");
    deSanitizationTest(CryptoWallet(std::vector<std::string>{"CRYPTOWALLET", "&&,", "", "&&,", "", ",,&"}).serialize(),
                       std::make_pair(false, std::vector<std::string>{"CRYPTOWALLET", "&&,", "", "&&,", "", ",,&"}),
                       "Creating CryptoWallet with string vector");
    std::string corruptedCryptoWallet("CRYPTOWAL&LET,NomeProva,blockchainName,1,2,3,4");
    deSanitizationTest(corruptedCryptoWallet, std::make_pair(true, std::vector<std::string>{}),
                       "deSanitization CryptoWallet Corrupted");
    std::cout << std::endl;

    std::cout
            << "//Note Unit Testing ----------------------------------------------------------------------------------"
            << std::endl;
    Note n1("NomeProva", "Prova");
    serializationTest(n1, std::string("NOTE,NomeProva,Prova"), "serialization Note 1");
    deSanitizationTest(n1.serialize(), std::make_pair(false, std::vector<std::string>{"NOTE", "NomeProva", "Prova"}),
                       "deSanitization Note 1");
    Note nNotCorrupted("", "&&,&&");
    serializationTest(nNotCorrupted, std::string("NOTE,,&&&&&,&&&&"), "serialization Note notCorrupted");
    deSanitizationTest(nNotCorrupted.serialize(), std::make_pair(false, std::vector<std::string>{"NOTE", "", "&&,&&"}),
                       "deSanitization Note notCorrupted");
    deSanitizationTest(Note(std::vector<std::string>{"NOTE", "", "&&,&&"}).serialize(),
                       std::make_pair(false, std::vector<std::string>{"NOTE", "", "&&,&&"}),
                       "Creating Note with string vector");
    std::string corruptedNote("NOTE,pr&ova,prov&a");
    deSanitizationTest(corruptedNote, std::make_pair(true, std::vector<std::string>{}),
                       "deSanitization Note Corrupted");
    std::cout << std::endl;

    std::cout
            << "//Tree Unit Testing ----------------------------------------------------------------------------------"
            << std::endl;
    RBBSTree<SerializableObject> container;
    CryptoWallet *p5 = new CryptoWallet("5", "blockchainName", std::vector<std::string>{"1", "2", "3", "4"});;
    CreditCard *p3 = new CreditCard("3", "OwnerProva", "provaProva", "prova", d1);;
    Note *p7 = new Note("7", "ciao7");
    Contact *p1p = new Contact("1", "Nome", "Cognome", d1, t1, "Email");
    Account *p4 = new Account("4", "ciao4", "come4", "stai4");
    Account *p6 = new Account("6", "ciao6", "come6", "stai6");
    Account *p8 = new Account("8", "ciao8", "come8", "stai8");
    container.insert(p5);
    container.insert(p3);
    container.insert(p7);
    container.insert(p1p);
    container.insert(p4);
    container.insert(p6);
    container.insert(p8);
    encInFileTest(container, "", "saving in file container");
    RBBSTreeSearchTest(container.search("6"), "ACCOUNT,6,ciao6,come6,stai6", "searching for 6");
    RBBSTreeTest(container, "CONTACT,1,Nome,Cognome,1/1/1,prova prova2,Email"
                            "CREDITCARD,3,OwnerProva,provaProva,prova,1/1/1"
                            "ACCOUNT,4,ciao4,come4,stai4"
                            "CRYPTOWALLET,5,blockchainName,1,2,3,4"
                            "ACCOUNT,6,ciao6,come6,stai6"
                            "NOTE,7,ciao7"
                            "ACCOUNT,8,ciao8,come8,stai8", "tree insertion");
    container.insert(p8);
    RBBSTreeTest(container, "CONTACT,1,Nome,Cognome,1/1/1,prova prova2,Email"
                            "CREDITCARD,3,OwnerProva,provaProva,prova,1/1/1"
                            "ACCOUNT,4,ciao4,come4,stai4"
                            "CRYPTOWALLET,5,blockchainName,1,2,3,4"
                            "ACCOUNT,6,ciao6,come6,stai6"
                            "NOTE,7,ciao7"
                            "ACCOUNT,8,ciao8,come8,stai8", "failed insert because of name duplicate");
    RBBSTreeFilterTest<Account>(container, "ACCOUNT,4,ciao4,come4,stai4"
                                           "ACCOUNT,6,ciao6,come6,stai6"
                                           "ACCOUNT,8,ciao8,come8,stai8", "filtering tree (multiple account)(ACCOUNT)");
    RBBSTreeFilterTest<CryptoWallet>(container, "CRYPTOWALLET,5,blockchainName,1,2,3,4",
                                     "filtering tree (CRYPTOWALLET)");
    RBBSTreeFilterTest<Contact>(container, "CONTACT,1,Nome,Cognome,1/1/1,prova prova2,Email",
                                "filtering tree (CONTACT)");
    RBBSTreeFilterTest<CreditCard>(container, "CREDITCARD,3,OwnerProva,provaProva,prova,1/1/1",
                                   "filtering tree (CREDITCARD)");
    RBBSTreeFilterTest<Note>(container, "NOTE,7,ciao7", "filtering tree (NOTE)");
    container.deleteT("5");
    container.deleteT("1");
    container.deleteT("5");
    container.deleteT("8");
    RBBSTreeFilterTest<SerializableObject>(container, "CREDITCARD,3,OwnerProva,provaProva,prova,1/1/1"
                                                      "ACCOUNT,4,ciao4,come4,stai4"
                                                      "ACCOUNT,6,ciao6,come6,stai6"
                                                      "NOTE,7,ciao7", "filtering tree (SerializableObject)");
    RBBSTreeTest(container, "CREDITCARD,3,OwnerProva,provaProva,prova,1/1/1"
                            "ACCOUNT,4,ciao4,come4,stai4"
                            "ACCOUNT,6,ciao6,come6,stai6"
                            "NOTE,7,ciao7", "tree deletion");
    container.deleteT("4");
    container.deleteT("3");
    container.deleteT("7");
    container.deleteT("6");
    RBBSTreeTest(container, "", "tree deletion (entire tree)");
    RBBSTreeSearchTest(container.search("4"), "", "searching for '4' (empty tree)");
    Account *p4new = new Account("4", "ciao4", "come4", "stai4");
    RBBSInsertionWhenEmptiedTest(container, *p4new, "ACCOUNT,4,ciao4,come4,stai4");
    RBBSTreeDeletionWhenEmptiedTest(container);
    RBBSTreeFilterTest<Account>(container, "ACCOUNT,4,ciao4,come4,stai4", "filtering tree (ACCOUNT)");
    RBBSTreeFilterTest<CryptoWallet>(container, "", "filtering tree (no CryptoWallet elements)(CRYPTOWALLET)");
    RBBSTreeFilterTest<Contact>(container, "", "filtering tree (no Contact elements)(CONTACT)");
    RBBSTreeFilterTest<CreditCard>(container, "", "filtering tree (no CreditCard elements)(CREDITCARD)");
    RBBSTreeFilterTest<Note>(container, "", "filtering tree (no NOTE elements)(NOTE)");
    Note *n0 = new Note("asdòlkfjadfj", "prova 0 prova");
    Note *n2 = new Note("dfadfajdfl4l", "prova 1 prova");
    Note *n3 = new Note("faflaksjdfal", "prova 2 prova");
    Note *n4 = new Note("jfdkjfaifnwe", "prova 3 prova");
    container.insert(n0);
    container.insert(n2);
    container.insert(n3);
    container.insert(n4);
    RBBSTreeSearchTest(container.search("adl"), "NOTE,asdòlkfjadfj,prova 0 prova"
                                                "NOTE,dfadfajdfl4l,prova 1 prova"
                                                "NOTE,faflaksjdfal,prova 2 prova", "searching for 'adl'");
    RBBSTreeSearchTest(container.search("4"), "ACCOUNT,4,ciao4,come4,stai4"
                                              "NOTE,dfadfajdfl4l,prova 1 prova", "searching for '4'");
    RBBSTreeSearchTest(container.search("asdfalskdjfaòlsdfjafja"), "", "searching for something not in");
    container.deleteT("asdòlkfjadfj");
    RBBSTreeTest(container, "ACCOUNT,4,ciao4,come4,stai4"
                            "NOTE,dfadfajdfl4l,prova 1 prova"
                            "NOTE,faflaksjdfal,prova 2 prova"
                            "NOTE,jfdkjfaifnwe,prova 3 prova", "tree deletion (single node)");
    container.deleteT("dfadfajdfl4l");
    RBBSTreeTest(container, "ACCOUNT,4,ciao4,come4,stai4"
                            "NOTE,faflaksjdfal,prova 2 prova"
                            "NOTE,jfdkjfaifnwe,prova 3 prova", "tree deletion (single node)");
    container.deleteT("faflaksjdfal");
    RBBSTreeTest(container, "ACCOUNT,4,ciao4,come4,stai4"
                            "NOTE,jfdkjfaifnwe,prova 3 prova", "tree deletion (single node)");
    container.deleteT("jfdkjfaifnwe");
    RBBSTreeTest(container, "ACCOUNT,4,ciao4,come4,stai4", "tree deletion (single node)");
    std::cout << std::endl;

    std::cout
            << "//EncDec Unit Testing ----------------------------------------------------------------------------------"
            << std::endl;
    encInFileTest(container, "true", "enc in file");  //the only node written is ACCOUNT4ciao4come4stai4
    VerifyPasswordInFileTest("../Savings/Databases/prova1.txt", false, "wrong password",
                             "wrong password test");
    VerifyPasswordInFileTest("../Savings/Databases/prova1.txt", true, "1234", "right password");

    decFromFileTest(container, "ACCOUNT 4 ciao4 come4 stai4 \n", "dec - test");

    n0 = new Note("prima", "prova 0 prova");
    n2 = new Note("seconda", "prova 1 prova");
    n3 = new Note("terza", "prova 2 prova");
    n4 = new Note("quarta", "prova 3 prova");
    container.insert(n0);
    container.insert(n2);
    container.insert(n3);
    container.insert(n4);
    EncDec_File prova("1234", "prova.txt");
    prova.encInFile(container);
    decFromFileTest(container, "ACCOUNT 4 ciao4 come4 stai4 \n"
                               "NOTE prima prova 0 prova \n"
                               "NOTE quarta prova 3 prova \n"
                               "NOTE seconda prova 1 prova \n"
                               "NOTE terza prova 2 prova \n", "dec - test");
    std::cout << std::endl;

    std::cout
            << "//EncDec Unit Testing + Vault --------------------------------------------------------------------------"
            << std::endl;
    Vault vlt("../Savings/Databases");
    readFileNamesTest(vlt, std::vector<std::string>{"24SerializableObjectTest.txt",
                                                    "ciao.txt",
                                                    "prova1.txt",
                                                    "prova2.txt",
                                                    "prova3.txt",
                                                    "prova5.txt"}, "reading files in the savings folder");
    std::vector<std::string> serializedVec;
    for (auto &srlObj: container) serializedVec.push_back(srlObj.serialize());
    loadFromStorageTest(vlt, std::make_pair<std::string, std::string>("prova1.txt", "1234"),
                        std::make_pair(true, serializedVec), "loading from file");
    Note *n5 = new Note("prima", "prova 0 prova");
    Note *n6 = new Note("seconda", "prova 1 prova");
    Note *n7 = new Note("terza", "prova 2 prova");
    Note *n8 = new Note("quarta", "prova 3 prova");
    vlt.addSerializableObject(n5);
    vlt.addSerializableObject(n6);
    vlt.addSerializableObject(n7);
    vlt.addSerializableObject(n8);
    std::vector<std::string> serializedVlt;
    for (auto &srlObj: vlt.vectorize()) serializedVlt.push_back(srlObj->serialize());
    loadToStorageTest(vlt, std::make_pair<std::string, std::string>("prova1.txt", "1234"),
                      std::make_pair(true, serializedVlt), "loading to file and backwards");
    Note *n51 = new Note("prima", "prova 0 prova");
    Note *n61 = new Note("seconda", "prova 1 prova");
    Note *n71 = new Note("terza", "prova 2 prova");
    Note *n81 = new Note("quarta", "prova 3 prova");
    vlt.loadStorage("ciao.txt", "prova");
    vlt.addSerializableObject(n51);
    vlt.addSerializableObject(n61);
    vlt.addSerializableObject(n71);
    vlt.addSerializableObject(n81);
    serializedVlt.clear();
    for (auto &srlObj: vlt.vectorize()) serializedVlt.push_back(srlObj->serialize());
    loadToStorageTest(vlt, std::make_pair<std::string, std::string>("ciao.txt", "prova"),
                      std::make_pair(true, serializedVlt), "loading to a non existing file");

    std::cout << std::endl;

    std::cout
            << "//Extensive Stress Unit Test ---------------------------------------------------------------------------"
            << std::endl;
    Note *a = new Note("a", "nota a");
    Note *b = new Note("b", "nota b");
    Note *c = new Note("c", "nota c");
    Note *d = new Note("d", "nota d");


    Contact *e = new Contact("e", "Nome e", "Cognome e", Date(15, 07, 02), Telephone("+39", "999999"), "Email e");
    Contact *f = new Contact("f", "Nome f", "Cognome f", Date(15, 07, 02), Telephone("+39", "999999"), "Email e");
    Contact *g = new Contact("g", "Nome g", "Cognome g", Date(15, 07, 02), Telephone("+39", "999999"), "Email e");
    Contact *h = new Contact("h", "Nome h", "Cognome h", Date(15, 07, 02), Telephone("+39", "999999"), "Email e");

    CryptoWallet *i = new CryptoWallet("i", "Nome i", std::vector<std::string>{"word i1", "word i2"});
    CryptoWallet *l = new CryptoWallet("l", "Nome l", std::vector<std::string>{"word l1", "word l2"});
    CryptoWallet *m = new CryptoWallet("m", "Nome m", std::vector<std::string>{"word m1", "word m2"});
    CryptoWallet *n = new CryptoWallet("n", "Nome n", std::vector<std::string>{"word n1", "word n2"});

    CreditCard *o = new CreditCard("o", "Owner o", "Number o", "Cvv o", Date(15, 07, 02));
    CreditCard *p = new CreditCard("p", "Owner p", "Number p", "Cvv p", Date(15, 07, 02));
    CreditCard *q = new CreditCard("q", "Owner q", "Number q", "Cvv q", Date(15, 07, 02));
    CreditCard *r = new CreditCard("r", "Owner r", "Number r", "Cvv r", Date(15, 07, 02));

    Account *s = new Account("s", "Email s", "Password s", "Username s");
    Account *t = new Account("t", "Email t", "Password t", "Username t");
    Account *u = new Account("u", "Email u", "Password u", "Username u");
    Account *v = new Account("v", "Email v", "Password v", "Username v");
    Account *z = new Account("z", "Email z", "Password z", "Username z");

    vlt.loadStorage("24SerializableObjectTest.txt", "0123456789");
    vlt.addSerializableObject(l);
    vlt.addSerializableObject(m);
    vlt.addSerializableObject(b);
    vlt.addSerializableObject(h);
    vlt.addSerializableObject(t);
    vlt.addSerializableObject(f);
    vlt.addSerializableObject(r);
    vlt.addSerializableObject(d);
    vlt.addSerializableObject(a);
    vlt.addSerializableObject(u);
    vlt.addSerializableObject(i);
    vlt.addSerializableObject(n);
    vlt.addSerializableObject(p);
    vlt.addSerializableObject(z);
    vlt.addSerializableObject(g);
    vlt.addSerializableObject(q);
    vlt.addSerializableObject(e);
    vlt.addSerializableObject(o);
    vlt.addSerializableObject(s);
    vlt.addSerializableObject(v);
    vlt.addSerializableObject(c);
    std::vector<std::string> vec{a->serialize(), b->serialize(), c->serialize(),
                                 d->serialize(), e->serialize(), f->serialize(),
                                 g->serialize(), h->serialize(), i->serialize(),
                                 l->serialize(), m->serialize(), n->serialize(),
                                 o->serialize(), p->serialize(), q->serialize(),
                                 r->serialize(), s->serialize(), t->serialize(),
                                 u->serialize(), v->serialize(), z->serialize()};
    loadToStorageTest(vlt, std::make_pair<std::string, std::string>("24SerializableObjectTest.txt", "0123456789"),
                      std::make_pair(true, vec),
                      "Input of 24 serializable objects (checking saving order)");
    vlt.deleteSerializableObject("l");
    vlt.deleteSerializableObject("m");
    vlt.deleteSerializableObject("b");
    vlt.deleteSerializableObject("h");
    vlt.deleteSerializableObject("t");
    vlt.deleteSerializableObject("f");
    vlt.deleteSerializableObject("r");
    vlt.deleteSerializableObject("d");
    vlt.deleteSerializableObject("a");
    vlt.deleteSerializableObject("u");
    vlt.deleteSerializableObject("i");
    vlt.deleteSerializableObject("n");
    vlt.deleteSerializableObject("p");
    vlt.deleteSerializableObject("z");
    vlt.deleteSerializableObject("g");
    vlt.deleteSerializableObject("q");
    vlt.deleteSerializableObject("e");
    vlt.deleteSerializableObject("o");
    vlt.deleteSerializableObject("s");
    vlt.deleteSerializableObject("v");
    vlt.deleteSerializableObject("c");
    loadToStorageTest(vlt, std::make_pair<std::string, std::string>("24SerializableObjectTest.txt", "0123456789"),
                      std::make_pair(true, std::vector<std::string>{}),
                      "Deletion of 24 serializable objects (if it deletes it completely)");
}