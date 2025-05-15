#include <memory>
#include <stack>

using namespace std;

// AVL, a-b, Max/Min heaps, Tries (normal, pruned, compressed, multiway), quadtree, kd-tree, d-dimensional range tree


template <typename T>
struct BinaryNode {
    T val;
    int height = 0;
    unique_ptr<BinaryNode> leftchild;
    unique_ptr<BinaryNode> rightchild;
    BinaryNode(T v) : val{v} {}
    void printSubTree(BinaryNode<T> *node, int depth) const;
};

// ABSTRACT
template <typename T>
class BinaryTree {
    protected:
        unique_ptr<BinaryNode<T>> root;
        // returns a stack of ancestors (or would be ancestors) of the key. Will include v's node
        stack<BinaryNode<T> *> getPredecessors(T v) const;

    public:
        BinaryTree() : root{nullptr} {};
        virtual ~BinaryTree() {};
        
        void printTree() const;
        virtual BinaryNode<T> *search(T v) const =0;
        virtual void insert(T v) =0;
        virtual unique_ptr<BinaryNode<T>> remove(T v) =0; 
};

template <typename T>
class AVLtree : public BinaryTree<T> {
    public:
        AVLtree() : BinaryTree<T>() {}
        // O(logn) search - does not transfer ownership
        // O(1) aux space
        virtual BinaryNode<T> *search(T v) const override;
        // O(logn) insert
        // O(logn) aux space - for the getPredecessors stack
        virtual void insert(T v) override;
        // O(logn) remove - "pops" the node from the tree, transferring ownership to the caller
        // O(logn) aux space - for the getPredecessors stack
        virtual unique_ptr<BinaryNode<T>> remove(T v) override;
};


#include "basicStructures-impl.hpp"
