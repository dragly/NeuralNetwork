#include "keyboardinputnetwork.h"

KeyboardInputNetwork::KeyboardInputNetwork()
{
    networkView = new KeyboardView();
    KeyboardView *keyboardView = (KeyboardView*)networkView;
    keyboardView->network = this;
    rightEngineOn = false;
    leftEngineOn = false;
}

void KeyboardInputNetwork::advance(double *parameters) {

}

double *KeyboardInputNetwork::parameters() {
    double *params = new double[2];
    if(leftEngineOn) {
        params[0] = 1.0;
    } else {
        params[0] = 0.0;
    }
    if(rightEngineOn) {
        params[1] = 1.0;
    } else {
        params[1] = 0.0;
    }
    return params;
}

void KeyboardInputNetwork::leftKeyPressed() {
    leftEngineOn = true;
}

void KeyboardInputNetwork::rightKeyPressed() {
    rightEngineOn = true;
}

void KeyboardInputNetwork::leftKeyReleased() {
    leftEngineOn = false;
}

void KeyboardInputNetwork::rightKeyReleased() {
    rightEngineOn = false;
}

void KeyboardView::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) {
        network->leftKeyPressed();
    } else {
        network->rightKeyPressed();
    }
}


void KeyboardView::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) {
        network->leftKeyReleased();
    } else {
        network->rightKeyReleased();
    }
}
