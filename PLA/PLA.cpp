#include <iostream>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

using namespace std;

// generate random number between 0.0 and 0.50
double rand_w()
{
    return (double)(random()%50)/100;
}

int main()
{
    /************ BEG CONFIG ************/

    const double theta = 0.8;
    const int bits =  4;
    //const int cases = pow(2, bits);
    const int cases = 16;
    const int result[cases] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 1,
        1, 1, 1, 1
    };

    /************ END CONFIG ************/

    double w[bits] = {0};
    int row = 0;
    int mat[cases][bits] = {0};

    // convert to binary table
    for(int i=0; i<cases; i++)
    {
        string num = bitset<bits>(i).to_string();

        for(int b=0; b<num.size(); b++)
            mat[i][b] = num[b] - '0';
    }

    // randomize weight
    for(int i=0; i<bits; i++)
        w[i] = rand_w();

    unsigned long int it = 0;

    while(true)
    {
        double sum = 0;

        for(int i=0; i<bits; i++)
        {
            // sum = w(i) * x(i)
            sum += w[i] * mat[row][i];
        }

        printf("row=%2d ", row+1);

        for(int i=0; i<bits; i++)
        {
            printf("w%d=%.3f ", i+1, w[i]);
        }

        printf("sum=%.3f iter=%lu\n", sum, it++);

        int desired = result[row];
        int calculated = (sum >= theta) ? 1 : 0;

        if(calculated == desired)
        {
            // go to next row
            row++;
        }
        else if(calculated == 0 && desired == 1)
        {
            // w(t+1) = w(t) + x(i)
            for(int i=0; i<bits; i++)
                w[i] += mat[row][i];

            // move to index
            row = 0;
        }
        else if(calculated == 1 && desired == 0)
        {
            // w(t+1) = w(t) - x(i)
            for(int i=0; i<bits; i++)
                w[i] -= mat[row][i];
            // move to index
            row = 0;
        }

        // found last stable weight
        if(row==cases-1)
        {
            cout << "Found solution" << endl;
            break;
        }

        //usleep(100000);
    }

    return 0;
}
