//#notReviewed
#ifndef RBBSTREE
#define RBBSTREE
#include <string>
#include "../Models/SerializableObject.h"

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
    static void insertFixUp(Node*, Node*&);
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
     * Funzione helper per la funzione inOrder.
     */
    static void recInOrder(Node*);
    /*
    * PRE: n non è nullo.
    * POST: restituisce il puntatore al nodo contenente il valore minimo dell'albero.
    */
    static Node* findMin(Node* n);
    /*
    * POST: restituisce, se presente, il puntatore al nodo il cui name è uguale al nameToSearch, altrimenti ritorna nullptr.
    */
    static Node* searchRec(Node* r, const std::string& nameToSearch);
    /*
     * POST: Dato un albero, e il puntatore di un nodo da eliminare all'interno di esso, va a eliminare il nodo, occupandosi
     * di mantenere le informazioni su min, max, predecessore e successore, coerenti.
     */
    static void deleteInTree(RBBSTree<T>& Tree,Node* nameToDelete);
    /*
     * POST: Attraverso delle rotazioni e dei trapianti va a sistemare l'albero per fare rispettare alcune regole rosso nere.
     */
    static void deleteFixUp(Node*&, Node*);
    /*
     * POST: passando un nodo come argomento, andiamo ricorsivamente a eliminare il figlio sinistro e il figlio destro.
     * Successivamente eliminiamo le informazioni contenute dal nodo corrente, e solo in fine il nodo corrente.
     */
    static void recDestroy(Node*);
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
        const T* operator->();
        const T& operator*();
        bool operator!=(const const_iterator&);
    };
    RBBSTree();
    /*
     * POST: inserisce nell'albero un oggetto di tipo T, attraverso un nodo che lo contiene, nella posizione, ordinata
     * rispetto al nome, giusta. Restituisce vero se l'operazione va a buon fine, mentre restituisce falso se
     * il nome dell'oggetto che vogliamo inserire è già presente nell'albero.
     */
    void insert(const T*);
    /*
     * POST: se trova un nome uguale a nameToSearch all'interno delle informazioni dei vari nodi, allora va a eliminare
     * il nodo corrispondente, altrimenti non fa niente.
     */
    void deleteT(const std::string& nameToSearch);
    /*
     * POST: esegue una scansione inOrder dell'albero
     */
    void InOrder() const;
    /*
     * POST: restituisce un puntatore nullo se non trova niente, altrimenti restituisce il puntatore al nodo che contiene
     * l'informazione con nome uguale a nameToSearch
     */
    Node* search (const std::string& nameToSearch) const;
    /*
     * PRE: deve essere utilizzato su un albero non vuoto.
     * POST: restituisce un const_iterator che punta al primo elemento dell'albero (nell'ordine inOrder)(il minore)
     */
    const_iterator begin() const;
    /*
     * PRE: deve essere utilizzato su un albero non vuoto.
     * POST: restituisce un const_iterator che punta all'elemento prima del primo elemento.
     */
    const_iterator start() const;
    /*
     * PRE: deve essere utilizzato su un albero non vuoto.
     * POST: restituisce un const_iterator che punta all'ultimo elemento dell'albero (nell'ordine inOrder)(il massimo)
     */
    const_iterator last() const;
    /*
     * PRE: deve essere utilizzato su un albero non vuoto.
     * POST: restituisce un const_iterator che punta all'elemento dopo l'ultimo elemento.
     */
    const_iterator end() const;
    ~RBBSTree();
};
#endif