#include "binaryinputhandler.h"

BinaryInputHandler::BinaryInputHandler(int _paramIndex, double _activeFrom, double _activeTo)
{
    paramIndex = _paramIndex;
    activeLowerLimit = _activeFrom;
    activeUpperLimit = _activeTo;
}

void BinaryInputHandler::execute(int index, double value) {

    if (paramIndex == index && convertToBinary(value))
        connectedNode->set();
}

void BinaryInputHandler::reset() { //remove the set states, so it's ready for a new run through
    connectedNode->reset();
}

bool BinaryInputHandler::convertToBinary(double in) {
    if (in < activeUpperLimit && in > activeLowerLimit)
        return true;
    else return false;
}

void BinaryInputHandler::setConnectedNode(BinaryNode* node) {
    this->connectedNode=node;
}
