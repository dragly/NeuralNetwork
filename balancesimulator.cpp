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
    line->setRotation(190);
    counter = 0;
    lineAngularVelocity = 0;
}

int BalanceSimulator::advance(double *parameters) {
    double rotation = M_PI * line->rotation() / 180.0;
    double torque = -sin(rotation);
    if(parameters[0] > 0.0) {
        torque -= 10.0;
    }
    if(parameters[1] > 0.0) {
        torque += 10.0;
    }
    lineAngularVelocity = lineAngularVelocity + torque * 0.001;
    rotation = rotation + lineAngularVelocity * 0.001;
    line->setRotation(rotation * 180 / M_PI);
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

double *BalanceSimulator::parameters() {
    double rotation = line->rotation() * (1.0/360.0); // M_PI * line->rotation() / 180.0;
    rotation+=0.5;
    double realRotation = fmod(rotation, 1.0);

    if(realRotation < 0) {
        realRotation += 1.0;
    }

    double *params = new double[1];
    params[0] = realRotation;
    return params;
}
