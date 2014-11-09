#include "dataset.h"


#define ARC4RANDOM_MAX 0x100000000


Dataset::Dataset(QObject *parent) :
    QObject(parent)
{
   // upperLimit = 0.0;
    //lowerLimit = 0.0;
    //lowerLimitHasBeenSet = false;
    //upperLimitHasBeenSet = false;


}


void Dataset::createRandomData(int numberOfElements, QVector<double> &dataVector){
    qsrand(QTime::currentTime().msec());
    int randomNumber;
    for (int i = 0; i< numberOfElements; i++)
    {
        randomNumber = qrand();
        dataVector.append(randomNumber);

    }
}


void Dataset::createStandardNormalDistribution(int numberOfElements, QVector<double>&dataVector){
        for (int i = 0 ; i < numberOfElements ; i++){
            double x1, x2, w, y1, y2;

            do{
                x1 = 2.0 * ((double)arc4random() / ARC4RANDOM_MAX) - 1.0;
                x2 = 2.0 * ((double)arc4random() / ARC4RANDOM_MAX) - 1.0;
                w = x1 * x1 + x2*x2;
            } while (w>=1.0);

            w = sqrt((-2.0 * log(w))/w);
            y1 = x1 * w;
            y2 = x2 * w;

            dataVector.append(y1);
            // dataVector.append(y2); // we throw this one away, eventhough we could use it... optimize code here later
        }

        //qDebug() << dataVector;
    }


double Dataset::calculateAndersonDarling(QVector<double> &dataVector){
        QVector<double> sortedVector = dataVector;
        qSort(sortedVector.begin(), sortedVector.end());
        //qDebug() << "sorted test vector: " << sortedVector;

        double mean = calculateMean(dataVector);
        double sigma = calculateSigma(dataVector);

        double sum = 0.0;

        double CDF1 = 0.0;
        double CDF2 = 0.0;
        double value1 = 0.0;
        double value2 = 0.0;

        int n = sortedVector.size();

        for (int i = 1 ; i <= n  ; i++){
            value1 = sortedVector.at(i-1);
            //qDebug() << i ;
            value2 = sortedVector.at(n-i);

            CDF1 = calculateCDFforNormalDistribution(value1, mean, sigma);
            CDF2 = 1-calculateCDFforNormalDistribution(value2, mean, sigma);

            sum = sum + (2*i-1)*(log(CDF1)+log(CDF2));
        }

        double AD = -n - (1.0/n) * sum;
        //qDebug() << AD;
        return AD;

    }

double Dataset::calculatePvalueForAndersonDarling(double ADvalue){			// for large n only; the intervalls may be not completely right...
        double pValue = 0.0;
        if (ADvalue > 0.6) {
            pValue = exp(1.2937 - 5.709*(ADvalue) + 0.0186 * ADvalue * ADvalue);
        }
        if (ADvalue <= 0.6 && ADvalue > 0.34){
            pValue = exp(0.9177 - 4.279 * ADvalue - 1.38 * ADvalue * ADvalue);
        }
        if (ADvalue <= 0.34 && ADvalue > 0.2){
            pValue = 1 - exp(-8.318 + 42.796 * ADvalue - 59.938 * ADvalue * ADvalue);
        }
        if (ADvalue <= 0.2){
            pValue = 1- exp(-13.436 + 101.14 * ADvalue - 223.73 * ADvalue * ADvalue);
        }
        return pValue;
    }

double Dataset::calculateMean(QVector<double> &dataVector){
        int n = dataVector.size();
        double sum = 0.0;

        for (int i = 0 ; i < dataVector.size(); i++){
            sum += dataVector.at(i);
        }
        double mean;
        mean = sum/n;
        //qDebug() << "Mean is: " << mean;
        return mean;
    }

double Dataset::calculateSigma(QVector<double> &dataVector){
        double sigma = 0.0;
        int n = dataVector.size();
        double mean = calculateMean(dataVector);
        double error = 0.0;


        for (int index = 0 ; index < n ; index++){
            error = error + (dataVector.at(index) - mean) * (dataVector.at(index) - mean);

        }

        sigma = sqrt(error / n);
        //qDebug() << "Sigma: " << sigma;
        return sigma;
    }

    double Dataset::calculateCDFforNormalDistribution(double value, double mean, double sigma){
        return 0.5 * (1+ erf((value-mean)/(sigma * sqrt (2.0))));
    }




double  Dataset::calculatePotentialCapability(double lowerLimit, double upperLimit, QVector<double> &dataVector){

    double capabilityPotential = (upperLimit - lowerLimit)/(6*calculateSigma(dataVector));

    return capabilityPotential;
}


double Dataset::calculateCriticalCapabilityForUpperLimit(double upperLimit, QVector<double>&dataVector){
    double capabilityCriticalForUpperLimit = (upperLimit - calculateMean(dataVector))/(3*calculateSigma(dataVector));
    return capabilityCriticalForUpperLimit;
}

double Dataset::calculateCriticalCapabilityForLowerLimit(double lowerLimit, QVector<double> &dataVector){
    double capabilityCriticalForLowerLimit = (calculateMean(dataVector) - lowerLimit)/(3*calculateSigma(dataVector));

    return capabilityCriticalForLowerLimit;
}




void Dataset::writeDataSetToFile(QVector<double> &dataVector){
    QString filename = "~/Desktop/test/data.txt";       // need to know how to include the ~into the string
    // QString filename = QStandardPaths::HomeLocation;
    qDebug() << "Filename: " << filename;
    QFile file(filename);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream (&file);
        //stream << "1" << endl << "9" << endl << "15"<< endl;
        for (int i = 0 ; i < dataVector.size() ; i ++)
        {
            double value = dataVector.value(i);
            QString element = QString::number(value);
            stream << element << endl;
        }
    }
    file.close();

}
