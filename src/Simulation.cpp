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

Simulation::Simulation(string configuration_file_path) : m_configuration_file_path(configuration_file_path)
{
    Init();
    Run();
}

Simulation::~Simulation() // déconstructeur
{
}

void Simulation::Init()
{
    Read();
    Set();
    File_init();
}

void Simulation::Run()
{
    Iterations();
    //* Close files
    Close_files();
    Delete_obj();
}

void Simulation::Read()
{
    //* Read from config file
    Read_Configuration_file();
    //* Assignation des paramètres globaux
    Assign_variables();
    //test: vérifier la cohérence des variables globales
    test_variables_coherence();
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
    test_is_Pointer_array_to_null();
}

void Simulation::Model_init()
{
    //* Initaliser des génomes pour les humains
    Generate_human_genome_diversity();
    //test : vérifier la diversité des génomes
    test_diversity_genome();
    //* Ajouter des objets humain
    Add_human_obj_to_grid();
    // test : vérifier que chaque humain ait des coordonnées dans ses attributs + aucun conflit entre les humains
    test_humain_coords_conflits();
    Patient_zero();
}