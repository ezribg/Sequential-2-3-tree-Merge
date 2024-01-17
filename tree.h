#ifndef TREE
#define TREE
#include "node.h"
using namespace std;


class Tree {
    //int const CAP = 2000; // tree needs a number bigger than biggest possible insertion (999)
    Node * root;
    //void postOrder(Node * start);

    public:
    Tree(); // constructor
    //Tree(int val);
    Tree(Node * r);
    Node * search(Node * r, int valToFind);
    bool insert(int valToAdd);
    bool del(int valToKill);
    void print() {postOrder(root);}
    void postOrder(Node * start);

    Node * getRoot() {return root;}
};

#endif