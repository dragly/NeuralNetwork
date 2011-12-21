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
    virtual int advance(double *parameters) { return false; }
    virtual void reset() {}
    virtual void refreshView() {}

private:

};

#endif // PHYSICSSIMULATORABSTRACT_H
