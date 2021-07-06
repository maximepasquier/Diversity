#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include <mutex>
#include "Individu.h"
#include "Agent_Pathogene.h"
#include "AP_linked_list.h"
#include "Simulation.h"

using namespace std;

extern std::vector<std::mutex> verrous;

Simulation::Simulation()
{
}

Simulation::Simulation(string configuration_file_path, std::default_random_engine generator) : m_configuration_file_path(configuration_file_path), m_nombre_contamine(0), m_generator(generator)
{
    //* Attente active
    while (1)
    {
        for (auto &v : verrous)
        {
            if (v.try_lock()) // lock disponible
            {
                Execution();
                v.unlock();
                return;
            }
        }
        this_thread::sleep_for(chrono::seconds(10));
    }
}

Simulation::~Simulation() // déconstructeur
{
}

void Simulation::Execution()
{
    auto start = chrono::steady_clock::now();

    //* Read config file + assign
    Read();
    //* Init csv files
    File_init();

    int nombre_echecs = 0;

    for (int nb = 0; nb < 100; nb++)
    {
        m_nombre_contamine_max = 0;
        cout << nb << endl;
        Init();
        Run();
        End();

        //* Récupérer les résultats de la simulation
        if (!success) // seulement si la simulation échoue
        {
            nombre_echecs++;
            m_max_contamines_file << '\n'
                                  << m_nombre_contamine_max;
            m_iteration_max_contamines_file << '\n'
                                            << m_iteration_max_contamine;
            m_iteration_fin_simulation_file << '\n'
                                            << m_iteration_fin;
        }
    }

    //* Compoter le nombre total d'échecs
    m_nombre_echec_file << '\n'
                        << nombre_echecs;

    //* Fermer les fichiers csv
    Close_files();

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    m_Total_time = chrono::duration<double, micro>(diff).count();
}

//* Phase d'initalisation de la simulation
void Simulation::Init()
{
    Set();
}

//* Phase d'exécution de la simulation
void Simulation::Run()
{
    Iterations();
}

//* Phase de terminaison de la simulation
void Simulation::End()
{
    Delete_obj();
}

//* Lecture des données de la simulation
void Simulation::Read()
{
    //* Read from config file
    Read_Configuration_file();
    //* Assignation des paramètres globaux
    Assign_variables();
}

//* Structure de la simulation
void Simulation::Set()
{
    Data_structure_creation();
    Model_init();
}

//* Création des structures de données
void Simulation::Data_structure_creation()
{
    Set_Pointer_array();
    Set_Liste_I();
    //* Réinitialisation des matrices de pointeurs (NULL)
    Pointer_array_to_NULL();
}

//* Initialisation du modèle
void Simulation::Model_init()
{
    //* Initaliser des génomes pour les humains
    Generate_genome_diversity();
    //* Ajouter des objets humain
    Add_individu_obj_to_grid();
    //* Contaminer le premier individu
    Patient_zero();
}