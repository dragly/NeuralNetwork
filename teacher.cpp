#include "teacher.h"
#include "balancesimulator.h"
#include "keyboardinputnetwork.h"
#include "geniousnetwork.h"
#include "BinaryNetwork/binarynetwork1.h"

Teacher::Teacher(QObject *parent) :
    QObject(parent)
{
    physicsSimulator = new BalanceSimulator(this);

    //neuralNetwork = new GeniousNetwork();

    BinaryInputHandler** tmp = new BinaryInputHandler*[2];
    tmp[0]= new BinaryInputHandler(0,0.5,0.9);
    tmp[1]= new BinaryInputHandler(0,0.1,0.5);
    neuralNetwork = new BinaryNetwork1(1,2,2,tmp);

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
