#ifndef NEURON_H_
#define NEURON_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>

class Neuron
{
public:
    int id;
    int label;
    int numSynapses;
    std::vector<double> weights;

    Neuron();
    void init(int _numSynapses, int x, int y, int dimension);
    void weightsInit();
    double euclidianDistance(std::vector<double>& input);
};

#endif /* NEURON_H_ */
