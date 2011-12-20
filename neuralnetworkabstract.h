#ifndef NEURALNETWORKABSTRACT_H
#define NEURALNETWORKABSTRACT_H

#include <QtGui>

class NeuralNetworkAbstract
{
public:
    NeuralNetworkAbstract();
    QGraphicsView *networkView;
    virtual double* parameters() { return NULL; }
    virtual void advance(double *parameters) {}
};

#endif // NEURALNETWORKABSTRACT_H
