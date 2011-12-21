#ifndef BALANCESIMULATOR2_H
#define BALANCESIMULATOR2_H

#include "physicssimulatorabstract.h"

class BalanceSimulator2 : public PhysicsSimulatorAbstract
{
    Q_OBJECT
    public:
        BalanceSimulator2(QObject *parent);
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
        double x;
        double xVel;

        int counter;

        int firstRun; //one run at each side
};

#endif // BALANCESIMULATOR2_H
