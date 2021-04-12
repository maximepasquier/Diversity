#include <iostream>
#include <chrono>
#include <string.h>
#include "Simulation.h"

using namespace std;

//* Initialiser globalement un générateur de nombres aléatoire
unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);

int main(int argc, char const *argv[])
{
    Simulation Systeme_1("./Configuration/config.txt");
    return 0;
}