#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "dataset.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QVector<double> data;
    QVector<double>dataVector;
    Dataset *myData;


public slots:
    void saveDataToFileAndShowGraphInGnuPlot();
    void showGraph();

    void updateCapability(double value);




};

#endif // MAINWINDOW_H
