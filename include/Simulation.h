#ifndef DEF_SIMULATION
#define DEF_SIMULATION

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
#include "file_functions.h"
#include "test_variables.h"

class Simulation
{
public:
    Simulation();
    Simulation(std::string configuration_file_path);
    ~Simulation();
    void Init(std::string m_configuration_file_path);
    void Read(std::string m_configuration_file_path);
    void Set();
    void File_init();
    void test_variables_coherence2();
    void Data_structure_creation();
    void Model_init();
    void Run();
    void Assign_variables();
    void Set_Pointer_array();
    void Set_Liste_H();
    void Patient_zero();
    void Iterations();
    void Delete_obj();
    void Close_files();
    void Pointer_array_to_NULL();
    void Generate_human_genome_diversity();
    void Add_human_obj_to_grid();
    void Create_and_initialize_csv();
    void Open_append_mode_csv();
    void Update_csv();

protected:
    int m_TAILLE_SYSTEME;          // largeur de la grille
    int m_NOMBRE_PERSONNES;        // nombre de personnes initialement (densité)
    int m_ITERATIONS;              // nombre d'itérations de la simulation
    unsigned int m_GENOME_INIT_H;  // unsigned char pour le génome humain initial
    int m_GENOME_DIVERSITY_H;      // diversité des génomes humains
    unsigned int m_GENOME_INIT_AP; // unsigned char pour le génome AP initial
    float m_VITESSE_MUTATIONS_AP;  // définit la vitesse à laquelle les pathogènes mutent
    float m_CHARGE_VIRALE;         // charge virale (niveau de contagion)
    unsigned int m_PUISSANCE;      // puissance des termes dans la fonction de génome match
    float m_TRAINEE;               // détermine la probabilité de contaminer une cellule
    float m_SURVIE_AP;             // probabilité que le pathogène contaminant une cellule reste en vie
    std::string m_configuration_file_path;
    std::vector<std::pair<std::string, std::string>> m_configuration_file_data;
    Humain ***m_Pointer_array_H;
    node ***m_Pointer_array_AP;
    Linked_list m_Liste_AP;
    std::ofstream m_Humain_contamine, m_Humain_genomeAP, m_Humain_genomeH, m_Humain_hx, m_Humain_hy, m_Humain_immune;
    Humain **m_Liste_H;
};

#endif