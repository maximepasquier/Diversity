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

using namespace std;

//* Déclaration des paramètres globaux
int TAILLE_SYSTEME;          // largeur de la grille
int NOMBRE_PERSONNES;        // nombre de personnes initialement (densité)
int ITERATIONS;              // nombre d'itérations de la simulation
unsigned int GENOME_INIT_H;  // unsigned char pour le génome humain initial
int GENOME_DIVERSITY_H;      // diversité des génomes humains
unsigned int GENOME_INIT_AP; // unsigned char pour le génome AP initial
float VITESSE_MUTATIONS_AP;  // définit la vitesse à laquelle les pathogènes mutent
float CHARGE_VIRALE;         // charge virale (niveau de contagion)
unsigned int PUISSANCE;      // puissance des termes dans la fonction de génome match
float TRAINEE;               // détermine la probabilité de contaminer une cellule
float SURVIE_AP;             // probabilité que le pathogène contaminant une cellule reste en vie

int main(int argc, char const *argv[])
{
    //* Read from config file
    vector<pair<string, string>> configuration_file_data;
    string configuration_file_path = "./Configuration/config.txt";
    Read_Configuration_file(configuration_file_path, configuration_file_data);

    //* Assignation des paramètres globaux
    Assign_global_variables(configuration_file_data);

    //test: vérifier la cohérence des variables globales
    test_variables_coherence(TAILLE_SYSTEME, NOMBRE_PERSONNES, ITERATIONS, GENOME_INIT_H, GENOME_DIVERSITY_H, GENOME_INIT_AP, VITESSE_MUTATIONS_AP, CHARGE_VIRALE, PUISSANCE, TRAINEE, SURVIE_AP);

    //* Initialiser un générateur de nombres aléatoire
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    //* Générer les distributions et leur portée
    uniform_int_distribution<int> rand_int_taille_systeme(0, TAILLE_SYSTEME - 1); // 0 et TAILLE_SYSTEME inclus
    uniform_int_distribution<int> rand_int_size(0, 31);                           // rand sur la longueur d'un int
    uniform_real_distribution<float> rand_float(0.0, 1.0);                        // rand pour les probabilités

    //* Déclaration des matrices de pointeurs pour les humains
    Humain ***Pointer_array_H = new Humain **[TAILLE_SYSTEME];
    for (int i = 0; i < TAILLE_SYSTEME; i++)
    {
        Pointer_array_H[i] = new Humain *[TAILLE_SYSTEME];
    }
    //* Déclaration des matrices de pointeurs pour les agents pathogènes
    node ***Pointer_array_AP = new node **[TAILLE_SYSTEME];
    for (int i = 0; i < TAILLE_SYSTEME; i++)
    {
        Pointer_array_AP[i] = new node *[TAILLE_SYSTEME];
    }

    //* Déclaration des listes d'objets
    Humain *Liste_H[NOMBRE_PERSONNES];
    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        Liste_H[i] = new Humain;
    }

    //* Création d'une instance de Linked_list
    Linked_list Liste_AP;

    //* Réinitialisation des matrices de pointeurs (NULL)
    Pointer_array_to_NULL(TAILLE_SYSTEME, Pointer_array_H, Pointer_array_AP);

    //test : controle pointer to null
    test_is_Pointer_array_to_null(TAILLE_SYSTEME, Pointer_array_H, Pointer_array_AP);

    //* Initaliser des génomes pour les humains
    Generate_human_genome_diversity(NOMBRE_PERSONNES, GENOME_DIVERSITY_H, GENOME_INIT_H, generator, Liste_H);

    //test : vérifier la diversité des génomes
    test_diversity_genome(Liste_H, NOMBRE_PERSONNES, GENOME_DIVERSITY_H, GENOME_INIT_H);

    //* Ajouter des objets humain
    Add_human_obj_to_grid(NOMBRE_PERSONNES, TAILLE_SYSTEME, Liste_H, Pointer_array_H, generator);

    // test : vérifier que chaque humain ait des coordonnées dans ses attributs + aucun conflit entre les humains
    test_humain_coords_conflits(Liste_H, NOMBRE_PERSONNES);

    //* Contaminer un humain (patient zéro)
    Liste_H[0]->Setcontamine(true);
    Liste_H[0]->SetgenomeAP(GENOME_INIT_AP);

    //* Declarer les fichiers en écriture
    ofstream Humain_contamine, Humain_genomeAP, Humain_genomeH, Humain_hx, Humain_hy, Humain_immune;

    //* Initialiser les fichier .csv
    Create_and_initialize_csv(Humain_contamine, Humain_genomeAP, Humain_genomeH, Humain_hx, Humain_hy, Humain_immune);

    //* Open .csv files to append
    Open_append_mode_csv(Humain_contamine, Humain_genomeAP, Humain_genomeH, Humain_hx, Humain_hy, Humain_immune);

    //* Itérations
    for (int iteration = 0; iteration < ITERATIONS; iteration++)
    {
        //* Print les itérations (avancement)
        Print_progression(iteration, ITERATIONS);

        //* Write to .csv file
        Update_csv(NOMBRE_PERSONNES, Liste_H, Humain_contamine, Humain_genomeAP, Humain_genomeH, Humain_hx, Humain_hy, Humain_immune);

        //* Print ASCII grid to screen
        //Print_ASCII_grid(TAILLE_SYSTEME, Pointer_array_H, Pointer_array_AP);

        //* Construire la permutations de la liste humain
        int *permuted_liste;
        permuted_liste = new int[NOMBRE_PERSONNES];

        for (int i = 0; i < NOMBRE_PERSONNES; i++)
        {
            permuted_liste[i] = i;
        }
        Knuth_Shuffle(permuted_liste, NOMBRE_PERSONNES);

        //* Parcours du domaine (liste agents pathogènes)
        Update_AP(&Liste_AP, Pointer_array_AP, SURVIE_AP, generator);

        //* Parcours du domaine (liste humains)
        for (int i = 0; i < NOMBRE_PERSONNES; i++)
        {
            int index_H = permuted_liste[i];
            int x = Liste_H[index_H]->GetXH();
            int y = Liste_H[index_H]->GetYH();
            vector<pair<int, int>> coordonnees; // vecteur de paire de int
            //* Push les coordonnées des 4 voisins
            Get_coords_voisins(&coordonnees, TAILLE_SYSTEME, x, y);

            //* Déterminer les cas
            if (Liste_H[index_H]->Getcontamine()) //* contaminé
            {
                Humain_hote(index_H, Liste_H, PUISSANCE, VITESSE_MUTATIONS_AP, generator);
            }
            else //* pas contaminé
            {
                //* Un AP se trouve sur la même cellule
                Collision_H_AP(Liste_H, index_H, Pointer_array_AP, x, y, CHARGE_VIRALE, generator);

                //* Analyse du voisinage
                Analyse_voisinage(&coordonnees, Pointer_array_H, Liste_H, index_H, CHARGE_VIRALE, generator);
            }
            //* Mouvements
            //float r = rand_float(generator);
            //cout << "true random : " << r << endl;
            Mouvement(Pointer_array_H, Pointer_array_AP, &Liste_AP, TRAINEE, &coordonnees, x, y, rand_float, generator);
        }
        //* Sleep (FPS)
        this_thread::sleep_for(chrono::seconds(1));
        //* Supprimer la permutation
        delete[] permuted_liste;
    }

    //* Close files
    Close_files(Humain_contamine, Humain_genomeAP, Humain_genomeH, Humain_hx, Humain_hy, Humain_immune);

    //* Supprimer tous les objets humains

    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        delete Liste_H[i];
    }

    for (int i = 0; i < TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j > TAILLE_SYSTEME; j++)
        {
            delete Pointer_array_H[i][j];
            delete Pointer_array_AP[i][j];
        }
    }

    //* Supprimer tous les objets agent_pathogene
    Liste_AP.remove_all();
    return 0;
}