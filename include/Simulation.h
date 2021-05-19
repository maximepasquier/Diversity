#ifndef DEF_SIMULATION
#define DEF_SIMULATION

#include <fstream>
#include <vector>
#include "Individu.h"
#include "Agent_Pathogene.h"
#include "AP_linked_list_node.h"
#include "AP_linked_list.h"

/**
 * La classe simulation est le coeur de la simulation et contient
 * toutes les méthodes et attributs nécessaire au déroulement 
 * d'une simulation. Chaque instance de la classe est une
 * simulation.
 */

class Simulation
{
public:
    //* Méthodes du fichier "Simulation.cpp"
    Simulation();
    Simulation(std::string configuration_file_path);
    ~Simulation();
    void Init();
    void Read();
    void Set();
    void Model_init();
    void Mesures();
    void Run();
    void End();
    void Data_structure_creation();
    //* Méthodes du fichier "m_variables.cpp"
    void Assign_variables();
    void Set_Pointer_array();
    void Set_Liste_I();
    void Delete_obj();
    void Pointer_array_to_NULL();
    //* Méthodes du fichier "m_mesures.cpp"
    int Update_nombre_AP_diff();
    void Nombre_de_fois_contamine();
    int Update_infected_number();
    //* Méthodes du fichier "m_file_functions.cpp"
    void File_init_all_data();
    void File_init();
    void Read_Configuration_file();
    void Close_files_all_data();
    void Close_files();
    void Create_and_initialize_csv_all_data();
    void Create_and_initialize_csv();
    void Open_append_mode_csv_all_data();
    void Open_append_mode_csv();
    void Update_csv_all_data(int iteration);
    void Update_csv();
    //* Méthodes du fichier "m_iterations.cpp"
    void Iterations();
    bool Is_immune(int index_I, unsigned int genome_AP);
    bool Is_immune_cell(int x, int y, int index_I);
    void AP_mutation(int index_I);
    void Get_immunity(int index_I);
    void Resistance_naturelle(int index_I);
    void One_iteration(int iteration);
    void Update_all_AP();
    void Update_all_I(int *permuted_liste);
    void Update_one_I(int index_I);
    void Contamination_cases(int coords[4][2] , int x, int y, int index_I);
    void Individu_hote(int index_I);
    void Collision_I_AP(int x, int y, int index_I);
    void Analyse_voisinage(int coords[4][2], int index_I);
    void Mouvement(int coords[4][2], int x, int y);
    void Moving(int coords[4][2], int x, int y, int choix);
    void Add_AP_to_cell(int x, int y);
    void Contaminate_cell(int x, int y);
    void Pointer_move_update(int coords[4][2], int x, int y, int choix);
    int SIR_recovered();
    //* Méthodes du fichier "m_model.cpp"
    void Patient_zero();
    void Add_individu_obj_to_grid();
    void Generate_genome_diversity();
    //* Méthodes du fichier "test.cpp"
    void test_variables_coherence();
    void test_is_Pointer_array_to_null();
    void test_diversity_genome();
    void test_humain_coords_conflits();

private:
    //* Variables issues du fichier config
    int m_TAILLE_SYSTEME;              // largeur de la grille
    int m_NOMBRE_INDIVIDUS;            // nombre de personnes initialement (densité)
    int m_ITERATIONS;                  // nombre d'itérations de la simulation
    unsigned int m_GENOME_INIT_I;      // unsigned char pour le génome humain initial
    int m_GENOME_DIVERSITY_I;          // diversité des génomes humains
    unsigned int m_GENOME_INIT_AP;     // unsigned char pour le génome AP initial
    float m_VITESSE_MUTATIONS_AP;      // définit la vitesse à laquelle les pathogènes mutent
    float m_CHARGE_VIRALE;             // charge virale (niveau de contagion)
    unsigned int m_PARAMETRE_FONCTION; // puissance des termes dans la fonction de génome match
    float m_CELLULE_AP;                // détermine la probabilité de contaminer une cellule
    float m_SURVIE_AP;                 // probabilité que le pathogène contaminant une cellule reste en vie
    int m_NOMBRE_MOUVEMENT;            // nombre de mouvements par itération
    int m_TEMPS_AVANT_IMMUNITE;        // temps minimal pour considérer une immunité et non une résistance naturelle
    bool m_IMMUNITE_MECANISME; 
    bool m_RESISTANCE_MECANISME;

    //* Variables pour les mesures de la simulation
    int m_nombre_contamine; // compteur du nombre d'individus contaminés à chaque itération
    int m_nombre_AP_diff;   // compteur du nombre d'agents pathogènes à chaque itération

    //* Path du fichier config
    std::string m_configuration_file_path;

    //* Variable contentant les données lu du fichier config
    std::vector<std::pair<std::string, std::string>> m_configuration_file_data;

    //* Matrice de pointeurs sur les objets individus et pathogènes
    Individu ***m_Pointer_array_I;
    AP_linked_list_node ***m_Pointer_array_AP;

    //* Liste chaînée contentant les agents pathogènes contaminant les cellules
    AP_linked_list m_Liste_AP;

    //* Liste de pointeurs contenant les objets individus
    Individu **m_Liste_I;

    //* Fichiers csv pour stocker toutes les données de la simulation
    std::ofstream m_Humain_contamine, m_Humain_genomeAP, m_Humain_genomeH, m_Humain_hx, m_Humain_hy, m_Humain_immune, m_times, m_HammingDistance;

    //* Fichier csv pour la prise des données essentielles
    std::ofstream m_nombre_contamine_file, m_nombre_de_fois_contamine_file, m_nombre_AP_diff_file, m_SIR_recovered_file;

    //* Variables pour calculer les temps d'exécution du programme
    unsigned long long int m_Init_time = 0;
    unsigned long long int m_Run_time = 0;
    unsigned long long int m_Mesures_time = 0;
    unsigned long long int m_End_time = 0;
    unsigned long long int m_Total_time = 0;
};

#endif