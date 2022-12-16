//#notReviewed
#ifndef RBBSTREE
#define RBBSTREE
#include <string>

template <class T>
class RBBSTree {
private:
    class Node {
        public:
            const T& info;
            Node* pre;
            Node* succ;
            Node* parent;
            Node* left;
            Node* right;
            int color;
            Node(const T& info, Node* prev=nullptr,Node* succ=nullptr,Node* parent=nullptr,Node* left=nullptr,Node* right=nullptr, int color= 0);
            ~Node();
    };

    Node* root;
    Node* min;
    Node* max;

    static Node* insertInTree(Node*&, const T&);
    static void transplant(Node*& r, Node*& x, Node*& toTransplant);
    static void insertFixUp(Node*, Node*&);
    static void rotateLeft(Node*& r, Node* x);
    static void rotateRight(Node*& r, Node* x);
    static void recInOrder(Node*);
    static Node* findMin(Node* n);
    static Node* deleteInTree(Node*& r,Node* nameToDelete);
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
        const Node* operator->();
        bool operator!=(const const_iterator&);
    };
    RBBSTree();
    void insert(const T&);
    void deleteT(const std::string& nameToSearch);
    void InOrder();
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