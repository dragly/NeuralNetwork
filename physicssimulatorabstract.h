#ifndef PHYSICSSIMULATORABSTRACT_H
#define PHYSICSSIMULATORABSTRACT_H

#include <QtGui>

class PhysicsSimulatorAbstract : public QObject
{
Q_OBJECT
public:
    explicit PhysicsSimulatorAbstract(QObject *parent = 0);
    QGraphicsView *simulatorView;
    virtual void simulate() {}
    virtual double *parameters() { return NULL; }
    virtual bool advance(double *parameters) { return false; }
};

#endif // PHYSICSSIMULATORABSTRACT_H
