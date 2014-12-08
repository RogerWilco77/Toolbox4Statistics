#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->spnbxLowerSpec, SIGNAL(valueChanged(double)), this, SLOT(updateCapability(double))) ;

    connect(ui->spnbxUpperSpec, SIGNAL(valueChanged(double)), this, SLOT(updateCapability(double)));

    connect(ui->btnShowGraph, SIGNAL(clicked()), this, SLOT(updateGraph()));
    //Dataset::createRandomData(100, dataVector);




    myData = new Dataset();
    Dataset::createStandardNormalDistribution(1000, dataVector);

    ui->tblData->setRowCount(dataVector.size());
    ui->tblData->setColumnCount(1);

    for (int i = 0 ; i < (dataVector.size()); i++){
        QString datapoint;
        //datapoint = QString::number(myData->getDataVector()[i]);
        datapoint = QString::number(dataVector.at(i));
        QTableWidgetItem *newItem = new QTableWidgetItem(datapoint);
        ui->tblData->setItem(i, 0, newItem);
    }

    ui->lblSampleSize->setText(QString::number(dataVector.size()));
    ui->lblMean->setText(QString::number(Dataset::calculateMean(dataVector)));
    ui->lblSigma->setText(QString::number(Dataset::calculateSigma(dataVector)));
    ui->lblAndersonDarling->setText(QString::number(Dataset::calculateAndersonDarling(dataVector)));
    ui->lblPValue->setText(QString::number(Dataset::calculatePvalueForAndersonDarling(Dataset::calculateAndersonDarling(dataVector))));





    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(saveDataToFileAndShowGraphInGnuPlot()));




}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveDataToFileAndShowGraphInGnuPlot(){
    Dataset::writeDataSetToFile(dataVector);

}

void MainWindow::updateGraph() {

    // create the series plot
    QVector<double> x;

     for (int i = 0 ; i < dataVector.size() ; i++)
     {
         x.append(i);
     }


    ui->graphwidget->addGraph();
    ui->graphwidget->graph(0)->setData(x, dataVector);

    ui->graphwidget->xAxis->setLabel("data point");
    ui->graphwidget->yAxis->setLabel("value");


    ui->graphwidget->rescaleAxes();
    ui->graphwidget->replot();


    // create the histogram
    QCPBars *myBars = new QCPBars(ui->histogramWidget->xAxis, ui->histogramWidget->yAxis);
    ui->histogramWidget->addPlottable(myBars);
    QVector<double> keyData;
    QVector<double> valueData;
    //keyData << 1 << 2 << 3;
    //valueData << 2 << 4 << 8;

    Dataset::calculateBinsForHistogram(dataVector, 0.1, keyData, valueData);

    myBars->setData(keyData, valueData);
    myBars->setWidth(0.1);
    ui->histogramWidget->rescaleAxes();
    ui->histogramWidget->replot();



}

void MainWindow::updateCapability(double value)
{
    double lowerSpec = ui->spnbxLowerSpec->value();
    double upperSpec = ui->spnbxUpperSpec->value();

    ui->lblPotentialCapability->setText(QString::number(Dataset::calculatePotentialCapability(lowerSpec, upperSpec,dataVector)));
    ui->lblCriticalCapabilityForLoweLimit->setText(QString::number(Dataset::calculateCriticalCapabilityForLowerLimit(lowerSpec, dataVector)));
    ui->lblCriticalCapabilityForUpperLimit->setText(QString::number(Dataset::calculateCriticalCapabilityForUpperLimit(lowerSpec, dataVector)));
}
