#ifndef DEF_SIMULATION
#define DEF_SIMULATION

#include <fstream>
#include <vector>
#include <random>
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
    Simulation(std::string configuration_file_path, std::default_random_engine generator);
    ~Simulation();
    void Execution();
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
    int Update_infected_number();
    void Nombre_de_fois_contamine();
    int Update_nombre_AP_diff();
    //* Méthodes du fichier "m_file_functions.cpp"
    void File_init();
    void Read_Configuration_file();
    void Close_files();
    void Create_and_initialize_csv();
    void Open_append_mode_csv();
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
    void Contamination_cases(int coords[][2], int x, int y, int index_I);
    void Pre_contamine_to_contamine();
    void Individu_hote(int index_I);
    void Collision_I_AP(int x, int y, int index_I);
    void Analyse_voisinage(int coords[][2], int index_I);
    void Mouvement(int x, int y);
    void Moving(int coords[][2], int x, int y, int choix);
    void Add_AP_to_cell(int x, int y);
    void Contaminate_cell(int x, int y);
    void Pointer_move_update(int coords[][2], int x, int y, int choix);
    int SIR_recovered();
    //* Méthodes du fichier "m_model.cpp"
    void Patient_zero();
    void Add_individu_obj_to_grid();
    void Generate_genome_diversity();

private:
    //* Générateur de nombres aléatoires
    std::default_random_engine m_generator;

    //* Variables issues du fichier config
    int m_TAILLE_SYSTEME;                     // largeur de la grille
    int m_NOMBRE_INDIVIDUS;                   // nombre de personnes initialement (densité)
    int m_ITERATIONS;                         // nombre d'itérations de la simulation
    unsigned int m_GENOME_INIT_I;             // unsigned char pour le génome humain initial
    int m_GENOME_DIVERSITY_I;                 // diversité des génomes humains
    unsigned int m_GENOME_INIT_AP;            // unsigned char pour le génome AP initial
    float m_VITESSE_MUTATIONS_AP;             // définit la vitesse à laquelle les pathogènes mutent
    float m_CHARGE_VIRALE;                    // charge virale (niveau de contagion)
    unsigned int m_PARAMETRE_FONCTION;        // puissance des termes dans la fonction de génome match
    unsigned int m_PARAMETRE_FONCTION_DOUBLE; // puissance des termes dans la fonction de double génome match
    float m_CELLULE_AP;                       // détermine la probabilité de contaminer une cellule
    float m_SURVIE_AP;                        // probabilité que le pathogène contaminant une cellule reste en vie
    int m_NOMBRE_MOUVEMENT;                   // nombre de mouvements par itération
    int m_TEMPS_AVANT_IMMUNITE;               // temps minimal pour considérer une immunité et non une résistance naturelle
    bool m_IMMUNITE_MECANISME;                // activation ou non du mécanisme d'immunisation
    bool m_RESISTANCE_MECANISME;              // activation ou non du mécanisme de résistance naturelle
    bool m_PERFECT_MIX;                       // mode de mouvement en mélange parfait ou en en nombre de mouvements fixés
    int m_FAIL_SEUIL;                         // seuil au delà duquel on ne restart pas la simulation
    int m_RERUN_LIMIT;                        // nombre maximum de restart de simulation en cas "d'échec"

    //* Variables pour les mesures de la simulation
    int m_nombre_contamine;        // compteur du nombre d'individus contaminés à chaque itération
    int m_nombre_AP_diff;          // compteur du nombre d'agents pathogènes à chaque itération
    int m_iteration_fin;           // nombre d'itération final
    int m_nombre_contamine_max;    // nojmbre maximum de contaminés simultanément
    int m_iteration_max_contamine; // itération du maximum de contaminés maximum
    int m_SIR_recovered;           // nombre d'individus avant au moins une immunité et sain
    int m_nombre_AP_diff_max;      // nombre maximum d'agents pathogènes simultanément

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

    //* Fichier csv pour la prise des données essentielles
    std::ofstream m_nombre_echec_file, m_iteration_fin_simulation_file, m_max_contamines_file, m_iteration_max_contamines_file, m_taille_pandemie_file, m_nombre_de_fois_contamine_file, m_nombre_AP_diff_file;

    //* Variables pour calculer les temps d'exécution du programme
    unsigned long long int m_Init_time = 0;
    unsigned long long int m_Run_time = 0;
    unsigned long long int m_Mesures_time = 0;
    unsigned long long int m_End_time = 0;
    unsigned long long int m_Total_time = 0;

    //* Variable booléenne déterminant l'écher ou le succès d'une simulation
    bool success;
};

#endif