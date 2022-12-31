#ifndef VAULT_H
#define VAULT_H
#include "../Core/RBBSTree.h"
#include "SerializableObject.h"
#include "../Core/EncDec_File.h"
#include "../Models/Account.h"
#include "../Models/CryptoWallet.h"
#include "../Models/CreditCard.h"
#include "../Models/Contact.h"
#include "../Models/Note.h"

class Vault {
private:
   RBBSTree<SerializableObject>* tree;
   EncDec_File* storage;
   std::string pathToDirectory;
public:
   explicit Vault(const std::string& path);
   void loadStorage(std::string vaultName, std::string password);
   void unloadStorage();
   bool loadFromStorage();
   bool loadToStorage();
   void reset();
   bool addSerializableObject(const SerializableObject* ptr);
   void deleteSerializableObject(const std::string& nameToSearch);
   const std::vector<const SerializableObject*> searchSerializableObjects(const std::string& nameToSearch) const;
   const std::vector<const SerializableObject*> vectorize() const;
   template<class T>
    std::vector<const T*> filteredVectorize() const;
   bool operator=(const Vault&) = delete;
   Vault(const Vault&) = delete;
};


#endif //VAULT_H
