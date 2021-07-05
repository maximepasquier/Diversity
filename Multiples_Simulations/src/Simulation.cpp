#include <chrono>
#include <random>
#include <thread>
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

    for (int nb = 0; nb < 1000; nb++)
    {
        //* Rerun la simulation en cas d'échec de la pandémie
        for (int i = 0; i <= m_RERUN_LIMIT; i++)
        {
            Init();
            Run();
            End();
        }
    }

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
    Close_files();
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