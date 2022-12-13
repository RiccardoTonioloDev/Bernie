//#notReviewed
#ifndef RBBSTREE
#define RBBSTREE

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
            Node(const T&, Node* =nullptr,Node* =nullptr,Node* =nullptr,Node* =nullptr,Node* =nullptr, int = 0);
            ~Node();
    };

    Node* root;
    Node* min;
    Node* max;

    static void insertInTree(Node*&, const T&);
    static void transplant(Node*&, Node*&, Node*&);
    static void insertFixUp(Node*, Node&);
    static void rotateLeft(Node*&, Node*&);
    static void rotateRight(Node*, Node*);
    static void recInOrder(Node*);
    static Node* findMin(Node*);

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
};

#endif