#include <chrono>
#include <random>
#include "Individu.h"
#include "Agent_Pathogene.h"
#include "AP_linked_list_node.h"
#include "AP_linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

Simulation::Simulation()
{
}

Simulation::Simulation(string configuration_file_path) : m_configuration_file_path(configuration_file_path), m_nombre_contamine(0)
{
    int time_metrique = 1000000;

    auto start = chrono::steady_clock::now();

    auto Init_start = chrono::steady_clock::now();
    Init();
    auto Init_end = chrono::steady_clock::now();
    auto Init_diff = Init_end - Init_start;
    m_Init_time = chrono::duration<double, nano>(Init_diff).count();

    auto Run_start = chrono::steady_clock::now();
    Run();
    auto Run_end = chrono::steady_clock::now();
    auto Run_diff = Run_end - Run_start;
    m_Run_time = chrono::duration<double, nano>(Run_diff).count();

    Mesures();

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    m_Total_time = chrono::duration<double, nano>(diff).count();

    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");
    m_times.open(path_copy + "/times.csv", std::ios::app);
    m_times << m_Init_time / time_metrique << ',' << m_Run_time / time_metrique << ',' << m_Iterations_time / time_metrique << ',' << m_Update_csv_time / time_metrique << ',' << m_Permutations_time / time_metrique << ',' << m_Update_AP_time / time_metrique << ',' << m_Update_H_time / time_metrique << ',' << m_Coords_time / time_metrique << ',' << m_Contamination_cases_time / time_metrique << ',' << m_Mouvement_time / time_metrique << ',' << m_Total_time / time_metrique;
    m_times.close();
}

Simulation::~Simulation() // déconstructeur
{
}

void Simulation::Init()
{
    Read();
    Set();
    //File_init_all_data();
    File_init();
}

void Simulation::Run()
{
    auto Iterations_start = chrono::steady_clock::now();
    Iterations();
    auto Iterations_end = chrono::steady_clock::now();
    auto Iterations_diff = Iterations_end - Iterations_start;
    m_Iterations_time = chrono::duration<double, nano>(Iterations_diff).count();
}

void Simulation::Mesures()
{
    Nombre_de_fois_contamine();
    //Close_files_all_data();
    Close_files();
    Delete_obj();
}

void Simulation::Read()
{
    //* Read from config file
    Read_Configuration_file();
    //* Assignation des paramètres globaux
    Assign_variables();
}

void Simulation::Set()
{
    Data_structure_creation();
    Model_init();
}

void Simulation::Data_structure_creation()
{
    Set_Pointer_array();
    Set_Liste_H();
    //* Réinitialisation des matrices de pointeurs (NULL)
    Pointer_array_to_NULL();
}

void Simulation::Model_init()
{
    //* Initaliser des génomes pour les humains
    Generate_human_genome_diversity();
    //* Ajouter des objets humain
    Add_human_obj_to_grid();
    Patient_zero();
}