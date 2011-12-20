#include "balancesimulator.h"
#include <QtDebug>
#include "math.h"

BalanceSimulator::BalanceSimulator(QObject *parent) : PhysicsSimulatorAbstract(parent)
{
    simulatorView = new QGraphicsView();
    simulatorScene = new QGraphicsScene();
    simulatorView->setScene(simulatorScene);
    line = simulatorScene->addLine(0,0,0,40);
    line->setRotation(190);
}

bool BalanceSimulator::advance(double *parameters) {
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
    if(-M_PI / 2 < realRotation && realRotation < M_PI / 2) {
        return false;
    } else {
        return true;
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
