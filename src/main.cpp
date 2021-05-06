#include <iostream>
#include <chrono>
#include <string.h>
#include "Simulation.h"

using namespace std;

//* Initialiser globalement un générateur de nombres aléatoire
//unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
//default_random_engine generator(seed);
default_random_engine generator(123456789);


int main(int argc, char const *argv[])
{
    auto start = chrono::steady_clock::now();

    Simulation Reference("./Simulations/Reference");

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Le temps total est de : " << chrono::duration<double, milli>(diff).count() << " ms" << endl;
    return 0;
}