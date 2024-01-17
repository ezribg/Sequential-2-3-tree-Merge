#include "tree.h"
#include "node.h"

Tree::Tree() {
    root = new Node(1000);
}

Tree::Tree(Node * r) {
    root = r;
}


// NOTE: only return if it is a leaf node
Node * Tree::search(Node * r, int valToFind) {
    // must be leaf, must either be equla to the value or the first thing bigger than it
    if (r->numChildren() == 0)
        return r;
    
    if (valToFind <= r->getChildVal(0))
        return search(r->getChild(0), valToFind);
    else if (valToFind <= r->getChildVal(1))
        return search(r->getChild(1), valToFind);
    else if (r->midExist())
        return search(r->getChild(2), valToFind);

    return NULL;
}


bool Tree::insert(int valtoAdd) {
    Node * absorber = search(root, valtoAdd);

    if (absorber->getVal() == valtoAdd)
        return false;
    
    Node * newChild = new Node(valtoAdd);
    absorber->absorb(newChild);
    
    if (root->getParent() != NULL)
        root = root->getParent();

    return true;
}

bool Tree::del(int valToKill) {
    // return a pointer to the root of tree that contains the set of leaves S - valToKill
    
    // if a isn't in the tree, do nothing
    // otherwise, remove a from the tree, subject to the rules

    Node * leaf = search(root, valToKill);
    if (leaf->getVal() != valToKill)
        return false;

    Node * p = leaf->getParent();
    p->discard(leaf);
    leaf->setParent(NULL);

    if (p->numChildren() == 2) {
        //cout << "booty" << endl;
        p->shiftUp(p->getChildVal(1));
        return true;
    }
    
    Node * b = p->getChild(0);
    if (p->getParent() == NULL) {
        root = b;
        return true;
    }

    int totChildren = 0;
    Node * mr = p->getParent();
    for (int i = 0; i < mr->numChildren(); i++)
        totChildren += mr->getChild(i)->numChildren();


    // am i the left, right, or middle?
    int index = 0;
        for(int i = 1; i < mr->numChildren(); i++) {
            if (mr->getChildVal(i) == p->getVal())
                index = i;
        }


    Node * uncle = mr->getChild(1);
    
    if (totChildren >= 4) {
        // distribute children among at least two parents
        // may need to remove a parent (case of 5 children)

        Node * nephew;

        if (totChildren == 5) {
            if (index == 1) {
                uncle = mr->getChild(0);
            }

            uncle->setChild(b, 2);
            p->discard(b);
            mr->discard(p);
            uncle->sortChildren();
            uncle->shiftUp(uncle->getChildVal(2));
            //delete [] p;
            return true;
        }

        if (totChildren == 7) {
            if (index == 0) {
                nephew = uncle->getChild(0);
            }
            else if (index == 1) {
                uncle = mr->getChild(2);
                nephew = uncle->getChild(0);
            }
            else {
                nephew = uncle->getChild(2);
            }
        }

        if (totChildren == 4) {
            if (index == 0) {
                nephew = uncle->getChild(0);
            }
            else {
                uncle = mr->getChild(0);
                nephew = uncle->getChild(2);
            }
        }

        if (totChildren == 6) {
            if (index == 0) {
                if (uncle->numChildren() == 3) {
                    nephew = uncle->getChild(0);
                }
                else {
                    uncle->setChild(b, 2);
                    p->discard(b);
                    mr->discard(p);
                    uncle->sortChildren();
                    uncle->shiftUp(uncle->getChildVal(2));
                    delete [] p;
                    return true;
                }
            }
            else if (index == 1) {
                if (mr->getChild(0)->numChildren() == 3) {
                    uncle = mr->getChild(0);
                    nephew = uncle->getChild(2);
                }
                else {
                    uncle = mr->getChild(2);
                    nephew = uncle->getChild(0);
                }

            }
            else {
                if (uncle->numChildren() == 3) {
                    nephew = uncle->getChild(2);
                }
                else {
                    uncle->setChild(b, 2);
                    p->discard(b);
                    mr->discard(p);
                    uncle->sortChildren();
                    uncle->shiftUp(uncle->getChildVal(2));
                    delete [] p;
                    return true;
                }
            }
        }

        p->setChild(nephew, 1);
        p->sortChildren();
        uncle->discard(nephew);
        uncle->shiftUp(uncle->getChildVal(1));
        p->shiftUp(p->getChildVal(1));
        
        return true;
    }

    if (index == 1) {
        // move to right uncle
        uncle = mr->getChild(0);
    }

    uncle->setChild(b, 2);
    p->discard(b);
    uncle->sortChildren();
    int nVal = uncle->getChildVal(2);
    uncle->shiftUp(nVal);

    return del(p->getVal());
}


void Tree::postOrder(Node * current) {
    if (current == NULL)
        return;
    
    postOrder(current->getChild(0));
    postOrder(current->getChild(1));
    if (current->midExist())
        postOrder(current->getChild(2));
    
    cout << current->getVal() << endl;
}