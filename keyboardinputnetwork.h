#ifndef KEYBOARDINPUTNETWORK_H
#define KEYBOARDINPUTNETWORK_H

#include <QObject>
#include "neuralnetworkabstract.h"

class KeyboardInputNetwork : public NeuralNetworkAbstract
{
public:
   KeyboardInputNetwork();
   void leftKeyPressed();
   void rightKeyPressed();
   void leftKeyReleased();
   void rightKeyReleased();

   void advance(double *parameters);
   double * parameters();
private:
   bool rightEngineOn;
   bool leftEngineOn;
};

class KeyboardView : public QGraphicsView {
public:
    KeyboardInputNetwork *network;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // KEYBOARDINPUTNETWORK_H
