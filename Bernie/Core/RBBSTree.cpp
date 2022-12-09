//#notReviewed
#include "RBBSTree.h"

template<class T>
RBBSTree<T>::Node::Node(const T& i, Node* p, Node* s,Node* par, Node* l,Node* r): info(i), pre(p), succ(s), parent(par), left(l), rigth(r) { }




