#include "node.h"
#include "tree.h"
#include <iostream>
using namespace std;

int main() {
    Node * one = new Node(39);

    Tree * tree = new Tree(one);
    tree->insert(33);
    tree->insert(31);
    tree->insert(36);
    tree->insert(28);
    tree->insert(26);
    tree->insert(38);
    tree->insert(24);
    //cout << tree->search(one, 33)->getVal() << endl;

    tree->del(31);
    tree->print();

    delete [] one;
    delete [] tree;

    return 0;
}