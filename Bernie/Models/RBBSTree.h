//#notReviewed
#ifndef RBBSTREE.H
#define RBBSTREE.H

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
            Node(const T&, Node* =nullptr,Node* =nullptr,Node* =nullptr,Node* =nullptr,Node* =nullptr);
            ~Node();
    };

    Node* root;
    Node* min;
    Node* max;

    static void insertInTree(Node*, Node&);
    static void insertFixUp(Node*, Node&);
    static void rotateLeft(Node*, Node*);
    static void rotateRight(Node*, Node*);
    static Node* findMin();

public:
    RBBSTree();
    void insert(const T&)
};

#endif