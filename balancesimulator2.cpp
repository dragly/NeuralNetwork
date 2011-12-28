#include "balancesimulator2.h"

#include <QtDebug>
#include "math.h"

BalanceSimulator2::BalanceSimulator2(QObject *parent) : PhysicsSimulatorAbstract(parent)
{
    simulatorView = new QGraphicsView();
    simulatorScene = new QGraphicsScene();
    simulatorView->setScene(simulatorScene);
    line = simulatorScene->addLine(0,0,0,40);
    velocity = 0;
    position=0;
    simulatorScene->addLine(-100,0,100,0);
    this->reset();
}

void BalanceSimulator2::reset() {
    // Random start angle
    //    double offset = (double)rand()/(double)RAND_MAX;
    //    rotation = M_PI * (190 - 20*offset) / 180.0;
    // Non-random start angle
    rotation = M_PI * (190) / 180.0;
    counter = 0;
    lineAngularVelocity = 0;
    velocity = 0;
    position=0;
    firstRun=-1;
    refreshView();
}
int BalanceSimulator2::advance(double *parameters) {
    double torque = -sin(rotation);
    double xAccel = 0;
    double constAccel = 2.0;
    if(parameters[0] > 0.0) {
        torque += constAccel*cos(rotation);
        xAccel += constAccel;

    }
    if(parameters[1] > 0.0) {
        xAccel -= constAccel;
        torque -= constAccel*cos(rotation);
    }

    velocity += xAccel * 0.020;
    position = position + velocity * 0.001;
    lineAngularVelocity += torque * 0.001;
    rotation = rotation + lineAngularVelocity * 0.001;
    double realRotation = fmod(rotation, 2 * M_PI);
    if(realRotation > M_PI) {
        realRotation -= 2*M_PI;
    }
    if(realRotation < -M_PI) {
        realRotation += 2*M_PI;
    }

    counter++;

    if (counter > 100000) //it doesn't crash
        return 100000;
    int time;
    if(-M_PI / 2 < realRotation && realRotation < M_PI / 2) {
        time = counter;
    } else if (position > 100.0 || position < -100.0) {
        time = counter;
    } else {
        time = -1;
    }
    if (time<0) {
        return -1;
    } else if (firstRun==-1) {
        reset();
        rotation = M_PI * (170) / 180.0;
        firstRun=time;
        return -1;
    } else {
        time +=firstRun;
        time /=2;
        firstRun=-1;
        return time;
    }
}

void BalanceSimulator2::refreshView() {
    line->setX(position);
    line->setRotation(rotation * 180 / M_PI);
}

double *BalanceSimulator2::parameters() {
    double realRotation = fmod(rotation, 2 * M_PI);
    double newRotation = realRotation /(2 * M_PI); // M_PI * line->rotation() / 180.0;
    newRotation-=0.5;

    if(newRotation < 0) {
        newRotation += 1.0;
    }

    double *params = new double[3];
    params[0] = newRotation;
    params[1] = position;
    params[2] = velocity;
    return params;
}
