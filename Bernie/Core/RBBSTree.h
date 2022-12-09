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
    RBBSTree();
    void insert(const T&);
    void InOrder();
};

#endif