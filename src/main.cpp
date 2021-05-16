#include <iostream>
#include <chrono>
#include <random>
#include "Simulation.h"

//* Initialiser globalement un générateur de nombres aléatoire
//unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
//default_random_engine generator(seed);
std::default_random_engine generator(123456789);


int main(int argc, char const *argv[])
{
    auto start = std::chrono::steady_clock::now();
    //* (string configuration_file_path, bool immunity_and_mutation, bool natural_resistance)

    //* SI
    //Simulation Reference("./Simulations/SI_Reference", false, true);

    //* SIR
    Simulation Reference("./Simulations/SIR_Reference", true, true);

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Le temps total est de : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
    return 0;
}