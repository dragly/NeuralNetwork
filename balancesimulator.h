#ifndef BALANCESIMULATOR_H
#define BALANCESIMULATOR_H

#include "physicssimulatorabstract.h"

class BalanceSimulator : public PhysicsSimulatorAbstract
{
Q_OBJECT
public:
    BalanceSimulator(QObject *parent);
    double *parameters();
    int advance(double *parameters);
    void reset();
private:
    QGraphicsScene *simulatorScene;
    QGraphicsItem *line;
    QTimer *timer;
    double lineAngularVelocity;

    int counter;
};

#endif // BALANCESIMULATOR_H
