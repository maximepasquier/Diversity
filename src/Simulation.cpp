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

    int rerun_times = m_RERUN_LIMIT;

    //* Rerun la simulation en cas d'échec de la pandémie
    for (int i = 0; i <= m_RERUN_LIMIT; i++)
    {
        m_iteration_fin = -1;

        auto Init_start = chrono::steady_clock::now();
        Init();
        auto Init_end = chrono::steady_clock::now();
        auto Init_diff = Init_end - Init_start;
        m_Init_time = chrono::duration<double, micro>(Init_diff).count();

        auto Run_start = chrono::steady_clock::now();
        Run();
        auto Run_end = chrono::steady_clock::now();
        auto Run_diff = Run_end - Run_start;
        m_Run_time = chrono::duration<double, micro>(Run_diff).count();

        auto Mesures_start = chrono::steady_clock::now();
        Mesures();
        auto Mesures_end = chrono::steady_clock::now();
        auto Mesures_diff = Mesures_end - Mesures_start;
        m_Mesures_time = chrono::duration<double, micro>(Mesures_diff).count();

        auto End_start = chrono::steady_clock::now();
        End();
        auto End_end = chrono::steady_clock::now();
        auto End_diff = End_end - End_start;
        m_End_time = chrono::duration<double, micro>(End_diff).count();

        //* Vérifier que le Run() ait abouti sur un événement
        if (m_iteration_fin > m_FAIL_SEUIL || m_iteration_fin == -1)
        {
            rerun_times = i;
            break;
        }
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    m_Total_time = chrono::duration<double, micro>(diff).count();

    int time_metrique = 1000;

    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");
    m_times.open(path_copy + "/times.csv", std::ios::app);
    m_times << m_Init_time / time_metrique << ','
            << m_Run_time / time_metrique << ','
            << m_Mesures_time / time_metrique << ','
            << m_End_time / time_metrique << ','
            << m_Total_time / time_metrique;
    m_times.close();

    m_rerun.open(path_copy + "/rerun.csv");
    m_rerun << "Nombre de rerun" << '\n'
            << rerun_times;
    m_rerun.close();
}

//* Phase d'initalisation de la simulation
void Simulation::Init()
{
    Read();
    Set();
    File_init();
}

//* Phase d'exécution de la simulation
void Simulation::Run()
{
    Iterations();
}

//* Phase de mesures de la simulation
void Simulation::Mesures()
{
    Nombre_de_fois_contamine();
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