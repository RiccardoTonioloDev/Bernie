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
bool RBBSTree<T>::insert(const T* info){
    if(searchNode(*info) == nullptr){ //it will be converted in the name string thanks to the overloading of operator string()
        Node* newNode = insertInTree(*this, info);
        if(newNode->parent == nullptr){
            newNode->color = COLORS::BLACK;
            return true;
        }
        if(newNode->parent->parent == nullptr) return true;
        insertFixUp(root, newNode);
        return true;
    } else return false;
}

template<class T>
typename RBBSTree<T>::Node* RBBSTree<T>::insertInTree(RBBSTree<T>& Tree, const T* info){
    Node*& root = Tree.root;
    if(root == nullptr){
        root = new Node(info);
        Tree.min = root;
        Tree.max = root;
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
        if((*info) > (*(Tree.max->info))) Tree.max = newNode;
    }else{
        Tree.min = newNode;
        Tree.max = newNode;
    }

    return newNode;
}

template<class T>
void RBBSTree<T>::insertFixUp(Node *& root, Node* &z){
    while(z->parent != nullptr && z->parent->color == COLORS::RED){
        if(z->parent == z->parent->parent->left){
            Node* y = z->parent->parent->right;
            if(y && y->color == COLORS::RED){
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
            if(y && y->color == COLORS::RED){
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
void RBBSTree<T>::transplant(Node*& root, Node* old, Node* newN){
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
    if(x->right) x->right->parent = x;
    RBBSTree::transplant(r,x,y);
    y->left = x;
    x->parent = y;
}

template<class T>
void RBBSTree<T>::rotateRight(RBBSTree::Node*& r, RBBSTree::Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if(x->left) x->left->parent = x;
    RBBSTree::transplant(r,x,y);
    y->right = x;
    x->parent = y;
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::begin() const {
    const_iterator cit;
    if(root){
        cit.currentPointer = min;
        cit.isStart = false;
        cit.isEnd = false;
    }else{
        cit.currentPointer = nullptr;
        cit.isStart = true;
        cit.isEnd = true;
    }
    return cit;
}


template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::end() const {
    const_iterator cit;
    if(root){
        cit.currentPointer = max;
        ++cit.currentPointer;
        cit.isStart = false;
        cit.isEnd = true;
    }else{
        cit.currentPointer = nullptr;
        cit.isStart = true;
        cit.isEnd = true;
    }
    return cit;
}


template<class T>
RBBSTree<T>::~RBBSTree() {
    Node* start = min; Node* next = nullptr;
    while (start){
        if(start->succ) next = start->succ;
        delete start;
        start = next;
        next = nullptr;
    }
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
    if(toFix) toFix->color = COLORS::BLACK;
}

template<class T>
void RBBSTree<T>::deleteInTree(RBBSTree<T>& Tree, RBBSTree::Node* toDelete) {
    Node*& r = Tree.root;
    Node* y = toDelete;
    Node* toSave;
    int y_original_color = y->color;
    if(toDelete->left == nullptr){
        toSave = toDelete->right;
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
        }else if(toSave) toSave->parent = y;
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
void RBBSTree<T>::deleteT(const std::string &nameToSearch) {
    Node* toDelete = searchNode(nameToSearch);
    if(toDelete) deleteInTree(*this,toDelete);
}

template<class T>
typename RBBSTree<T>::Node* RBBSTree<T>::searchNode(const std::string& nameToSearch) const {
    Node* tmp = root;
    while(tmp != nullptr){
        if(*(tmp->info) == nameToSearch)
            return tmp;
        else tmp = (*(tmp->info) < nameToSearch) ? tmp->right : tmp->left;
    }
    return nullptr;
}

template<class T>
const std::vector<const T*> RBBSTree<T>::search(const std::string& subStrToSearch) const {
    std::vector<const T*> result;
    for(Node* start = min;start != nullptr;start=start->succ){
        int indexOfSubStrToSearch = 0;
        std::string currentName = *(start->info);
        for(std::string::const_iterator cit = currentName.begin();cit != currentName.end();++cit){
            if(*cit == subStrToSearch[indexOfSubStrToSearch]){
                indexOfSubStrToSearch++;
            }
        }

        if(indexOfSubStrToSearch == subStrToSearch.size()){
            result.push_back(start->info);
        }
    }
    return result;
}

template<class T>
template<class U>
std::vector<const T *> RBBSTree<T>::filter() const {
    Node* start = min; Node* next = nullptr;
    std::vector<const T*> saved;
    while (start){
        if(start->succ) next = start->succ;
        const U* savedPointer = dynamic_cast<const U*>(start->info);
        if(savedPointer) saved.push_back(static_cast<const T*>(savedPointer));
        start = next;
        next = nullptr;
    }
    return saved;
}

template<class T>
const std::vector<const T*> RBBSTree<T>::toVector() const {
    std::vector<const T*> result;
    for(Node* start = min;start; start= start->succ) result.push_back(start->info);
    return result;
}

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
            currentPointer++;
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
            currentPointer--;
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
const T* RBBSTree<T>::const_iterator::operator->() const {
    return currentPointer->info;
}

template<class T>
const T& RBBSTree<T>::const_iterator::operator*() const {
    return *(currentPointer->info);
}

template<class T>
bool RBBSTree<T>::const_iterator::operator!=(const RBBSTree<T>::const_iterator& cit) const {
    return !(cit.currentPointer == currentPointer && cit.isEnd == isEnd && cit.isStart == isStart);
}
template class RBBSTree<SerializableObject>;
template std::vector<const SerializableObject*> RBBSTree<SerializableObject>::filter<Account>() const;
template std::vector<const SerializableObject*> RBBSTree<SerializableObject>::filter<CryptoWallet>() const;
template std::vector<const SerializableObject*> RBBSTree<SerializableObject>::filter<CreditCard>() const;
template std::vector<const SerializableObject*> RBBSTree<SerializableObject>::filter<Note>() const;
template std::vector<const SerializableObject*> RBBSTree<SerializableObject>::filter<Contact>() const;
template std::vector<const SerializableObject*> RBBSTree<SerializableObject>::filter<SerializableObject>() const;
