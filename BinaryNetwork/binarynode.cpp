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

bool BinaryNode::addConnection(BinaryNode* node) {

    //check if the connection already exists
    for (int i=0;i < numChildren;i++) {
        if (children[i] == node)
            return false;
    }

    //add the connection
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

    return true;
}

bool BinaryNode::removeConnection(int index) {

    index %= numChildren+1; //it's able to accept any random positive integer

    if (numChildren < 1)
        return false;
    else if (numChildren == 1) {
        delete [] children;
        children = 0;
        numChildren=0;
    } else {
        numChildren--;
        BinaryNode** temp = new BinaryNode*[numChildren];
        int j=0;
        for (int i=0;i<numChildren+1;i++) {
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

bool BinaryNode::state() {
    return _state;
}

int BinaryNode::getNumChildren() {
    return numChildren;
}

BinaryNode** BinaryNode::getChildren(){
    return children;
}

void BinaryNode::Copy(BinaryNode* node) {

    if (numChildren > 0) {
        delete [] children;
        children = 0;
    }

    //add the vars
    _state = node->state();
    numChildren = node->getNumChildren();
    children = node->getChildren();

    if (numChildren == 0)
        return;

    //add the connections
    BinaryNode** temp = new BinaryNode*[numChildren];

    for (int i=0;i<(numChildren-1);i++) {
        temp[i]=children[i];
    }
    children=temp;
}



