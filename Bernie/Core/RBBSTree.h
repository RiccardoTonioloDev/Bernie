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

    void deleteFix(Node *x);

    void transplant(Node *u, Node *v);

    void deleteNodeHelper(Node *toDelete);

    void leftRotate(Node *x);

    void rightRotate(Node *x);

    Node *searchNode(const std::string &nameToSearch) const;

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

    const std::vector<const T *> search(const std::string &subStrToSearch) const;

    const_iterator begin() const;

    const_iterator end() const;

    bool insert(const T *info);

    bool deleteT(const std::string &nameToSearch);

    template<class U>
    std::vector<const T *> filter() const;

    const std::vector<const T *> toVector() const;
};

#endif