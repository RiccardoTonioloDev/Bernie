#ifndef RBBSTREE2
#define RBBSTREE2

#include <algorithm>
#include <string>

#include "../Models/Account.h"
#include "../Models/Contact.h"
#include "../Models/CreditCard.h"
#include "../Models/CryptoWallet.h"
#include "../Models/Note.h"
#include "../Models/SerializableObject.h"

template<class T>
class RBBSTree {
private:
    class Node {
    public:
        const T *info;
        Node *pre;
        Node *succ;
        Node *parent;
        Node *left;
        Node *right;
        int color;

        Node(const T *info, Node *prev = nullptr, Node *succ = nullptr, Node *parent = nullptr, Node *left = nullptr,
             Node *right = nullptr, int color = 0);

        ~Node();
    };

    Node *root;
    Node *min;
    Node *max;
    Node *TNULL;

    /*
     * POST: aggiusta la posizione del nodo passato x, mantenendo le 5 proprietà dell'albero rosso nero, rispetto alla
     * precedente cancellazione.
     */
    void deleteFix(Node *x);

    /*
     * POST: effettua il trapianto del nodo v nel nodo u (sposta sostanzialmente i parent di u su v).
     */
    void transplant(Node *u, Node *v);

    /*
     * POST: funzione che dato un nodo passato come puntatore, lo elimina all'interno dell'albero.
     */
    void deleteNodeHelper(Node *toDelete);

    /*
     * POST: effettua la rotazione verso destra del sotto albero radicato sotto il nodo x.
     */
    void leftRotate(Node *x);

    /*
     * POST: effettua la rotazione verso sinistra del sotto albero radicato sotto il nodo x.
     */
    void rightRotate(Node *x);

    /*
     * POST: dato un nome cerca il nodo che possiede nel campo name nella parte info di tipo T, quel nome.
     * Restituisce:
     *      - TNULL: se non trova alcun nodo con quel nome;
     *      - il puntatore del nodo trovato altrimenti.
     */
    Node *searchNode(const std::string &nameToSearch) const;

    /*
     * POST: aggiusta la posizione del nodo passato x, mantenendo le cinque proprietà dell'albero rosso nero, rispetto
     * al precedente inserimento.
     */
    void insertFixUp(Node *k);

public:
    class const_iterator {
    private:
        const Node *currentPointer;
        bool isEnd;
        bool isStart;

    public:
        friend class RBBSTree<T>;

        const_iterator operator++(int);

        const_iterator &operator++();

        const_iterator operator--(int);

        const_iterator &operator--();

        const T *operator->() const;

        const T &operator*() const;

        bool operator!=(const const_iterator &) const;
    };

    RBBSTree();

    ~RBBSTree();

    /*
     * POST: dato una sotto sequenza da cercare, restituisce tutti i nodi come puntatore a T, all'interno di un vector,
     * che possiedono nel proprio campo name la sotto sequenza specificata.
     */
    const std::vector<const T *> search(const std::string &subStrToSearch) const;

    const_iterator begin() const;

    const_iterator end() const;

    /*
     * POST: permette d'inserire all'interno dell'albero un puntatore di tipo T (verrà incapsulato da un nodo)
     * Restituisce:
     *      - false: se la insert non va a buon fine (esiste un altro elemento con lo stesso nome all'interno dell'albero.
     *      - true: altrimenti.
     */
    bool insert(const T *info);

    /*
     * POST: permette di eliminare un nodo all'interno dell'albero che possiede il campo name uguale a quello specificato
     * come parametro.
     * Restituisce:
     *      - false: se la delete non va a buon fine (non esiste nessun nodo da eliminare con quel nome);
     *      - true: altrimenti.
     */
    bool deleteT(const std::string &nameToSearch);

    /*
     * POST: restituisce un vettore filtrato in base al tipo specificato, ordinato, corrispondente ai valori del tipo
     * specificato, all'interno dell'albero.
     */
    template<class U>
    std::vector<const T *> filter() const;

    /*
     * POST: restituisce la rappresentazione a forma di vettore dell'albero, ordinata in modo crescente secondo l'ordine
     * lessicografico dei nomi.
     */
    const std::vector<const T *> toVector() const;
};

#endif