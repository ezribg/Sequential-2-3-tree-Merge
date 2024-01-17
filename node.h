#ifndef NODE
#define NODE
#include <stdlib.h>
#include <iostream>
using namespace std;

class Node {
    Node * parent;      // parent node
    int values[6];       // values of child nodes
    Node * child[6];    // child nodes
    int children;    // how many children
    int value;          // this node's value
        
    public:
    
    Node();
    Node(int val); // constructor

    void absorb(Node * newChild);
    void discard(Node * removeChild);
    //void discard(Node * removeChild);

    bool midExist();
    void sortChildren();
    void shiftUp(int val);

    int numChildren() {return children;}
    Node * getParent() { return parent;}
    int getVal() {return value;}
    int getChildVal(int index) {return values[index];}
    Node * getChild(int index) {return child[index];}

    void setParent(Node * p) {parent = p;}
    void setChild (Node * c, int index);
    void setValue(int val) {value = val;}
    
    //void postOrder()
    
};

#endif