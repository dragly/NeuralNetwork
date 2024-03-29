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
    int advance2(double *parameters);
    void reset();
    void refreshView();
private:
    QGraphicsScene *simulatorScene;
    QGraphicsItem *line;
    QTimer *timer;
    double lineAngularVelocity;
    double rotation;

    int counter;

    int firstRun; //one run at each side
};

#endif // BALANCESIMULATOR_H
