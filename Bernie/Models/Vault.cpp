#include "Vault.h"

Vault::Vault(const std::string& path): tree(nullptr),storage(nullptr),pathToDirectory(path) {}

void Vault::loadStorage(std::string vaultName, std::string password) {
    storage = new EncDec_File(password,pathToDirectory+vaultName);
}
void Vault::unloadStorage() {
    delete storage;
}

bool Vault::loadFromStorage() {
    if(storage == nullptr) return false;
    std::vector<std::vector<std::string>> serializedVault = storage->decFromFile();
    RBBSTree<SerializableObject>* trialTree = new RBBSTree<SerializableObject>();
    for(auto rowsIterator = serializedVault.begin(); rowsIterator != serializedVault.end(); ++rowsIterator){
        if((*rowsIterator)[0] == "ACCOUNT" && (*rowsIterator).size() == 5) trialTree->insert(new Account(*rowsIterator));
        else if((*rowsIterator)[0] == "CREDITCARD" && (*rowsIterator).size() == 6) trialTree->insert(new CreditCard(*rowsIterator));
        else if((*rowsIterator)[0] == "CONTACT" && (*rowsIterator).size() == 7) trialTree->insert(new Contact(*rowsIterator));
        else if((*rowsIterator)[0] == "CRYPTOWALLET" && (*rowsIterator).size() > 2) trialTree->insert(new CryptoWallet(*rowsIterator));
        else if((*rowsIterator)[0] == "NOTE" && (*rowsIterator).size() == 3) trialTree->insert(new Note(*rowsIterator));
        else {
            delete trialTree;
            return false;
        }
    }
    if(tree) delete tree;
    tree = trialTree;
    return true;
}

bool Vault::loadToStorage() {
    if(storage == nullptr) return false;
    if(tree == nullptr) return false;
    storage->encInFile(*tree);
    return true;
}