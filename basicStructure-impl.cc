#include "basicStructures.cc"
#include "iostream"

// BinaryNode methods
template <typename T>
void BinaryNode<T>::printSubTree(BinaryNode<T> *node, int depth) const {
    if (!node) return;

    printSubTree(node->rightchild.get(), depth + 1);
    
    for (int i = 0; i < depth; ++i) cout << "   ";
    cout << node->val << endl;

    printSubTree(node->leftchild.get(), depth + 1);
}


// BinaryTree methods
template <typename T>
void BinaryTree<T>::printTree() const {
    printSubTree(root.get(), 0);
}

template <typename T>
stack<BinaryNode<T> *> BinaryTree<T>::getPredecessors(T v) const {
    stack<BinaryNode<T> *> st;
    BinaryNode<T> curnode = root.get();

    while (curnode) {
        if (v == curnode->val) {
            st.push(curnode);
            break;
        }
        st.push(curnode);
        if (v < curnode->val) curnode = curnode->leftchild.get();
        else curnode = curnode->rightchild.get();
    }
    return st;
}


// AVLtree methods
template <typename T>
BinaryNode<T> *AVLtree<T>::search(T v) const {
    BinaryNode<T> *curnode = this->root.get();
    while(curnode) {
        if (curnode->val == v) return curnode;
        if (v < curnode->val) curnode = curnode->leftchild.get();
        else curnode = curnode->rightchild.get();
    }
    return nullptr;
}

// on this now, have to figure out rotations - have to add height node augmentation
// CREATE A NORMAL INSERTION FUNCTION FOR BINARY TREE - to call first, prior to fixing - or not, its a Abstract Class after all

template <typename T>
void AVLtree<T>::insert(T v) {
    
}



