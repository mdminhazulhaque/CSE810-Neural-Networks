#include "hopfield.h"

int Neuron::act(int m, int *x) {
    int i;
    int a = 0;
    for (i = 0; i < m; i++) {
        a += x[i] * w[i];
    }

    return a;
}

Neuron::Neuron(int *j) {
    int i;
    for (i = 0; i < 4; i++) {
        w[i] = *(j+i);
    }
}

int Network::threshold(int k) {
    if ( k >= 0) {
        return 1;
    } else {
        return 0;
    }
}

Network::Network (int a[4], int b[4], int c[4], int d[4]) {
    nrn[0] = Neuron(a);
    nrn[1] = Neuron(b);
    nrn[2] = Neuron(c);
    nrn[3] = Neuron(d);
}

void Network::activation (int *patrn) {
    int i,j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            cout <<"\nnrn[" << i << "].w[" << j << "] = " << nrn[i].w[j];
        }

        nrn[i].activation = nrn[i].act(4,patrn);
        cout << "\nactivation is " << nrn[i].activation;
        output[i] = threshold(nrn[i].activation);
        cout << "\noutput value is " << output[i] << "\n";
    }
}
