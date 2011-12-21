#include "binarynode.h"

BinaryNode::BinaryNode()
{
    _state=false;
}

void BinaryNode::set() {
    if (_state)
        return;

    _state=true;

    for (int i = 0; i < children.length();i++) {
        children[i]->set();
    }
}

void BinaryNode::reset() {
    if (!_state)
        return;

    _state = false;

    for (int i = 0; i < children.length();i++) {
        children[i]->reset();
    }
}

bool BinaryNode::addConnection(BinaryNode* node) {

    //check if the connection already exists
    if(children.contains(node)) {
        return false;
    }

    //add the connection
    children.append(node);

    return true;
}

bool BinaryNode::removeConnection(int index) {

    index %= children.length()+1; //it's able to accept any random positive integer

    if (children.length() < 1) {
        return false;
    } else {
        children.removeAt(index);
    }
    return true;
}

bool BinaryNode::state() {
    return _state;
}

int BinaryNode::getNumChildren() {
    return children.length();
}

QList<BinaryNode*> BinaryNode::getChildren(){
    return children;
}

void BinaryNode::Copy(BinaryNode* node) {
    //add the vars
    _state = node->state();
    // make a copy of the original node's children
    children = QList<BinaryNode*>(node->getChildren());
}



