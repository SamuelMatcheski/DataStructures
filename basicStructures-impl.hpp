#ifndef BASIC_STRUCTURES_IMPL_HPP
#define BASIC_STRUCTURES_IMPL_HPP

#include <iostream>
#include <stdexcept>

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
    if (root) root->printSubTree(root.get(), 0);
}

template <typename T>
stack<BinaryNode<T> *> BinaryTree<T>::getPredecessors(T v) const {
    stack<BinaryNode<T> *> st;
    BinaryNode<T> *curnode = root.get();

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
int getHeight(const BinaryNode<T> *p) {
    return p ? p->height : -1;
}

template <typename T>
void updateHeight(BinaryNode<T> *parent) {
    int leftHeight = -1;
    int rightHeight = -1;
    if (parent->leftchild) {
        leftHeight = parent->leftchild->height;
    }
    if (parent->rightchild) {
        rightHeight = parent->rightchild->height;
    }
    parent->height = max(rightHeight, leftHeight) + 1;
}

// rotate the subtree of z accordingly. Returns a pointer to the new root of this subtree
template <typename T>
unique_ptr<BinaryNode<T>> triNodeRotation(unique_ptr<BinaryNode<T>> z) {
    // z = node with imbalance
    // y = taller child of z
    // x = taller child of y (tiebreak goes to 'same side' as y)

    if (getHeight(z->leftchild.get()) > getHeight(z->rightchild.get())) {
        unique_ptr<BinaryNode<T>> y = move(z->leftchild);
        if (getHeight(y->leftchild.get()) >= getHeight(y->rightchild.get())) {
            // LL case (tiebreaks follow same side rule)
            // y becomes root. y's right child becomes new left child of z. x stays where it is, no need to define
            z->leftchild = move(y->rightchild);
            y->rightchild = move(z);

            updateHeight(y->rightchild.get());
            updateHeight(y.get());

            return y;
        } else {
            // LR case
            unique_ptr<BinaryNode<T>> x = move(y->rightchild);
            // x becomes root. x's left child becomes right child of y, and x's right child becomes left child of z

            y->rightchild = move(x->leftchild);
            z->leftchild = move(x->rightchild);
            x->leftchild = move(y);
            x->rightchild = move(z);

            updateHeight(x->leftchild.get());
            updateHeight(x->rightchild.get());
            updateHeight(x.get());

            return x;
        }
    } else {
        unique_ptr<BinaryNode<T>> y = move(z->rightchild);
        if (getHeight(y->rightchild.get()) >= getHeight(y->leftchild.get())) {
            // RR case
            z->rightchild = move(y->leftchild);
            y->leftchild = move(z);

            updateHeight(y->leftchild.get());
            updateHeight(y.get());

            return y;
        } else {
            // RL case
            unique_ptr<BinaryNode<T>> x = move(y->leftchild);
            y->leftchild = move(x->rightchild);
            z->rightchild = move(x->leftchild);
            x->rightchild = move(y);
            x->leftchild = move(z);

            updateHeight(x->rightchild.get());
            updateHeight(x->leftchild.get());
            updateHeight(x.get());

            return x;
        }
    }
}

template <typename T>
void AVLtree<T>::insert(T v) {
    // empty tree case
    if (!this->root) {
        this->root = make_unique<BinaryNode<T>>(BinaryNode<T>(v));
        return;
    }
    // getPredecessors to get pathway to key for normal insertion
    stack<BinaryNode<T> *> st = this->getPredecessors(v);
    // no duplicate keys allowed  
    if (v == st.top()->val) {
        cout << "Key is already in the tree, no duplicate keys allowed" << endl;
        return;
    }
    // basic insertion
    auto newNode = make_unique<BinaryNode<T>>(BinaryNode<T>{v});
    if (v < st.top()->val) {
        st.top()->leftchild = move(newNode);
    } else {
        st.top()->rightchild = move(newNode);
    }

    // now we go back up stack updating heights and possibly doing rotations
    while (!st.empty()) {
        BinaryNode<T>* node = st.top(); st.pop();
        updateHeight(node);

        int balance = getHeight(node->rightchild.get()) - getHeight(node->leftchild.get());

        if (abs(balance) > 1) {
            unique_ptr<BinaryNode<T>> rotatedRoot;
            // Moving here gets a little complicated, essentially we release the pointer to the node that has imbalance (whether its root or child)
            //   We give its ownership to the triNodeRotation function, that then does the roatation and returns a unique pointer to what took ^'s place
            if (st.empty()) {
                // node is the root of the tree
                rotatedRoot = triNodeRotation(move(this->root));
                this->root = move(rotatedRoot);
            } else {
                // node has a parent. Must update parents pointer
                BinaryNode<T>* parent = st.top();
                if (node->val < parent->val) {
                    rotatedRoot = triNodeRotation(move(parent->leftchild));
                    parent->leftchild = move(rotatedRoot);
                } else {
                    rotatedRoot = triNodeRotation(move(parent->rightchild));
                    parent->rightchild = move(rotatedRoot);
                }
            }

            break; // for insertion, we will only ever need one rotation
        }
    }
}

template <typename T>
unique_ptr<BinaryNode<T>> AVLtree<T>::remove(T v) {
    throw logic_error("remove() not yet implemented");
}

#endif

