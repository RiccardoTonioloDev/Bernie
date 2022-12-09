//#notReviewed
#include "RBBSTree.h"
#include <iostream>

template<class T>
RBBSTree<T>::Node::Node(const T& i, Node* p, Node* s,Node* par, Node* l,Node* r, int c): info(i), pre(p), succ(s), parent(par), left(l), right(r), color(c) { }

template<class T>
RBBSTree<T>::RBBSTree() : root(nullptr), min(nullptr), max(nullptr) {}

template<class T>
void RBBSTree<T>::insert(const T& info){
    insertInTree(root, info);
}

template<class T>
void RBBSTree<T>::insertInTree(Node*& root, const T& info){
    if(root == nullptr){
        root = new Node(info);
        return;
    }

    Node* it = root;
    Node* prec = nullptr;

    while(it != nullptr){
        prec = it;
        if(info < it->info)
            it = it->left;
        else if (info > it->info){       
            it = it->right;
        }
    }

    Node* newNode = new Node(info, prec->pre, prec, prec, nullptr, nullptr);
    if(info < prec->info){
        prec->left = newNode;
        prec->pre = newNode;
    }

    else if(info > prec->info){
        prec->right = newNode;
        prec->succ = newNode;
    }
}

template<class T>
void RBBSTree<T>::recInOrder(Node* r){
    if(r != nullptr){
        recInOrder(r->left);
        std::cout<<"|" << r->info << " color: " << r->color << "|";
        recInOrder(r->right);
    }
}

template<class T>
void RBBSTree<T>::InOrder(){
    recInOrder(root);
}

template<class T>
typename RBBSTree<T>::Node* RBBSTree<T>::findMin(Node* r){
    Node* it = r;
    for(;it->left != nullptr; it = it->left);
    return it;
}

template<class T>
void RBBSTree<T>::transplant(Node*& root, Node*& old, Node*& newN){
    if(old->parent == nullptr)
        root = newN;
    else {
        if(old == (old->parent)->left)
            (old->parent)->left = newN;
        else 
            (old->parent)->right = newN;
    }

    if(newN != nullptr)
        newN->parent = old->parent;
}

template<class T>
void RBBSTree<T>::rotateLeft(Node*& r, Node*&){

}

template class RBBSTree<int>;


