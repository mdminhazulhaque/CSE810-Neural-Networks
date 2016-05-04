#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include <vector>
#include <math.h>
#include <ctime>
#include <iostream>

using namespace std;

class Backpropagation
{
public:
    vector<vector<double>> wInode;
    vector<vector<double>> wHnode;
    vector<vector<double>> train_set;
    double rate = 0.5;
    double error = 0.1;
    double target = 1.0;
    int innode = 2;
    int outnode = 1;
    int hidenode = 2;

public:
    Backpropagation();
    ~Backpropagation();
    void init(vector<vector<double>> train_set, double error, double rate);
    void train();
    double test(vector<double> test_set);

private:
    double sigmoid(double x);
    vector<vector<double>> initial_weight;
    double first_batch_error;
    vector < vector<double>> final_weight;
    double final_error;
    int number_of_batch;


};

#endif //BACKPROPAGATION_H
