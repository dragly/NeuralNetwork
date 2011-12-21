#include "binarynode.h"

BinaryNode::BinaryNode()
{
    _state=false;
}

void BinaryNode::set() {
    if (_state)
        return;

    _state=true;

    for (int i = 0; i < _children.length();i++) {
        _children[i]->set();
    }
}

void BinaryNode::reset() {
    if (!_state)
        return;

    _state = false;

    for (int i = 0; i < _children.length();i++) {
        _children[i]->reset();
    }
}

bool BinaryNode::addConnection(BinaryNode* node) {

    //check if the connection already exists
    if(_children.contains(node)) {
        return false;
    }

    //add the connection
    _children.append(node);

    return true;
}

bool BinaryNode::removeConnection(int index) {

    index %= _children.length()+1; //it's able to accept any random positive integer

    if (_children.length() < 1) {
        return false;
    } else {
        _children.removeAt(index);
    }
    return true;
}

bool BinaryNode::state() {
    return _state;
}

int BinaryNode::getNumChildren() {
    return _children.length();
}

QList<BinaryNode*> BinaryNode::children(){
    return _children;
}

void BinaryNode::Copy(BinaryNode* node) {
    //add the vars
    _state = node->state();
    // make a copy of the original node's children
    _children = QList<BinaryNode*>(node->children());
}



