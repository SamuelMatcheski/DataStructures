#include <iostream>
#include "basicStructures.cc"

int main() {
    AVLtree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "\nAVL Tree Structure (rotated counter-clockwise):\n" << endl;
    tree.printTree();

    tree.insert(6);

    cout << "\nAVL Tree Structure (rotated counter-clockwise):\n" << endl;
    tree.printTree();

    cout << "\nSearching for 7 and 42..." << endl;
    BinaryNode<int>* found7 = tree.search(7);
    BinaryNode<int>* found42 = tree.search(42);

    if (found7) {
        cout << "Found 7: " << found7->val << endl;
    } else {
        cout << "7 not found!" << endl;
    }

    if (found42) {
        cout << "Found 42: " << found42->val << endl;
    } else {
        cout << "42 not found!" << endl;
    }

    return 0;
}
