#include "balancesimulator.h"
#include <QtDebug>
#include "math.h"

BalanceSimulator::BalanceSimulator(QObject *parent) : PhysicsSimulatorAbstract(parent)
{
    simulatorView = new QGraphicsView();
    simulatorScene = new QGraphicsScene();
    simulatorView->setScene(simulatorScene);
    line = simulatorScene->addLine(0,0,0,40);
    simulatorScene->addLine(-100,0,100,0);
    this->reset();
}

void BalanceSimulator::reset() {
    // Random start angle
//    double offset = (double)rand()/(double)RAND_MAX;
//    rotation = M_PI * (190 - 20*offset) / 180.0;
    // Non-random start angle
    rotation = M_PI * (190) / 180.0;
    counter = 0;
    lineAngularVelocity = 0;
    refreshView();
}

int BalanceSimulator::advance(double *parameters) {
    double torque = -sin(rotation);
    if(parameters[0] > 0.0) {
        torque -= 10.0;
    }
    if(parameters[1] > 0.0) {
        torque += 10.0;
    }
    lineAngularVelocity = lineAngularVelocity + torque * 0.001;
    rotation = rotation + lineAngularVelocity * 0.001;
    double realRotation = fmod(rotation, 2 * M_PI);
    if(realRotation > M_PI) {
        realRotation -= 2*M_PI;
    }
    if(realRotation < -M_PI) {
        realRotation += 2*M_PI;
    }

    counter++;

    if (counter > 100000) //don't crash
        return 100000;

    if(-M_PI / 2 < realRotation && realRotation < M_PI / 2) {
        return counter;
    } else {
        return -1;
    }
}

void BalanceSimulator::refreshView() {
    line->setRotation(rotation * 180 / M_PI);
}

double *BalanceSimulator::parameters() {
    double realRotation = fmod(rotation, 2 * M_PI);
    double newRotation = realRotation /(2 * M_PI); // M_PI * line->rotation() / 180.0;
    newRotation-=0.5;

    if(newRotation < 0) {
        newRotation += 1.0;
    }

    double *params = new double[1];
    params[0] = newRotation;
    return params;
}
