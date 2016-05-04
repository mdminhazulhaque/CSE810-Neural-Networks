#include "Backpropagation.h"

Backpropagation::Backpropagation()
{
}

Backpropagation::~Backpropagation()
{
}

void Backpropagation::train()
{
    vector<double> hideValue(hidenode, 0.0);
    vector<double> outValue(outnode, 0.0);

    vector<double> inodeOut(hidenode, 0.0);
    vector<double> hidenodeOut(outnode, 0.0);

    vector<double> hiderror(hidenode, 0.0);
    vector<double> allerror;

    vector<vector<double>> allhiderror;

    double e = 0.0;

    vector<vector<double>> hidevalueM;


    vector<vector<double>> wdetaInnode = wInode;
    vector<vector<double>> wdetaHidenode = wHnode;

    for (int i = 0; i < wInode.size(); i++)
    {
        for (int j = 0; j < wInode[0].size(); j++)
            wdetaInnode[i][j] = 0;
    }


    for (int i = 0; i < wHnode.size(); i++)
    {
        for (int j = 0; j < wHnode[0].size(); j++)
            wdetaHidenode[i][j] = 0;
    }


    for (int index = 0; index < train_set.size(); index++)
    {
        for (int i = 0; i < hidenode; i++)
        {
            for (int j = 0; j < innode; j++)
            {
                inodeOut[i] += train_set[index][j] * wInode[j][i];
            }
            hideValue[i] = sigmoid(inodeOut[i]);
        }

        for (int i = 0; i < outnode; i++)
        {
            for (int j = 0; j < hidenode; j++)
            {
                hidenodeOut[i] += hideValue[j] * wHnode[j][i];
            }
            outValue[i] = sigmoid(hidenodeOut[i]);
        }
        hidevalueM.push_back(hideValue);

        double err = (train_set[index][2] - outValue[0]) * (1 - outValue[0]) * outValue[0];

        allerror.push_back(err);

        double er = train_set[index][2] - outValue[0];
        e += fabs(er) * fabs(er);


        for (int i = 0; i < hidenode; i++)
        {
            wdetaHidenode[i][0] += rate * err * hideValue[i];
        }

        for (int i = 0; i < hidenode; i++)
        {
            hiderror[i] = err * wHnode[i][0] * (1 - hideValue[i]) * hideValue[i];
        }
        for (int i = 0; i < innode; i++)
        {
            for (int j = 0; j < hidenode; j++)
            {
                wdetaInnode[i][j] += hiderror[j] * train_set[index][i];
            }
        }
    }

    for (int i = 0; i < wInode.size(); i++)
    {
        for (int j = 0; j < wInode[0].size(); j++)
            wInode[i][j]+=wdetaInnode[i][j];
    }


    for (int i = 0; i < wHnode.size(); i++)
    {
        for (int j = 0; j < wHnode[0].size(); j++)
            wHnode[i][j]+=wdetaHidenode[i][j];
    }

    this->error = e / 8;
}

double Backpropagation::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

void Backpropagation::init(vector<vector<double>> train_set, double error, double rate)
{
    this->train_set = train_set;
    this->error = error;
    this->rate = rate;
    srand(2);

    for (int i = 0; i < innode; i++)
    {
        vector<double> tmp;
        for (int j = 0; j < hidenode; j++)
        {
            tmp.push_back(10.0 * (double)rand() / RAND_MAX - 1);
        }
        wInode.push_back(tmp);
    }

    for (int i = 0; i < hidenode; i++)
    {
        vector<double> tmp;
        for (int j = 0; j < outnode; j++)
        {
            tmp.push_back(2.0 * (double)rand() / RAND_MAX - 1);
        }
        wHnode.push_back(tmp);
    }
}
