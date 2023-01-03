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
    RBBSTree<SerializableObject> *tree;
    EncDec_File *storage;
    std::string pathToDirectory;
public:
    explicit Vault(const std::string &path);

    /*
     * POST: va a salvarsi dove andare a salvare e da dove estrarre, nella parte EncDec_File dell'oggetto
     */
    void loadStorage(const std::string &vaultName, const std::string &password);

    /*
     * PRE: lo storage delle essere stato caricato (eventualità comunque gestita)
     * POST: va a caricare gli elementi interni al file all'interno dell'albero.
     * Il tipo di ritorno è:
     *      - false: se il file è corrotto e quindi è presente qualche problema di lettura (chiave di decrypt non corretta / file manomesso);
     *      - true: se il file è stato letto correttamente.
     */
    bool loadFromStorage();

    /*
     * PRE: lo storage delle essere stato caricato (eventualità comunque gestita)
     * POST: va a caricare gli elementi dell'albero all'interno dello storage di riferimento.
     * Il tipo di ritorno è:
     *      - false: se non è stato creato lo storage e/o l'albero.
     *      - true: altrimenti.
     */
    bool loadToStorage();

    /*
     * POST: va a resettare l'oggetto. Esegue delete dell'albero e dello storage, di modo da poter riutilizzare l'oggetto
     * per leggere un altro file.
     */
    void reset();

    /*
     * POST: fornisce un vettore di stringhe che specificano i nomi dei files all'interno della cartella di saving per
     * i database.
     */
    std::vector<std::string> fetchDBNames() const;

    /*
     * POST: inserisce il puntatore a SerializableObject all'interno dell'albero nella posizione giusta.
     * Il tipo di ritorno è:
     *      - false: se il nome del SerializableObject passato per puntatore è già presente all'interno dell'albero, oppure
     *               se non è stato impostato l'albero e/o lo storage.
     *      - true: altrimenti.
     */
    bool addSerializableObject(const SerializableObject *ptr);

    /*
     * POST: elimina il nodo all'interno dell'albero
     * Il tipo di ritorno è:
     *      - false: se non è stato impostato lo storage e/o l'albero.
     *      - true: altrimenti.
     */
    void deleteSerializableObject(const std::string &nameToSearch);

    std::vector<const SerializableObject *> searchSerializableObjects(const std::string &nameToSearch) const;

    std::vector<const SerializableObject *> vectorize() const;

    template<class T>
    std::vector<const SerializableObject *> filteredVectorize() const;

    bool operator=(const Vault &) = delete;

    Vault(const Vault &) = delete;
};


#endif //VAULT_H
