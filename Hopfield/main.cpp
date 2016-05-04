#include <iostream>
#include "hopfield.h"

using namespace std;

int main () {
    int patrn1[] = { 1, 0, 1, 0 }, i;
    int wt1[] = { 0, -3, 3, -3 };
    int wt2[] = { -3, 0, -3, 3 };
    int wt3[] = { 3, -3, 0, -3 };
    int wt4[] = { -3, 3, -3, 0 };

    cout << "\nThis program is for a Hopfield network with a single layer of ";
    cout << "\nfully interconnected neurons. THe network should recall the ";
    cout << "\npatterns 1010 and 0101 correctly.\n";

    //create network by calling its constructor.
    //the constructor calls neuron constructor as many times as the number of
    //neurons in the network.
    Network h1(wt1, wt2, wt3, wt4);

    //present a patter to the network and get the activations of the neurons
    h1.activation(patrn1);

    //check if the pattern given is correctly recalled and give message.
    for (i = 0; i < 4; i++) {
        if (h1.output[i] == patrn1[i]) {
            cout << "\npattern = " << patrn1[i] << " output = " << h1.output[i] << " - component matches";
        } else {
            cout << "\npattern = " << patrn1[i] << " output = " << h1.output[i] << " - discrepancy occurred.";
        }
    }

    cout << "\n\n";
    int patrn2[] = { 0, 1, 0, 1 };
    h1.activation(patrn2);

    //check if the pattern given is correctly recalled and give message.
    for (i = 0; i < 4; i++) {
        if (h1.output[i] == patrn2[i]) {
            cout << "\npattern = " << patrn2[i] << " output = " << h1.output[i] << " - component matches";
        } else {
            cout << "\npattern = " << patrn2[i] << " output = " << h1.output[i] << " - discrepancy occurred.";
        }
    }

    return 0;
}
