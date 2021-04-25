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

    Simulation Charge_virale_moins("./Simulations/Charge_virale_moins");
    Simulation Charge_virale_plus("./Simulations/Charge_virale_plus");
    Simulation Genome_H_AP_opposes("./Simulations/Genome_H_AP_opposes");
    Simulation Genome_H_diversity_moins("./Simulations/Genome_H_diversity_moins");
    Simulation Genome_H_diversity_plus("./Simulations/Genome_H_diversity_plus");
    Simulation Nombre_Personnes_moins("./Simulations/Nombre_Personnes_moins");
    Simulation Nombre_Personnes_plus("./Simulations/Nombre_Personnes_plus");
    Simulation Puissance_moins("./Simulations/Puissance_moins");
    Simulation Puissance_plus("./Simulations/Puissance_plus");
    Simulation Reference("./Simulations/Reference");
    Simulation Survie_AP_moins("./Simulations/Survie_AP_moins");
    Simulation Survie_AP_plus("./Simulations/Survie_AP_plus");
    Simulation Systeme_MAX("./Simulations/Systeme_MAX");
    Simulation Taille_Systeme_moins("./Simulations/Taille_Systeme_moins");
    Simulation Taille_Systeme_plus("./Simulations/Taille_Systeme_plus");
    Simulation Trainee_moins("./Simulations/Trainee_moins");
    Simulation Trainee_plus("./Simulations/Trainee_plus");
    Simulation Vitesse_mutation_moins("./Simulations/Vitesse_mutation_moins");
    Simulation Vitesse_mutation_plus("./Simulations/Vitesse_mutation_plus");    

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Le temps total est de : " << chrono::duration<double, milli>(diff).count() << " ms" << endl;
    return 0;
}