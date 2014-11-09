#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->spnbxLowerSpec, SIGNAL(valueChanged(double)), this, SLOT(updateCapability(double))) ;

    connect(ui->spnbxUpperSpec, SIGNAL(valueChanged(double)), this, SLOT(updateCapability(double)));
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
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(showGraph()));




}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveDataToFileAndShowGraphInGnuPlot(){
    Dataset::writeDataSetToFile(dataVector);

}

void MainWindow::showGraph() {
    system("/usr/local/bin/gnuplot ~/Desktop/test/gnuplotConfiguration");

}

void MainWindow::updateCapability(double value)
{
    double lowerSpec = ui->spnbxLowerSpec->value();
    double upperSpec = ui->spnbxUpperSpec->value();

    ui->lblPotentialCapability->setText(QString::number(Dataset::calculatePotentialCapability(lowerSpec, upperSpec,dataVector)));
    ui->lblCriticalCapabilityForLoweLimit->setText(QString::number(Dataset::calculateCriticalCapabilityForLowerLimit(lowerSpec, dataVector)));
    ui->lblCriticalCapabilityForUpperLimit->setText(QString::number(Dataset::calculateCriticalCapabilityForUpperLimit(lowerSpec, dataVector)));
}
