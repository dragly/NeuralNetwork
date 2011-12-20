#include "geniousnetwork.h"

GeniousNetwork::GeniousNetwork()
{
    networkView = new QGraphicsView();
    leftEngineOn = false;
    rightEngineOn = false;
}

void GeniousNetwork::advance(double *parameters) {
    if(parameters[0] < 0.9 && parameters[0] > 0.5) {
        rightEngineOn = true;
    } else {
        rightEngineOn = false;
    }
    if(parameters[0] > 0.1 && parameters[0] < 0.5) {
        leftEngineOn = true;
    } else {
        leftEngineOn = false;
    }
}

double* GeniousNetwork::parameters() {
    double *params = new double[2];
    if(leftEngineOn) {
        params[0] = 1.0;
    } else {
        params[0] = 0.0;
    }
    if(rightEngineOn) {
        params[1] = 1.0;
    } else {
        params[1] = 0.0;
    }
    return params;
}
