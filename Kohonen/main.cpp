#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include "som.h"

using namespace std;

void fileInput(const char dataset[], std::vector< std::vector<double> >& data, std::vector<int>& target);

int main()
{
    int numEpochs			= 2500;
    double acceptableError 	= 0.001;
    double eta0 			= 0.2;
    double sigma0 			= 0.8;
    double tau 				= 100000;

    std::vector< std::vector<double> > trainingData;
    std::vector<int> trainingTarget;

    std::vector< std::vector<double> > validationData;
    std::vector<int> validationTarget;

    fileInput("/media/data/dev/qt/NN/Kohonen/iris.data", trainingData, trainingTarget);

    cout << endl << "Processing..." << endl << endl;

    int xDim = 5;
    int yDim = 6;
    int nInput = trainingData[0].size();
    int dimension;

    dimension = xDim;
    if(yDim > xDim)
        dimension = yDim;

    SOM som(xDim, yDim, nInput, dimension);

    som.trainingConfig(numEpochs, acceptableError, eta0, sigma0, tau);
    som.training(trainingData);
    som.clustering(trainingData, trainingTarget);

    fileInput("/media/data/dev/qt/NN/Kohonen/iris.test", validationData, validationTarget);

    som.operation(validationData, validationTarget);

    return 0;
}

void fileInput(const char dataset[], std::vector< std::vector<double> >& data, std::vector<int>& target)
{
    int numExamples, numInputs, numTargets;
    const int TITLE_LENGHT = 100;
    char title[TITLE_LENGHT];

    ifstream inFile(dataset, ios::in);

    if(!inFile)
    {
        cerr << "Cannot load file" << endl;
        exit(1);
    }

    inFile.getline(title, TITLE_LENGHT, '\n');

    inFile >> numExamples;
    inFile >> numInputs;
    inFile >> numTargets;

    data.resize(numExamples);
    target.resize(numExamples);

    for (int i = 0; i < numExamples; i++)
    {
        data[i].resize(numInputs);
    }

    for (unsigned int i = 0; i < data.size(); i++)
    {
        for (unsigned int j = 0; j < data[i].size(); j++)
        {
            inFile >> data[i][j];
        }

        inFile >> target[i];
    }

    inFile.close();
}
