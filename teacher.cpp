#include "teacher.h"
#include "balancesimulator.h"
#include "balancesimulator2.h"
#include "keyboardinputnetwork.h"
#include "geniousnetwork.h"
#include "BinaryNetwork/binarynetwork1.h"

Teacher::Teacher(QObject *parent) :
    QObject(parent)
{
    physicsSimulator = new BalanceSimulator2(this);

    neuralNetwork = new KeyboardInputNetwork();

    //BinaryInputHandler** tmp = new BinaryInputHandler*[2];
    //tmp[0]= new BinaryInputHandler(0,0.5,0.9);
    //tmp[1]= new BinaryInputHandler(0,0.1,0.5);
    //neuralNetwork = new BinaryNetwork1(1,2,2,tmp);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(advanceVisualization()));
    // Reset everything
    this->reset();
    oldTime = 0;
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


    //Avoid continued evolution when the concept is working.
    int testtime=-1;
    physicsSimulator->reset();

    while (testtime < 0) {
        testtime = step();
    }

    if (oldTime>90000) {
        qDebug() << "Time was"<< oldTime;
        return;
    }

    for (int i=0;i< numCycles;i++) {
        numberOfTrials++;
        physicsSimulator->reset();

        neuralNetwork->Evolve();

        int time = -1;
        while (time < 0) {
            time = step();
        }

        if (time > 90000) { //The number shouldn't be set by the simulator.
            qDebug("Success");
            qDebug() << "Number of trials was" << numberOfTrials;
            oldTime=time;
            break;
        }

        if (time >= oldTime) {
            oldTime=time;
        } else {
            neuralNetwork->revertEvolve();
        }
    }

    qDebug() << "Time was"<< oldTime;

    physicsSimulator->reset();
    neuralNetwork->reset();
    physicsSimulator->refreshView();
    neuralNetwork->refreshView();
}

void Teacher::reset() {
    numberOfTrials = 0;
    physicsSimulator->reset();
    timer->stop();
    neuralNetwork->reset();
}


void Teacher::setCycles(int _cycles) {
    numCycles = _cycles;
}

void Teacher::advanceVisualization() {

    int time = step();
    physicsSimulator->refreshView();
    neuralNetwork->refreshView();

    if (time > 0) {
        timer->stop();
        qDebug() << time;
        physicsSimulator->reset();
        neuralNetwork->reset();

        physicsSimulator->refreshView();
        neuralNetwork->refreshView();
        return;
    }
}

void Teacher::visualize() {
    physicsSimulator->reset();
    neuralNetwork->reset();
    timer->start(1);
}
