#include "Vault.h"
#include <dirent.h>
#include <algorithm>

Vault::Vault(const std::string &path) : tree(nullptr), storage(nullptr), pathToDirectory(path) {}

Vault::~Vault() {
    delete storage;
    delete tree;
}

bool Vault::loadStorage(const std::string &vaultName, const std::string &password) {
    if (storage) reset();
    storage = new EncDec_File(password, pathToDirectory + "/" + vaultName);
    tree = new RBBSTree<SerializableObject>;
    return loadFromStorage();
}

bool Vault::loadFromStorage() {
    if (storage == nullptr) return false;
    if (!(storage->verifyPassword(*storage))) return false;
    std::vector<std::vector<std::string>> serializedVault = storage->decFromFile();
    RBBSTree<SerializableObject> *trialTree = new RBBSTree<SerializableObject>();
    for (auto rowsIterator = serializedVault.begin(); rowsIterator != serializedVault.end(); ++rowsIterator) {
        if ((*rowsIterator)[0] == "ACCOUNT" && (*rowsIterator).size() == 5)
            trialTree->insert(new Account(*rowsIterator));
        else if ((*rowsIterator)[0] == "CREDITCARD" && (*rowsIterator).size() == 6)
            trialTree->insert(new CreditCard(*rowsIterator));
        else if ((*rowsIterator)[0] == "CONTACT" && (*rowsIterator).size() == 7)
            trialTree->insert(new Contact(*rowsIterator));
        else if ((*rowsIterator)[0] == "CRYPTOWALLET" && (*rowsIterator).size() > 2)
            trialTree->insert(new CryptoWallet(*rowsIterator));
        else if ((*rowsIterator)[0] == "NOTE" && (*rowsIterator).size() == 3)
            trialTree->insert(new Note(*rowsIterator));
        else {
            delete trialTree;
            reset();
            return false;
        }
    }
    delete tree;
    tree = trialTree;
    return true;
}

bool Vault::loadToStorage() const {
    if (storage == nullptr) return false;
    if (tree == nullptr) return false;
    storage->encInFile(*tree);

    return true;
}

void Vault::reset() {
    delete storage;
    delete tree;
    storage = nullptr;
    tree = nullptr;
}

std::vector<std::string> Vault::fetchDBNames() const {
    std::vector<std::string> fileNames;
    DIR *dir = opendir(pathToDirectory.c_str());
    if (dir == nullptr) {
        std::cerr << "Could not open directory: " << pathToDirectory << std::endl;
        return fileNames;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {
            fileNames.push_back(entry->d_name);
        }
    }
    closedir(dir);

    std::sort(fileNames.begin(), fileNames.end());

    return fileNames;
}

bool Vault::addSerializableObject(const SerializableObject *ptr) {
    if (storage == nullptr) return false;
    if (tree == nullptr) return false;
    bool result = tree->insert(ptr);
    if (result) loadToStorage();
    return result;
}

bool Vault::deleteSerializableObject(const std::string &nameToSearch) {
    if (tree == nullptr || storage == nullptr) return false;
    if (tree->deleteT(nameToSearch)) {
        loadToStorage();
        return true;
    }
    return false;
}

std::vector<const SerializableObject *> Vault::searchSerializableObjects(const std::string &nameToSearch) const {
    if (tree == nullptr) return {};
    return tree->search(nameToSearch);
}

std::vector<const SerializableObject *> Vault::vectorize() const {
    if (tree == nullptr) return {};
    return tree->toVector();
}

template<class T>
std::vector<const SerializableObject *> Vault::filteredVectorize() const {
    if (tree == nullptr) return {};
    return tree->template filter<T>();
}

template std::vector<const SerializableObject *> Vault::filteredVectorize<Account>() const;

template std::vector<const SerializableObject *> Vault::filteredVectorize<CreditCard>() const;

template std::vector<const SerializableObject *> Vault::filteredVectorize<CryptoWallet>() const;

template std::vector<const SerializableObject *> Vault::filteredVectorize<Contact>() const;

template std::vector<const SerializableObject *> Vault::filteredVectorize<Note>() const;

bool Vault::modifyTreeObj(const SerializableObject *toModify, const SerializableObject *toAssign) {
    std::string name = *toAssign;
    std::string nameOfModified = *toModify;
    if (nameOfModified == name && tree->searchSingle(nameOfModified) != nullptr) {
        const_cast<SerializableObject *>(toModify)->modify(toAssign);
        loadToStorage();
        return true;
    } else return false;
}

bool Vault::isInitialized() const {
    return tree != nullptr && storage != nullptr;
}

bool Vault::deleteDB(const std::string &name, const std::string &password) {
    if(!loadStorage(name, password)) return false;
    reset();
    std::remove((pathToDirectory+"/"+name).c_str());
    return true;
}