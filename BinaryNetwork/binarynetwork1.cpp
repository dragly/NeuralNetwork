#include "binarynetwork1.h"

BinaryNetwork1::BinaryNetwork1(int _numInputs, int _numOutputs, int _numInputHandlers, BinaryInputHandler** _inputHandlers)
{
    this->numInputs = _numInputs;
    this->numOutputs = _numOutputs;
    this->numInputHandlers = _numInputHandlers;

    networkView = new QGraphicsView();

    this->inputHandlers = _inputHandlers;
    this->outputs = new double[numOutputs];


    //add and connect input nodes
    for (int i=0;i<_numInputHandlers;i++) {
        BinaryNode* tmp = new BinaryNode();
        inputHandlers[i]->setConnectedNode(tmp);
        nodes.push_back(tmp);
    }

    //add output nodes
    for (int i=0;i<_numOutputs;i++) {
        nodes.push_back(new BinaryNode());
    }
}

BinaryNetwork1::~BinaryNetwork1() {
    delete [] inputHandlers;
    delete [] outputs;
    delete networkView;

    while (!nodes.empty())
        delete nodes.back();
}

void BinaryNetwork1::advance(double *parameters)
{
    //send a current trough our circuit
    for (int i = 0; i < numInputs;i++)
        for  (int j = 0; j < numInputHandlers;j++)
            inputHandlers[j]->execute(i,parameters[i]);

    //read the state of the output nodes
    for (int i = 0; i < numOutputs;i++) {
        outputs[i] = (nodes.at(numInputs+i)->state())? 1.0 : 0.0;
    }
    //turn off the power
    for (int i = 0; i < numInputs;i++)
        for  (int j = 0; j < numInputHandlers;j++)
            inputHandlers[j]->reset();
}

double* BinaryNetwork1::parameters() {
   double* params = new double[numOutputs];
   for (int i = 0; i < numOutputs;i++) {
       params[i] = outputs[i];
   }
   return params;
}

//add connection

//add node

//remove node - do not allow removal of the first (numInputs+numOutputs) nodes.

//remove connection
