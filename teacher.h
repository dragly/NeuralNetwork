#ifndef TEACHER_H
#define TEACHER_H

#include "physicssimulatorabstract.h"
#include "neuralnetworkabstract.h"

class Teacher : public QObject
{
Q_OBJECT
public:
    Teacher(QObject* parent = 0);
    PhysicsSimulatorAbstract *physicsSimulator;
    NeuralNetworkAbstract *neuralNetwork;

    void visualize();

public slots:
    void advanceVisualization();

private:
    QTimer *timer;
    double *neuralNetworkParams;
    double *physicsSimulatorParams;
};

#endif // TEACHER_H
