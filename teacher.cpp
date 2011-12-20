#include "teacher.h"
#include "balancesimulator.h"
#include "keyboardinputnetwork.h"
#include "geniousnetwork.h"

Teacher::Teacher(QObject *parent) :
    QObject(parent)
{
    physicsSimulator = new BalanceSimulator(this);
    neuralNetwork = new GeniousNetwork();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(advanceVisualization()));
}

void Teacher::advanceVisualization() {
    neuralNetworkParams = neuralNetwork->parameters();
    bool okay = physicsSimulator->advance(neuralNetworkParams);
    delete [] neuralNetworkParams;

    if (!okay) {
        timer->stop();
        return;
    }

    physicsSimulatorParams = physicsSimulator->parameters();
    neuralNetwork->advance(physicsSimulatorParams);
    delete [] physicsSimulatorParams;
}

void Teacher::visualize() {
    timer->start(1);
}
