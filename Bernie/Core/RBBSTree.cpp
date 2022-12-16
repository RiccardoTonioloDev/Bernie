//#notReviewed
#include "RBBSTree.h"
#include <iostream>
enum COLORS {RED, BLACK};

template<class T>
RBBSTree<T>::Node::Node(const T* i, Node* p, Node* s,Node* par, Node* l,Node* r, int c): info(i), pre(p), succ(s), parent(par), left(l), right(r), color(c) { }

template<class T>
RBBSTree<T>::Node::~Node() {
    delete info;
}

template<class T>
RBBSTree<T>::RBBSTree() : root(nullptr), min(nullptr), max(nullptr) {}

template<class T>
void RBBSTree<T>::insert(const T* info){
    Node* newNode = insertInTree(*this, info);
    if(newNode->parent == nullptr){
        newNode->color = COLORS::BLACK;
        return;
    }
    if(newNode->parent->parent == nullptr) return;
    insertFixUp(root, newNode);
}

template<class T>
typename RBBSTree<T>::Node* RBBSTree<T>::insertInTree(RBBSTree<T>& Tree, const T* info){
    Node*& root = Tree.root;
    if(root == nullptr){
        root = new Node(info);
        return root;
    }

    Node* it = root;
    Node* prec = nullptr;

    while(it != nullptr){
        prec = it;
        if((*info) <= *(it->info))
            it = it->left;
        else{
            it = it->right;
        }
    }

    Node* newNode = new Node(info, nullptr, nullptr, prec, nullptr, nullptr,COLORS::RED);
    if((*info) <= *(prec->info)){
        newNode->pre = prec->pre;
        if(newNode->pre) newNode->pre->succ = newNode;
        prec->pre = newNode;
        newNode->succ = prec;
        prec->left = newNode;
    }else{
        newNode->succ = prec->succ;
        if(newNode->succ) newNode->succ->pre = newNode;
        prec->succ = newNode;
        newNode->pre = prec;
        prec->right = newNode;
    }
    if(Tree.min != nullptr){
        if((*info)<=(*(Tree.min->info))) Tree.min = newNode;
        if(!((*info)<=(*(Tree.max->info)))) Tree.max = newNode;
    }else{
        Tree.min = newNode;
        Tree.max = newNode;
    }

    return newNode;
}

template<class T>
void RBBSTree<T>::insertFixUp(Node *root, Node* &z){
    while(z->parent != nullptr && z->parent->color == COLORS::RED){
        std::cout<<"SAS"<<std::endl;
        if(z->parent == z->parent->parent->left){
            Node* y = z->parent->parent->right;
            if(y->color == COLORS::RED){
                z->parent->color = COLORS::BLACK;
                y->color = COLORS::BLACK;
                z->parent->parent->color = COLORS::RED;
                z = z->parent->parent;
            } else {
                if(z == z->parent->right){
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = COLORS::BLACK;
                z->parent->parent->color = COLORS::RED;
                rotateRight(root, z->parent->parent);
            }
        }else{
            Node* y = z->parent->parent->left;
            if(y->color == COLORS::RED){
                z->parent->color = COLORS::BLACK;
                y->color = COLORS::BLACK;
                z->parent->parent->color = COLORS::RED;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->left){
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = COLORS::BLACK;
                z->parent->parent->color = COLORS::RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    root->color = COLORS::BLACK;
}

template<class T>
void RBBSTree<T>::recInOrder(Node* r){
    if(r != nullptr){
        recInOrder(r->left);
        std::cout<<"|" << *(r->info) << " color: " << r->color << "|";
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
void RBBSTree<T>::rotateLeft(RBBSTree::Node*& r, RBBSTree::Node* x){
    Node* y = x->right;
    x->right = y->left;
    x->right->parent = x;
    RBBSTree::transplant(r,x,y);
    y->left = x;
    x->parent = y;
}

template<class T>
void RBBSTree<T>::rotateRight(RBBSTree::Node*& r, RBBSTree::Node* x) {
    Node* y = x->left;
    x->left = y->right;
    x->left->parent = x;
    RBBSTree::transplant(r,x,y);
    y->right = x;
    x->parent = y;
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::begin() const {
    const_iterator cit;
    cit.currentPointer = min;
    cit.isStart = false;
    cit.isEnd = false;
    return cit;
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::start() const {
    const_iterator cit;
    cit.currentPointer = min;
    --cit.currentPointer;
    cit.isStart = true;
    cit.isEnd = false;
    return cit;
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::last() const {
    const_iterator cit;
    cit.currentPointer = max;
    cit.isStart = false;
    cit.isEnd = false;
    return cit;
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::end() const {
    const_iterator cit;
    cit.currentPointer = max;
    ++cit.currentPointer;
    cit.isStart = false;
    cit.isEnd = true;
    return cit;
}

template<class T>
void RBBSTree<T>::recDestroy(RBBSTree::Node* ptr) {
    if(ptr!= nullptr){
        recDestroy(ptr->left);
        recDestroy(ptr->right);
        delete ptr;
    }
}

template<class T>
RBBSTree<T>::~RBBSTree() {
    recDestroy(root);
}


template<class T>
void RBBSTree<T>::deleteFixUp(RBBSTree::Node *& root, RBBSTree::Node *toFix) {
    while(toFix != nullptr && toFix != root && toFix->color == BLACK){
        if (toFix == toFix->parent->left){
            Node* sibling = toFix->parent->right;
            if(sibling->color == COLORS::RED){
                sibling->color = COLORS::BLACK;
                toFix->parent->color = COLORS::RED;
                rotateLeft(root,toFix->parent);
                sibling = toFix->parent->right;
            }
            if(sibling->left->color == COLORS::BLACK && sibling->right->color == COLORS::BLACK){
               sibling->color = COLORS::RED;
               toFix = toFix->parent;
            }else{
                if(sibling->right->color == COLORS::BLACK){
                    sibling->left->color = COLORS::BLACK;
                    sibling->color = COLORS::RED;
                    rotateRight(root,sibling);
                    sibling = toFix->parent->right;
                }
                sibling->color = toFix->parent->color;
                toFix->parent->color = COLORS::BLACK;
                sibling->right->color = COLORS::BLACK;
                rotateLeft(root, toFix->parent);
                toFix = root;
            }
        }else{
            Node* sibling = toFix->parent->left;
            if(sibling->color == COLORS::RED){
                sibling->color = COLORS::BLACK;
                toFix->parent->color = COLORS::RED;
                rotateRight(root,toFix->parent);
                sibling = toFix->parent->left;
            }
            if(sibling->right->color == COLORS::BLACK && sibling->left->color == COLORS::BLACK){
                sibling->color = COLORS::RED;
                toFix = toFix->parent;
            }else{
                if(sibling->left->color == COLORS::BLACK){
                    sibling->right->color = COLORS::BLACK;
                    sibling->color = COLORS::RED;
                    rotateLeft(root,sibling);
                    sibling = toFix->parent->left;
                }
                sibling->color = toFix->parent->color;
                toFix->parent->color = COLORS::BLACK;
                sibling->left->color = COLORS::BLACK;
                rotateRight(root, toFix->parent);
                toFix = root;
            }
        }
    }
    toFix->color = COLORS::BLACK;
}

template<class T>
void RBBSTree<T>::deleteInTree(RBBSTree<T>& Tree, RBBSTree::Node* toDelete) {
    Node*& r = Tree.root;
    Node* y = toDelete;
    Node* toSave;
    int y_original_color = y->color;
    if(toDelete->left == nullptr){
        toSave = toDelete->right;
        toDelete->pre->succ = toDelete->succ;
        toDelete->succ->pre = toDelete->pre;
        transplant(r,toDelete,toDelete->right);
    }else if(toDelete->right == nullptr){
        toSave = toDelete->left;
        transplant(r,toDelete,toDelete->left);
    }else{
        //In questo caso devo salvarmi il nuovo y (elemento che uso per sostituire toDelete)
        y = toDelete->succ;
        y_original_color = y->color;
        toSave = y->right;
        if(y != toDelete->right){
            transplant(r,y,y->right);
            y->right = toDelete->right;
            y->right->parent = y;
        }else toSave->parent = y;
        transplant(r,toDelete,y);
        y->left = toDelete->left;
        y->left->parent = y;
    }
    if(toDelete->pre) toDelete->pre->succ = toDelete->succ;
    if(toDelete->succ) toDelete->succ->pre = toDelete->pre;
    if(toDelete == Tree.min) Tree.min = toDelete->succ;
    if(toDelete == Tree.max) Tree.max = toDelete->pre;
    delete toDelete;
    if(y_original_color == COLORS::BLACK) deleteFixUp(r,toSave);
}

template<class T>
void RBBSTree<T>::deleteT(const std::string &nameToSearch) {}
//############################################ITERATOR#####################################################
template<class T>
typename RBBSTree<T>::const_iterator& RBBSTree<T>::const_iterator::operator++() {
    if(!isEnd && !isStart){
        if(currentPointer->succ == nullptr) {
            isEnd = true;
            currentPointer++;
        }else{
            currentPointer = currentPointer->succ;
        }
    }
    if(isStart){
       isStart = false;
       currentPointer++;
    }
    return (*this);
}
template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::const_iterator::operator++(int){
    const_iterator cit = (*this);
    //Essendo che isEnd e isStart non possono essere true assieme (accadrebbe con un albero vuoto, ma presupponiamo
    //che non si iteri su un albero vuoto): qui controllo se entrambi sono a false
    if(!isEnd && !isStart){
        if(currentPointer->succ == nullptr) {
            isEnd = true;
            currentPointer = currentPointer++;
        }else{
            currentPointer = currentPointer->succ;
        }
    }
    //In questo caso controllo se isStart è true (e quindi ha rotto la condizione di prima)
    else if(isStart){
        isStart = false;

        currentPointer++;
    }
    //Non mi occupo della isEnd==true perchè in tal caso non devo fare niente
    return cit;
}
template<class T>
typename RBBSTree<T>::const_iterator& RBBSTree<T>::const_iterator::operator--() {
    if(!isStart && !isEnd){
        if(currentPointer->pre == nullptr) {
            isStart = true;
            currentPointer--;
        }else{
            currentPointer = currentPointer->pre;
        }
    }
    if(isEnd){
        isEnd = false;
        currentPointer--;
    }
    return (*this);
}
template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::const_iterator::operator--(int){
    const_iterator cit = (*this);
    if(!isStart && !isEnd){
        if(currentPointer->pre == nullptr) {
            isStart = true;
            currentPointer = currentPointer--;
        }else{
            currentPointer = currentPointer->pre;
        }
    }else if(isEnd){
        isEnd = false;
        currentPointer--;
    }
    return cit;
}
template<class T>
const T* RBBSTree<T>::const_iterator::operator->() {
    return currentPointer->info;
}

template<class T>
const T& RBBSTree<T>::const_iterator::operator*() {
    return *(currentPointer->info);
}

template<class T>
bool RBBSTree<T>::const_iterator::operator!=(const RBBSTree<T>::const_iterator& cit) {
    return !(cit.currentPointer == currentPointer && cit.isEnd == isEnd && cit.isStart == isStart);
}
template class RBBSTree<SerializableObject>;