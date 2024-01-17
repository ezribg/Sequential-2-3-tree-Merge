#include "node.h"

// Empty node constructor
Node::Node() {
    for (int i = 0; i < 6; i++) {
        values[i] = 0;
        child[i] = NULL;
    }

    parent = NULL;
    children = 0;
    value = 0;
}

// Value/leaf node constructor
Node::Node(int val) {
    value = val;
    for (int i = 0; i < 6; i++) {
        values[i] = 0;
        child[i] = NULL;
    }

    parent = NULL;
    children = 0;
}


bool Node::midExist() {
    if (children == 3)
        return true;
    return false;
}


// Set a node to a specific position
void Node::setChild(Node * c, int index) {
    c->setParent(this);
    values[index] = c->getVal();
    child[index] = c;
    children += 1;
}

// Adds node to parent of current node
// If current node is root, makes new root and makes nodes its children
void Node::absorb(Node * newChild) {
    // If current node is root
    if (parent == NULL) {
        // create new root
        Node * root = new Node(value);
        
        root->setChild(newChild, 0);
        root->setChild(this, 1);

        return;
    }

    // If not node, and parent has space, add
    if (parent->numChildren() < 3) {
        parent->setChild(newChild, 2);
        parent->sortChildren();

        if (parent->getChildVal(2) == newChild->getVal()) {
            int index = parent->numChildren();
            parent->shiftUp(parent->getChildVal(index - 1));
        }
        
    }
    else {
        // overfill p by adding a -- have to figure out where it goes
        parent->setChild(newChild, 3);
        parent->sortChildren();

        Node * oldP = parent;
        // create p-left
        Node * pleft = new Node();
        pleft->setChild(oldP->getChild(0), 0);
        pleft->setChild(oldP->getChild(1), 1);
        pleft->setValue(pleft->getChildVal(1));

        oldP->discard(oldP->getChild(0));
        oldP->discard(oldP->getChild(0));
        
        oldP->setValue(oldP->getChildVal(1));

        if (oldP->getParent() != NULL) {
            if (oldP->getParent()->getChildVal(2) == oldP->getVal())
                oldP->shiftUp(oldP->getChildVal(1));
        }

        oldP->absorb(pleft);
    }
}


// Shifts children over to overwrite discarded child
void Node::discard(Node * removeChild) {
    int index = 0;
    for (int i = 0; i < children; i++) {
        if (child[i]->getVal() == removeChild->getVal()) {
            index = i;
            break;
        }
    }

    children -= 1;
    for (int i = index; i < children; i++) {
        child[i] = child[i + 1];
        values[i] = values[i + 1];
    }

    values[children] = 0;
    child[children] = NULL;
}


// Resorts children by value
void Node::sortChildren() {
    for (int i = 0; i < children; i++) {
        for (int j = i + 1; j < children; j++) {
            if (values[i] > values[j]) {
                int tempVal = values[i];
                Node * tempC = child[i];

                values[i] = values[j];
                values[j] = tempVal;

                child[i] = child[j];
                child[j] = tempC;
            }
        }
    }
}

// pass the value up to node and each parent
void Node::shiftUp(int val) {
    int oldVal = value;
    value = val;

    if (parent == NULL) {
        return;
    }

    if (parent->midExist() && parent->getChildVal(2) == oldVal) {
        parent->shiftUp(val);
        return;
    }
    else if (!parent->midExist() && parent->getChildVal(1) == oldVal) {
        parent->shiftUp(val);
    }
}
