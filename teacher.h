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
    int step();
    void teach();
    void setCycles(int _cycles);
    void reset();

public slots:
    void advanceVisualization();

private:
    int numCycles;
    QTimer *timer;
    double *neuralNetworkParams;
    double *physicsSimulatorParams;
};

#endif // TEACHER_H
