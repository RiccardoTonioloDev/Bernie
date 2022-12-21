#ifndef RBBSTREE
#define RBBSTREE
#include <string>
#include "../Models/SerializableObject.h"
#include "../Models/Account.h"
#include "../Models/CryptoWallet.h"
#include "../Models/CreditCard.h"
#include "../Models/Contact.h"
#include "../Models/Note.h"
#include <algorithm>

template <class T>
class RBBSTree {
private:
    class Node {
        public:
            const T* info;
            Node* pre;
            Node* succ;
            Node* parent;
            Node* left;
            Node* right;
            int color;
            Node(const T* info, Node* prev=nullptr,Node* succ=nullptr,Node* parent=nullptr,Node* left=nullptr,Node* right=nullptr, int color= 0);
            ~Node();
    };

    Node* root;
    Node* min;
    Node* max;

    /*
    * POST: restituisce un puntatore al nodo appena aggiunto.
    */
    static Node* insertInTree(RBBSTree<T>& Tree, const T*);
    /*
    * PRE: r, x, toTransplant sono tutti nodi non nulli.
    * POST: l'albero radicato in root avrà il nodo toTransplant e il suo sotto albero piantato al posto di x.
    */
    static void transplant(Node*& r, Node* x, Node* toTransplant);
    /*
    * PRE: i due nodi passati non sono nulli.
    * POST: assicura che l'albero Red-and-Black mantenga le proprietà di struttura, occupandosi dell'aggiustamento dei colori dei nodi dopo l'inserimento.
    */
    static void insertFixUp(Node*&, Node*&);
    /*
    * PRE: r e x sono nodi non nulli.
    * POST: rotazione del nodo x e del suo sotto albero verso sinistra mantenendo le proprietà d'ordine.
    */
    static void rotateLeft(Node*& r, Node* x);
    /*
    * PRE: r e x sono nodi non nulli.
    * POST: rotazione del nodo x e del suo sotto albero verso destra mantenendo le proprietà d'ordine.
    */
    static void rotateRight(Node*& r, Node* x);
    /*
     * POST: Dato un albero, e il puntatore di un nodo da eliminare all'interno di esso, va a eliminare il nodo, occupandosi
     * di mantenere le informazioni su min, max, predecessore e successore, coerenti.
     */
    static void deleteInTree(RBBSTree<T>& Tree,Node* toDelete);
    /*
     * POST: Attraverso delle rotazioni e dei trapianti va a sistemare l'albero per fare rispettare alcune regole rosso nere.
     */
    static void deleteFixUp(Node*&, Node*);
    /*
     * POST: restituisce un puntatore nullo se non trova niente, altrimenti restituisce il puntatore al nodo che contiene
     * l'informazione con nome uguale a nameToSearch
     */
    Node* searchNode (const std::string& nameToSearch) const;
public:
    class const_iterator{
    private:
        const Node* currentPointer;
        bool isEnd;
        bool isStart;
    public:
        friend class RBBSTree<T>;
        const_iterator operator++(int);
        const_iterator& operator++();
        const_iterator operator--(int);
        const_iterator& operator--();
        const T* operator->() const;
        const T& operator*() const;
        bool operator!=(const const_iterator&) const;
    };
    RBBSTree();
    /*
     * POST: inserisce nell'albero un oggetto di tipo T, attraverso un nodo che lo contiene, nella posizione, ordinata
     * rispetto al nome, giusta. Restituisce vero se l'operazione va a buon fine, mentre restituisce falso se
     * il nome dell'oggetto che vogliamo inserire è già presente nell'albero.
     */
    bool insert(const T*);
    /*
     * POST: se trova un nome uguale a nameToSearch all'interno delle informazioni dei vari nodi, allora va a eliminare
     * il nodo corrispondente, altrimenti non fa niente.
     */
    void deleteT(const std::string& nameToSearch);
    /*
     * PRE: deve essere utilizzato su un albero non vuoto.
     * POST: restituisce un const_iterator che punta al primo elemento dell'albero (nell'ordine inOrder)(il minore)
     */
    const std::vector<const T*> search(const std::string& nameToSearch) const;
    const std::vector<const T*> toVector() const;
    /*
     * POST: restituisce un const_iterator che punta al primo elemento.
     */
    const_iterator begin() const;
    /*
     * POST: restituisce un const_iterator che punta all'elemento dopo l'ultimo elemento.
     */
    const_iterator end() const;

    template<class U>
            std::vector<const T*> filter() const;
    ~RBBSTree();
};
#endif