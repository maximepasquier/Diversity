#include <iostream>
#include <chrono>
#include <string.h>
#include <sstream>
#include <thread>
#include <fstream>
#include <random>
#include <bitset>
#include <vector>
#include "Humain.h"
#include "Agent_Pathogene.h"
#include "node.h"
#include "Linked_list.h"
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
    /*
    cout << m_Init_time / time_metrique << endl;
    cout << m_Run_time / time_metrique << endl;
    cout << m_Iterations_time / time_metrique << endl;
    cout << m_Update_csv_time / time_metrique << endl;
    cout << m_Permutations_time / time_metrique << endl;
    cout << m_Update_AP_time / time_metrique << endl;
    cout << m_Update_H_time / time_metrique << endl;
    cout << m_Coords_time / time_metrique << endl;
    cout << m_Contamination_cases_time / time_metrique << endl;
    cout << m_Mouvement_time / time_metrique << endl;
    cout << m_Total_time / time_metrique << endl;
    */

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

    /*
    cout << "m_Init_time : " << m_Init_time / time_metrique << endl;
    cout << "m_Run_time : " << m_Run_time / time_metrique << endl;
    cout << "m_Iterations_time : " << m_Iterations_time / time_metrique << endl;
    cout << "m_Update_csv_time : " << m_Update_csv_time / time_metrique << endl;
    cout << "m_Permutations_time : " << m_Permutations_time / time_metrique << endl;
    cout << "m_Update_AP_time : " << m_Update_AP_time / time_metrique << endl;
    cout << "m_Update_H_time : " << m_Update_H_time / time_metrique << endl;
    cout << "m_Coords_time : " << m_Coords_time / time_metrique << endl;
    cout << "m_Contamination_cases_time : " << m_Contamination_cases_time / time_metrique << endl;
    cout << "m_Mouvement_time : " << m_Mouvement_time / time_metrique << endl;
    cout << "m_Total_time : " << m_Total_time / time_metrique << endl;
    */
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
    //cout << "Lecture des paramètres..." << endl;
    Read();
    //cout << "Initialisation du modèle..." << endl;
    Set();
    //cout << "Initialisation des fichier csv" << endl;
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
    //cout << "Fermeture des fichiers csv..." << endl;
    //Close_files_all_data();
    Close_files();
    //cout << "Libération de la mémoire..." << endl;
    Delete_obj();
}

void Simulation::Read()
{
    //* Read from config file
    Read_Configuration_file();
    //* Assignation des paramètres globaux
    Assign_variables();
    //test: vérifier la cohérence des variables globales
    //test_variables_coherence();
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
    //test : controle pointer to null
    //test_is_Pointer_array_to_null();
}

void Simulation::Model_init()
{
    //* Initaliser des génomes pour les humains
    Generate_human_genome_diversity();
    // test : vérifier la diversité des génomes
    //test_diversity_genome();
    //* Ajouter des objets humain
    Add_human_obj_to_grid();
    // test : vérifier que chaque humain ait des coordonnées dans ses attributs + aucun conflit entre les humains
    //test_humain_coords_conflits();
    Patient_zero();
}