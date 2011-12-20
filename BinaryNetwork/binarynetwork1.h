#ifndef BINARYNETWORK1_H
#define BINARYNETWORK1_H

#include "neuralnetworkabstract.h"
#include "binaryinputhandler.h"
#include "binarynode.h"

class BinaryNetwork1 : public NeuralNetworkAbstract
{
public:
    BinaryNetwork1(int _numInputs, int _numOutputs,int _numInputHandlers, BinaryInputHandler **_inputs);
    ~BinaryNetwork1();

    void advance(double *parameters);
    double * parameters();

private:
    BinaryInputHandler** inputHandlers;
    int numInputs;
    int numOutputs;
    int numInputHandlers;

    double* outputs; //should be abstracted

    std::vector<BinaryNode*> nodes; //order: inputs, outputs, all other nodes
};

#endif // BINARYNETWORK1_H
