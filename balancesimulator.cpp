#include "balancesimulator.h"
#include <QtDebug>
#include "math.h"

BalanceSimulator::BalanceSimulator(QObject *parent) : PhysicsSimulatorAbstract(parent)
{
    simulatorView = new QGraphicsView();
    simulatorScene = new QGraphicsScene();
    simulatorView->setScene(simulatorScene);
    line = simulatorScene->addLine(0,0,0,40);
    this->reset();
}

void BalanceSimulator::reset() {
    rotation = M_PI * 190 / 180.0;
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
    double newRotation = rotation * (1.0/2 * M_PI); // M_PI * line->rotation() / 180.0;
    newRotation+=0.5;
    double realRotation = fmod(newRotation, 1.0);

    if(realRotation < 0) {
        realRotation += 1.0;
    }

    double *params = new double[1];
    params[0] = realRotation;
    return params;
}
