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

    void Evolve();
    void revertEvolve();
    void refreshView();
    void resetView();

    bool addConnection(int fromIndex, int toIndex);
    bool removeConnection(int fromIndex, int number);

private:
    BinaryInputHandler** inputHandlers;
    int numInputs;
    int numOutputs;
    int numInputHandlers;

    double* outputs; //should be abstracted

    QList<BinaryNode*> nodes; //order: inputs, outputs, all other nodes
    QList<BinaryNode*> inputNodes; //order: inputs, outputs, all other nodes
    QList<BinaryNode*> outputNodes; //order: inputs, outputs, all other nodes
    BinaryNode backupNode;
    int backUpIndex;
    QGraphicsScene *networkScene;

    QList<QGraphicsRectItem*> nodeItems;
    QList<QGraphicsRectItem*> inputItems;
    QList<QGraphicsRectItem*> outputItems;
    // Connections
    QList<QGraphicsItem*> lineItems;
    QList<QGraphicsItem*> lineEndItems;

    bool doReset;
};

#endif // BINARYNETWORK1_H
