#include "RBBSTree.h"

template<class T>
RBBSTree<T>::Node::Node(const T *i, Node *p, Node *s, Node *par, Node *l, Node *r, int c) : info(i), pre(p), succ(s),
                                                                                            parent(par), left(l),
                                                                                            right(r), color(c) {}

template<class T>
RBBSTree<T>::Node::~Node() {
    delete info;
}

template<class T>
RBBSTree<T>::RBBSTree() :  min(nullptr), max(nullptr) {
    TNULL = new Node(nullptr);
    root = TNULL;
}

template<class T>
bool RBBSTree<T>::insert(const T *info) {
    Node *node = new Node(info, nullptr, nullptr, nullptr, TNULL, TNULL, 1);
    if (searchNode(*info) != TNULL) return false;

    Node *y = nullptr;
    Node *x = this->root;

    while (x != TNULL) {
        y = x;
        if (*(node->info) < *(x->info)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
        min = root;
        max = root;
    } else if (*(node->info) <= *(y->info)) {
        y->left = node;
        node->pre = y->pre;
        if (node->pre) node->pre->succ = node;
        y->pre = node;
        node->succ = y;
    } else {
        y->right = node;
        node->succ = y->succ;
        if (node->succ) node->succ->pre = node;
        y->succ = node;
        node->pre = y;
    }

    if (min != nullptr) {
        if ((*info) <= (*(min->info))) min = node;
        if ((*info) > (*(max->info))) max = node;
    } else {
        min = node;
        max = node;
    }

    if (node->parent == nullptr) {
        node->color = 0;
        return true;
    }

    if (node->parent->parent == nullptr) {
        return true;
    }

    insertFixUp(node);
    return true;
}

template<class T>
void RBBSTree<T>::insertFixUp(Node *k) {
    Node *u;
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;

            if (u->color == 1) {
                u->color = 0;
                k->parent->color = 0;
                k->parent->parent->color = 1;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = 0;
                k->parent->parent->color = 1;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = 0;
}

template<class T>
void RBBSTree<T>::transplant(Node *u, Node *v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

template<class T>
void RBBSTree<T>::leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template<class T>
void RBBSTree<T>::rightRotate(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::begin() const {
    const_iterator cit;
    if (root != TNULL) {
        cit.currentPointer = min;
        cit.isStart = false;
        cit.isEnd = false;
    } else {
        cit.currentPointer = nullptr;
        cit.isStart = true;
        cit.isEnd = true;
    }
    return cit;
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::end() const {
    const_iterator cit;
    if (root != TNULL) {
        cit.currentPointer = max;
        ++cit.currentPointer;
        cit.isStart = false;
        cit.isEnd = true;
    } else {
        cit.currentPointer = nullptr;
        cit.isStart = true;
        cit.isEnd = true;
    }
    return cit;
}

template<class T>
RBBSTree<T>::~RBBSTree() {
    Node *start = min;
    Node *next = nullptr;
    while (start) {
        if (start->succ) next = start->succ;
        delete start;
        start = next;
        next = nullptr;
    }
    delete TNULL;
}

template<class T>
void RBBSTree<T>::deleteNodeHelper(Node *toDelete) {
    Node *x, *y;
    y = toDelete;
    int y_original_color = y->color;
    if (toDelete->left == TNULL) {
        x = toDelete->right;
        transplant(toDelete, toDelete->right);
    } else if (toDelete->right == TNULL) {
        x = toDelete->left;
        transplant(toDelete, toDelete->left);
    } else {
        y = toDelete->succ;
        y_original_color = y->color;
        x = y->right;
        if (y->parent == toDelete) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = toDelete->right;
            y->right->parent = y;
        }

        transplant(toDelete, y);
        y->left = toDelete->left;
        y->left->parent = y;
        y->color = toDelete->color;
    }
    if (toDelete->pre) toDelete->pre->succ = toDelete->succ;
    if (toDelete->succ) toDelete->succ->pre = toDelete->pre;
    if (toDelete == min) min = toDelete->succ;
    if (toDelete == max) max = toDelete->pre;
    delete toDelete;
    if (y_original_color == 0) {
        deleteFixUp(x);
    }
}

template<class T>
bool RBBSTree<T>::deleteT(const std::string &nameToSearch) {
    Node *toDelete = searchNode(nameToSearch);
    if (toDelete != TNULL) {
        deleteNodeHelper(toDelete);
        return true;
    } else return false;
}

template<class T>
void RBBSTree<T>::deleteFixUp(Node *x) {
    Node *s;
    while (x != root && x->color == 0) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {
                if (s->right->color == 0) {
                    s->left->color = 0;
                    s->color = 1;
                    rightRotate(s);
                    s = x->parent->right;
                }

                s->color = x->parent->color;
                x->parent->color = 0;
                s->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == 1) {
                s->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == 0 && s->right->color == 0) {
                s->color = 1;
                x = x->parent;
            } else {
                if (s->left->color == 0) {
                    s->right->color = 0;
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }

                s->color = x->parent->color;
                x->parent->color = 0;
                s->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}

template<class T>
typename RBBSTree<T>::Node *RBBSTree<T>::searchNode(const std::string &nameToSearch) const {
    Node *tmp = root;
    while (tmp != TNULL) {
        if (*(tmp->info) == nameToSearch)
            return tmp;
        else
            tmp = (*(tmp->info) < nameToSearch) ? tmp->right : tmp->left;
    }
    return TNULL;
}

template<class T>
const std::vector<const T *> RBBSTree<T>::search(const std::string &subStrToSearch) const {
    std::vector<const T *> result;
    for (Node *start = min; start != nullptr; start = start->succ) {
        int indexOfSubStrToSearch = 0;
        std::string currentName = *(start->info);
        for (std::string::const_iterator cit = currentName.begin(); cit != currentName.end(); ++cit) {
            if (*cit == subStrToSearch[indexOfSubStrToSearch]) {
                indexOfSubStrToSearch++;
            }
        }

        if (indexOfSubStrToSearch == subStrToSearch.size()) {
            result.push_back(start->info);
        }
    }
    return result;
}

template<class T>
template<class U>
std::vector<const T *> RBBSTree<T>::filter() const {
    Node *start = min;
    Node *next = nullptr;
    std::vector<const T *> saved;
    while (start) {
        if (start->succ) next = start->succ;
        const U *savedPointer = dynamic_cast<const U *>(start->info);
        if (savedPointer) saved.push_back(static_cast<const T *>(savedPointer));
        start = next;
        next = nullptr;
    }
    return saved;
}

template<class T>
const std::vector<const T *> RBBSTree<T>::toVector() const {
    std::vector<const T *> result;
    for (Node *start = min; start; start = start->succ) result.push_back(start->info);
    return result;
}

template<class T>
typename RBBSTree<T>::const_iterator &RBBSTree<T>::const_iterator::operator++() {
    if (!isEnd && !isStart) {
        if (currentPointer->succ == nullptr) {
            isEnd = true;
            currentPointer++;
        } else {
            currentPointer = currentPointer->succ;
        }
    }
    if (isStart) {
        isStart = false;
        currentPointer++;
    }
    return (*this);
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::const_iterator::operator++(int) {
    const_iterator cit = (*this);
    // Essendo che isEnd e isStart non possono essere true assieme (accadrebbe con un albero vuoto, ma presupponiamo
    // che non si iteri su un albero vuoto): qui controllo se entrambi sono a false
    if (!isEnd && !isStart) {
        if (currentPointer->succ == nullptr) {
            isEnd = true;
            currentPointer++;
        } else {
            currentPointer = currentPointer->succ;
        }
    }
        // In questo caso controllo se isStart è true (e quindi ha rotto la condizione di prima)
    else if (isStart) {
        isStart = false;

        currentPointer++;
    }
    // Non mi occupo della isEnd==true perchè in tal caso non devo fare niente
    return cit;
}

template<class T>
typename RBBSTree<T>::const_iterator &RBBSTree<T>::const_iterator::operator--() {
    if (!isStart && !isEnd) {
        if (currentPointer->pre == nullptr) {
            isStart = true;
            currentPointer--;
        } else {
            currentPointer = currentPointer->pre;
        }
    }
    if (isEnd) {
        isEnd = false;
        currentPointer--;
    }
    return (*this);
}

template<class T>
typename RBBSTree<T>::const_iterator RBBSTree<T>::const_iterator::operator--(int) {
    const_iterator cit = (*this);
    if (!isStart && !isEnd) {
        if (currentPointer->pre == nullptr) {
            isStart = true;
            currentPointer--;
        } else {
            currentPointer = currentPointer->pre;
        }
    } else if (isEnd) {
        isEnd = false;
        currentPointer--;
    }
    return cit;
}

template<class T>
const T *RBBSTree<T>::const_iterator::operator->() const {
    return currentPointer->info;
}

template<class T>
const T &RBBSTree<T>::const_iterator::operator*() const {
    return *(currentPointer->info);
}

template<class T>
bool RBBSTree<T>::const_iterator::operator!=(const RBBSTree<T>::const_iterator &cit) const {
    return !(cit.currentPointer == currentPointer && cit.isEnd == isEnd && cit.isStart == isStart);
}

template
class RBBSTree<SerializableObject>;

template std::vector<const SerializableObject *> RBBSTree<SerializableObject>::filter<Account>() const;

template std::vector<const SerializableObject *> RBBSTree<SerializableObject>::filter<CryptoWallet>() const;

template std::vector<const SerializableObject *> RBBSTree<SerializableObject>::filter<CreditCard>() const;

template std::vector<const SerializableObject *> RBBSTree<SerializableObject>::filter<Note>() const;

template std::vector<const SerializableObject *> RBBSTree<SerializableObject>::filter<Contact>() const;

template std::vector<const SerializableObject *> RBBSTree<SerializableObject>::filter<SerializableObject>() const;
