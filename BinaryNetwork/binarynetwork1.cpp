#include "binarynetwork1.h"

BinaryNetwork1::BinaryNetwork1(int _numInputs, int _numOutputs, int _numInputHandlers, BinaryInputHandler** _inputHandlers)
{
    this->numInputs = _numInputs;
    this->numOutputs = _numOutputs;
    this->numInputHandlers = _numInputHandlers;

    networkScene = new QGraphicsScene();
    networkView = new QGraphicsView(networkScene);

    this->inputHandlers = _inputHandlers;
    this->outputs = new double[numOutputs];


    //add and connect input nodes
    for (int i=0;i<_numInputHandlers;i++) {
        BinaryNode* tmp = new BinaryNode();
        inputHandlers[i]->setConnectedNode(tmp);
        nodes.push_back(tmp);
        inputNodes.push_back(tmp);
    }

    //add output nodes
    for (int i=0;i<_numOutputs;i++) {
        BinaryNode* tmp = new BinaryNode();
        nodes.push_back(tmp);
        outputNodes.push_back(tmp);
    }
    this->resetView();

}

BinaryNetwork1::~BinaryNetwork1() {
    delete [] inputHandlers;
    delete [] outputs;
    delete networkView;

    while (!nodes.empty())
        delete nodes.back();
}

void BinaryNetwork1::resetView() {
    networkScene->clear();

    nodeItems.clear();
    inputItems.clear();
    outputItems.clear();
    lineItems.clear();

    for(int i = 0; i < numInputHandlers; i++) {
        QPen pen;
        BinaryNode* node = inputNodes.at(i);
        if(node->state()) {
            pen = QPen(QColor(Qt::green));
        } else {
            pen = QPen(QColor(Qt::red));
        }
        QGraphicsRectItem *item = networkScene->addRect(i*10,0,5,5, pen);
        nodeItems.append(item);
        inputItems.append(item);
    }

    for(int i = 0; i < numOutputs; i++) {
        QPen pen;
        if(outputNodes.at(i)->state()) {
            pen = QPen(QColor(Qt::green));
        } else {
            pen = QPen(QColor(Qt::red));
        }
        QGraphicsRectItem *item = networkScene->addRect(i*10,20,5,5, pen);
        nodeItems.append(item);
        outputItems.append(item);
    }
    // Add lines as connections
    for(int i = 0; i < numInputHandlers + numOutputs; i++) {
        QGraphicsRectItem *fromItem = nodeItems.at(i);
        for(int j = 0; j < nodes.at(i)->children().length(); j++) {
            BinaryNode *child = nodes.at(i)->children().at(j);
            QGraphicsRectItem *toItem = nodeItems.at(nodes.indexOf(child));
            qDebug() << "Connection from" << i << "to" << j;
            qDebug() << "Positions" << fromItem->rect() << toItem->rect();
            QGraphicsLineItem *lineItem = networkScene->addLine(fromItem->rect().x() + 2.5,
                                                                fromItem->rect().y() + 2.5,
                                                                toItem->rect().x() + 2.5,
                                                                toItem->rect().y() + 2.5);
            lineItems.append(lineItem);
        }
    }

    // Make sure we don't reset this before necessary
    doReset = false;
}

void BinaryNetwork1::refreshView() {
    if(doReset) {
        this->resetView();
    }
    if(inputItems.length() != numInputHandlers) {
        qWarning() << "Wrong number of input items!";
    }
    for(int i = 0; i < numInputHandlers; i++) {
        if(inputNodes.at(i)->state()) {
            inputItems.at(i)->setPen(QPen(QColor(Qt::green)));
        } else {
            inputItems.at(i)->setPen(QPen(QColor(Qt::red)));
        }
    }
    for(int i = 0; i < numOutputs; i++) {
        if(outputNodes.at(i)->state()) {
            outputItems.at(i)->setPen(QPen(QColor(Qt::green)));
        } else {
            outputItems.at(i)->setPen(QPen(QColor(Qt::red)));
        }
    }
}

void BinaryNetwork1::advance(double *parameters)
{
    //turn off the power
    for (int i = 0; i < numInputs;i++)
        for  (int j = 0; j < numInputHandlers;j++)
            inputHandlers[j]->reset();
    //send a current trough our circuit
    for (int i = 0; i < numInputs;i++)
        for  (int j = 0; j < numInputHandlers;j++)
            inputHandlers[j]->execute(i,parameters[i]);

    //read the state of the output nodes
    for (int i = 0; i < numOutputs;i++) {
        outputs[i] = (nodes.at(numInputHandlers+i)->state())? 1.0 : 0.0;
    }
}

double* BinaryNetwork1::parameters() {
   double* params = new double[numOutputs];
   for (int i = 0; i < numOutputs;i++) {
       params[i] = outputs[i];
   }
   return params;
}

void BinaryNetwork1::revertEvolve() {
    backupNode.Copy(nodes.at(backUpIndex));
    doReset = true; // Tell the visualizer to reset to show the new connections
}

void BinaryNetwork1::Evolve() {
    //one change at a time for now..:O)
    bool success=false;
    while (!success) {
        int rn1 = rand()%2;
        if (rn1==0) {  //add connection
            int rn2 = rand()%nodes.size();
            int rn3 = rand()%nodes.size();
            success=addConnection(rn2,rn3);
        } else { //remove connection
            int rn2 = rand()%nodes.size();
            int rn3 = rand();
            success=removeConnection(rn2,rn3);
        }
    }
    doReset = true; // Tell the visualizer to reset to show the new connections
}

bool BinaryNetwork1::addConnection(int fromIndex, int toIndex) {

    if (fromIndex == toIndex)
        return false;

    backUpIndex=fromIndex;
    backupNode.Copy(nodes.at(fromIndex));

    return nodes.at(fromIndex)->addConnection(nodes.at(toIndex));
}

bool BinaryNetwork1::removeConnection(int fromIndex, int number) {

    backUpIndex=fromIndex;
    backupNode.Copy(nodes.at(fromIndex));

    return nodes.at(fromIndex)->removeConnection(number);
}

//add connection

//add node

//remove node - do not allow removal of the first (numInputs+numOutputs) nodes.

//remove connection
