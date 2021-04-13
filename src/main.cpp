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
    Simulation Systeme_1("./Simulations/Systeme_1");
    //Simulation Systeme_2("./Simulations/Systeme_2");
    //Simulation Systeme_3("./Simulations/Systeme_3");
    //Simulation Systeme_4("./Simulations/Systeme_4");
    //Simulation Systeme_5("./Simulations/Systeme_5");
    //Simulation Systeme_6("./Simulations/Systeme_6");
    //Simulation Systeme_7("./Simulations/Systeme_7");
    //Simulation Systeme_1("/home/maxime/Documents/UNIGE");
    return 0;
}