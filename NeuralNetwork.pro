#-------------------------------------------------
#
# Project created by QtCreator 2011-12-19T23:24:00
#
#-------------------------------------------------

QT       += core gui

TARGET = NeuralNetwork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    teacher.cpp \
    physicssimulatorabstract.cpp \
    neuralnetworkabstract.cpp \
    switchboard.cpp \
    balancesimulator.cpp \
    keyboardinputnetwork.cpp \
    geniousnetwork.cpp \
    BinaryNetwork/binarynode.cpp \
    BinaryNetwork/binarynetwork1.cpp \
    BinaryNetwork/binaryinputhandler.cpp

HEADERS  += mainwindow.h \
    teacher.h \
    physicssimulatorabstract.h \
    neuralnetworkabstract.h \
    switchboard.h \
    balancesimulator.h \
    keyboardinputnetwork.h \
    geniousnetwork.h \
    BinaryNetwork/binarynode.h \
    BinaryNetwork/binarynetwork1.h \
    BinaryNetwork/binaryinputhandler.h \
    helpers.h

FORMS    += mainwindow.ui



















