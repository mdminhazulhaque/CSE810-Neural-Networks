#include <iostream>
#include <iomanip>
#include "Backpropagation.h"

#define endl '\n'

void print(vector < vector<double> >w)
{
    for (int i = 0; i < w.size(); i++)
    {
        for (int j = 0; j < w[0].size(); j++)
            std::cout << w[i][j] << " ";
        std::cout << endl;
    }
}

int main()
{
    double rate = 0.8;
    double error = 0.01;

    vector<vector<double>> train_set =
    {
        {0,0,0},
        {0,1,1},
        {1,0,1},
        {1,1,0}
    };

    Backpropagation bp;
    bp.init(train_set, 0.1, rate);
    int i = 0;
    double first_error = 0.0;
    double final_error = 0.0;
    int number_of_batch;
    vector<vector<double>> initIW = bp.wInode;
    vector<vector<double>> initHW = bp.wHnode;
    vector<vector<double>> finalIW;
    vector<vector<double>> finalHW;
    while(true)
    {
        i++;

        bp.train();
        if (i == 1)
            first_error = bp.error;
        //std::cout << bp.error << endl;

        if (i % 10000 == 0)
            std::cout << fixed << setprecision(10) << bp.error<<endl;
        if (bp.error < error)
        {
            //std::cout << bp.error<<endl;
            final_error = bp.error;
            number_of_batch = i;
            break;
        }
    }

    std::cout << "initial input node weight" << endl;
    print(initIW);
    std::cout << "initial hide node weight" << endl;
    print(initHW);
    std::cout << "first-batch error: " << first_error << endl;
    std::cout << "final input node weight" << endl;
    print(bp.wInode);
    std::cout << "final hide node weight" << endl;
    print(bp.wHnode);
    std::cout << "final error: " << final_error << endl;
    std::cout << "total number of batches: " << number_of_batch << endl;


}
