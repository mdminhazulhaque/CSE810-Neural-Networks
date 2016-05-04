#ifndef HOPFIELD_H
#define HOPFIELD_H

#include <iostream>
using namespace std;

class Neuron
{
public:
    Neuron(int *j);
    Neuron() {}

    int act(int m, int *x);

    int activation;
    int w[4];
};

class Network
{
public:
    Network(int* a, int* b, int* c, int* d);

    int threshold(int k);
    void activation(int *j);

    int output[4];
    Neuron nrn[4];
};

#endif // HOPFIELD_H
