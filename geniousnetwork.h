#ifndef GENIOUSNETWORK_H
#define GENIOUSNETWORK_H

#include "neuralnetworkabstract.h"

class GeniousNetwork : public NeuralNetworkAbstract
{
public:
    GeniousNetwork();

    void advance(double *parameters);
    double * parameters();

private:
    bool leftEngineOn;
    bool rightEngineOn;
};

#endif // GENIOUSNETWORK_H
