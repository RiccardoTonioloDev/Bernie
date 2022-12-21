#include "RBBSTree.h"
#include "TreeTestingFunctions.h"

void RBBSTreeTest(const RBBSTree<SerializableObject>& input, const std::string& expected, const std::string& testName){
    std::string saved("");
    RBBSTree<SerializableObject>::const_iterator cit;
    for(cit = input.begin();cit != input.end(); ++cit){
        saved = saved + cit->serialize();
    }
    if(saved == expected) std::cout << "TEST (" + testName + "): \033[92mPASSED\033[0m";
    else std::cout << "TEST (" + testName + "): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void RBBSInsertionWhenEmptiedTest(RBBSTree<SerializableObject>& tree,const SerializableObject& input,const std::string& expectedInside){
    tree.insert(&input);
    std::string saved("");
    RBBSTree<SerializableObject>::const_iterator cit = tree.begin();
    saved = cit->serialize();
    if(saved == expectedInside) std::cout << "TEST (insertion when emptied): \033[92mPASSED\033[0m";
    else std::cout << "TEST (insertion when emptied): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}

void RBBSTreeDeletionWhenEmptiedTest(RBBSTree<SerializableObject>& tree){
    try{
        tree.deleteT("prova");
    }catch(...)
    //Questo catch prende ogni tipo di eccezione possibile e la gestisce.
    {
        std::cout << "TEST (deletion when emptied): \033[91mNOT PASSED\033[0m";
    }
    std::cout << "TEST (deletion when emptied): \033[92mPASSED\033[0m";
    std::cout << std::endl;
}

/*void RBBSTreeSearchTest(const RBBSTree<SerializableObject>& tree,const std::string& toFind,bool expected, const std::string& testName){
    const void* info = tree.search(toFind);
    if((info && expected) || (!info && !expected)) std::cout << "TEST ("+testName+"): \033[92mPASSED\033[0m";
    else std::cout << "TEST ("+testName+"): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}*/

template<class T>
void RBBSTreeFilterTest(const RBBSTree<SerializableObject>& tree,const std::string& expected,const std::string& testName){
    std::vector<const SerializableObject*> saved = tree.filter<T>();
    std::string vectorSerialized("");
    for (typename std::vector<const SerializableObject*>::const_iterator cit = saved.begin();cit != saved.end();++cit) {
        vectorSerialized += (*cit)->serialize();
    }
    if(vectorSerialized == expected) std::cout << "TEST ("+testName+"): \033[92mPASSED\033[0m";
    else std::cout << "TEST ("+testName+"): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}
template void RBBSTreeFilterTest<Account>(const RBBSTree<SerializableObject>& tree,const std::string& expected,const std::string& testName);
template void RBBSTreeFilterTest<CryptoWallet>(const RBBSTree<SerializableObject>& tree,const std::string& expected,const std::string& testName);
template void RBBSTreeFilterTest<Contact>(const RBBSTree<SerializableObject>& tree,const std::string& expected,const std::string& testName);
template void RBBSTreeFilterTest<Note>(const RBBSTree<SerializableObject>& tree,const std::string& expected,const std::string& testName);
template void RBBSTreeFilterTest<CreditCard>(const RBBSTree<SerializableObject>& tree,const std::string& expected,const std::string& testName);
template void RBBSTreeFilterTest<SerializableObject>(const RBBSTree<SerializableObject>& tree,const std::string& expected,const std::string& testName);

void RBBSTreeSearchTest(const std::vector<const SerializableObject*> input,const std::string& expected,const std::string& testName){
    std::string vectorFound("");
    for (typename std::vector<const SerializableObject*>::const_iterator cit = input.begin();cit != input.end();++cit) {
        vectorFound += (*cit)->serialize();
    }
    if(vectorFound == expected) std::cout << "TEST ("+testName+"): \033[92mPASSED\033[0m";
    else std::cout << "TEST ("+testName+"): \033[91mNOT PASSED\033[0m";
    std::cout << std::endl;
}
