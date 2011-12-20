#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "balancesimulator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    teacher = new Teacher();
    ui->visualLayout->addWidget(teacher->physicsSimulator->simulatorView);
    ui->visualLayout->addWidget(teacher->neuralNetwork->networkView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_visualizeButton_clicked()
{
    teacher->visualize();
}
