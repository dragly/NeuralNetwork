#ifndef BALANCESIMULATOR_H
#define BALANCESIMULATOR_H

#include "physicssimulatorabstract.h"

class BalanceSimulator : public PhysicsSimulatorAbstract
{
Q_OBJECT
public:
    BalanceSimulator(QObject *parent);
    double *parameters();
    bool advance(double *parameters);
private:
    QGraphicsScene *simulatorScene;
    QGraphicsItem *line;
    QTimer *timer;
    double lineAngularVelocity;

};

#endif // BALANCESIMULATOR_H
