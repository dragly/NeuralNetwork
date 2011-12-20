#include "binarynode.h"

BinaryNode::BinaryNode()
{
    _state=false;
    numChildren=0;
}

void BinaryNode::set() {
    if (_state)
        return;

    _state=true;

    for (int i = 0; i < numChildren;i++) {
        children[i]->set();
    }
}

void BinaryNode::reset() {
    if (!_state)
        return;

    _state = false;

    for (int i = 0; i < numChildren;i++) {
        children[i]->reset();
    }
}

bool BinaryNode::state() {
    return _state;
}

void BinaryNode::addConnection(BinaryNode* node) {
    numChildren++;
    BinaryNode** temp = new BinaryNode*[numChildren];
    if (numChildren > 1) {
        for (int i=0;i<(numChildren-1);i++) {
            temp[i]=children[i];
        }
        delete [] children;
    }
    children=temp;
    children[numChildren-1]=node;
}

bool BinaryNode::removeConnection(int index) {
    index %= numChildren; //it's able to accept any random positive integer
    children[index]= 0;

    if (numChildren < 1)
        return false;
    else if (numChildren == 1) {
        delete [] children;
        children = 0;
    } else {
        numChildren--;
        BinaryNode** temp = new BinaryNode*[numChildren];
        int j=0;
        for (int i=0;i<(numChildren-1);i++) {
            if (i != index) {
                temp[j]=children[i];
                j++;
            }
        }
        delete [] children;
        children=temp;
    }
    return true;
}



