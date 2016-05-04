#include "som.h"

SOM::SOM(int xDim, int yDim, int _numInputs, int _dimension)
{
    winnerNeuron 		= 0;
    numEpochs 			= 0;
    acceptableError 	= 0.0;
    eta0 = sigma0 = tau = 0.0;
    distance 			= 0.0;
    lastSeason			= 0;

    dimension = _dimension;
    numInputs = _numInputs;
    neurons.resize(xDim);

    for (int x = 0; x < xDim; x++)
    {
        neurons[x].resize(yDim);
    }

    for (unsigned int x = 0; x < neurons.size(); x++)
    {
        for (unsigned int y = 0; y < neurons[x].size(); y++)
        {
            neurons[x][y].init(numInputs, x, y, dimension);
        }
    }
}

void SOM::trainingConfig(int _numEpochs, double _acceptableError, double _eta0, double _sigma0, double _tau)
{
    numEpochs 		= _numEpochs;
    acceptableError = _acceptableError;
    eta0 			= _eta0;
    sigma0 			= _sigma0;
    tau 			= _tau;
}

void SOM::shortestDistance(std::vector<double>& data)
{
    distance = neurons[0][0].euclidianDistance(data);
    winnerNeuron = neurons[0][0].id;

    for (unsigned int x = 0; x < neurons.size(); x++)
    {
        for (unsigned int y = 0; y < neurons[x].size(); y++)
        {
            if(distance > neurons[x][y].euclidianDistance(data))
            {
                distance = neurons[x][y].euclidianDistance(data);
                winnerNeuron = neurons[x][y].id;
            }
        }
    }
}

double SOM::euclidianDistance(int xWinner, int yWinner, int xNeighbor, int yNeighbor)
{
    return( pow(xWinner - xNeighbor, 2) + pow(yWinner - yNeighbor, 2) );
}

void SOM::adjustWeights(int index, std::vector<double>& inputData)
{
    long double sigma;
    long double lateralDistance;
    long double h;
    long double eta;

    int xWinner = winnerNeuron / dimension;
    int yWinner = winnerNeuron % dimension;

    for (unsigned int x = 0; x < neurons.size(); x++)
    {
        for (unsigned int y = 0; y < neurons[x].size(); y++)
        {
            sigma = sigma0 * exp(-index / tau);
            lateralDistance = euclidianDistance(xWinner, yWinner, x, y);
            h = exp( -lateralDistance / (2 * pow(sigma, 2)) );

            eta = eta0 * exp( -index /tau );

            if(eta <= 0.01)
                eta = 0.02;

            for (int w = 0; w < neurons[x][y].numSynapses; w++)
            {
                neurons[x][y].weights[w] += eta * h * (inputData[w] - neurons[x][y].weights[w]);
            }
        }
    }
}

void SOM::training(std::vector< std::vector<double> >& inputData)
{
    for (int epoch = 0; epoch < numEpochs; epoch++)
    {
        for (unsigned int example = 0; example < inputData.size(); example++)
        {
            shortestDistance(inputData[example]);
            int index = ( epoch * inputData.size() ) + example;
            adjustWeights(index, inputData[example]);
        }

        lastSeason++;

        if(distance < acceptableError)
            break;
    }
}

void SOM::clustering(std::vector< std::vector<double> >& inputData, std::vector<int>& target)
{
    int xWinner, yWinner;

    for (unsigned int example = 0; example < inputData.size(); example++)
    {
        shortestDistance(inputData[example]);

        xWinner = winnerNeuron / dimension;
        yWinner = winnerNeuron % dimension;

        neurons[xWinner][yWinner].label = target[example];
    }

    for (unsigned int x = 0; x < neurons.size(); x++)
    {
        for (unsigned int y = 0; y < neurons[x].size(); y++)
        {
            cout << neurons[x][y].label << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void SOM::operation(std::vector< std::vector<double> >& inputData, std::vector<int>& target)
{
    int xWinner, yWinner;
    int hits, errors;

    hits = 0;
    errors = 0;

    for (unsigned int example = 0; example < inputData.size(); example++)
    {
        shortestDistance(inputData[example]);

        xWinner = winnerNeuron / dimension;
        yWinner = winnerNeuron % dimension;

        if(neurons[xWinner][yWinner].label == target[example])
            hits++;
        else
            errors++;

        cout << "Test " << example << ": "
             << "(Actual --> " << neurons[xWinner][yWinner].label << ") | "
             << "(Expected --> " << target[example] << ")" << endl;
    }
    cout << endl << "Hits: " << hits << endl;
    cout << "Errors: " << errors << endl;
}
