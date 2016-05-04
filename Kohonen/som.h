#ifndef SOM_H_
#define SOM_H_

#include "neuron.h"
using namespace std;

class SOM
{
private:
    std::vector< std::vector<Neuron> > neurons;
    int winnerNeuron;
    int numEpochs, numInputs;
    int lastSeason;
    int dimension;
    double acceptableError;
    double eta0;
    double sigma0;
    double tau;
    long double distance;

public:
    SOM(int xDim, int yDim, int _numInputs, int _dimension);
    void trainingConfig(int _numEpochs, double _acceptableError, double _eta0, double _sigma0, double _tau);
    void shortestDistance(std::vector<double>& data);
    double euclidianDistance(int xWinner, int yWinner, int xNeighbor, int yNeighbor);
    void adjustWeights(int index, std::vector<double>& inputData);
    void training(std::vector< std::vector<double> >& inputData);
    void clustering(std::vector< std::vector<double> >& inputData, std::vector<int>& target);
    void operation(std::vector< std::vector<double> >& inputData, std::vector<int>& target);
};

#endif /* SOM_H_ */
