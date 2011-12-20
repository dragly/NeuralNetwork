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

int Teacher::step() {
    physicsSimulatorParams = physicsSimulator->parameters();
    neuralNetwork->advance(physicsSimulatorParams);
    delete [] physicsSimulatorParams;

    neuralNetworkParams = neuralNetwork->parameters();
    int time = physicsSimulator->advance(neuralNetworkParams);
    delete [] neuralNetworkParams;

    return time;
}

void Teacher::teach() {
    int oldTime = 0;
    qDebug("test");
    physicsSimulator->reset();

    for (int i=0;i< numCycles;i++) {

        int time = -1;
        while (time<0) {
            time = step();
        }

        if (time > 75000) { //The number shouldn't be set by the simulator.
            qDebug("Success");
            break;
        }

        if (time >= oldTime) {
            oldTime=time;
            neuralNetwork->Evolve();
        } else {
            neuralNetwork->revertEvolve();
            neuralNetwork->Evolve();
        }
        continue;
    }

}


void Teacher::setCycles(int _cycles) {
    numCycles = _cycles;
}

void Teacher::advanceVisualization() {

   int time = step();

    if (time > 0) {
        timer->stop();
        return;
    }
}

void Teacher::visualize() {
    timer->start(1);
}
