#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "teacher.h"
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_visualizeButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    Teacher *teacher;
};

#endif // MAINWINDOW_H
