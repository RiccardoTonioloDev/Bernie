#include "Vault.h"
#include <dirent.h>

Vault::Vault(const std::string &path) : tree(nullptr), storage(nullptr), pathToDirectory(path) {}

void Vault::loadStorage(const std::string &vaultName, const std::string &password) {
    if (storage) return;
    storage = new EncDec_File(password, pathToDirectory + "/" + vaultName);
    tree = new RBBSTree<SerializableObject>;
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
            return false;
        }
    }
    delete tree;
    tree = trialTree;
    return true;
}

bool Vault::loadToStorage() {
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

    return fileNames;
}

bool Vault::addSerializableObject(const SerializableObject *ptr) {
    if (storage == nullptr) return false;
    if (tree == nullptr) return false;
    bool result = tree->insert(ptr);
    if (result) storage->encInFile(*tree);
    return result;
}

void Vault::deleteSerializableObject(const std::string &nameToSearch) {
    if (tree == nullptr) return;
    if (storage == nullptr) return;
    if (tree->deleteT(nameToSearch)) storage->encInFile(*tree);
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
