#ifndef DATASET_H
#define DATASET_H

#include <QObject>


#include <math.h>
#include <QVector>
#include <QTime>
#include <QFile>

//#include <QStandardPaths>


#include <QDebug>

//! A class to create and handle data.
/*! Use this class to create and manipulate all data elements.*/
class Dataset : public QObject
{
    Q_OBJECT
public:
    explicit Dataset(QObject *parent = 0);

signals:


public slots:

    static void createRandomData(int numberOfElements, QVector<double> &dataVector); //!< Fills a QVector with data
    static void createStandardNormalDistribution (int numberOfElements, QVector<double> &dataVevtor); //!< fills a referenced data vector with normal distributed data
    static double calculateAndersonDarling(QVector<double> &dataVector);
    static double calculatePvalueForAndersonDarling(double ADvalue);
    static double calculateMean(QVector<double> &dataVector);
    static double calculateSigma(QVector<double> &dataVector);
    static double calculateCDFforNormalDistribution(double value, double mean, double sigma);

    static double calculatePotentialCapability(double lowerLimit, double upperLimit, QVector<double> &dataVector);
    static double calculateCriticalCapabilityForUpperLimit(double upperLimit, QVector<double> &dataVector);
    static double calculateCriticalCapabilityForLowerLimit(double lowerLimit, QVector<double> &dataVector);

    // file handling
    static void writeDataSetToFile(QVector<double>&dataVector);


    // visualisation
    static void calculateBinsForHistogram(QVector<double> &dataVector, double widthOfBins, QVector<double> &bins, QVector<double> &frequencies); //! < calculates the binning. Needs the Vector to bin, the vector with the bins and the frequencies


    //setters

    //getters



private:
/*                                  //this section should no longer be needed
    bool lowerLimitHasBeenSet;
    bool upperLimitHasBeenSet;
    double lowerLimit;
    double upperLimit;
    double capabilityPotential;
    double capabilityCriticalForLowerLimit;
    double capabilityCriticalForUpperLimit;
    double capabilityCritical;
*/


};

#endif // DATASET_H
