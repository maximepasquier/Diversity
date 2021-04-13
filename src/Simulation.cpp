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
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

Simulation::Simulation()
{
}

Simulation::Simulation(string m_configuration_file_path)
{
    Init(m_configuration_file_path);
    Run();
}

Simulation::~Simulation() // déconstructeur
{
}

void Simulation::Init(string m_configuration_file_path)
{
    Read(m_configuration_file_path);
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

void Simulation::Close_files()
{
    m_Humain_contamine.close();
    m_Humain_genomeAP.close();
    m_Humain_genomeH.close();
    m_Humain_hx.close();
    m_Humain_hy.close();
    m_Humain_immune.close();
}

void Simulation::Read(string m_configuration_file_path)
{
    //* Read from config file
    Read_Configuration_file(m_configuration_file_path, m_configuration_file_data);
    //* Assignation des paramètres globaux
    Assign_variables();
    //test: vérifier la cohérence des variables globales
    //test_variables_coherence(m_TAILLE_SYSTEME, m_NOMBRE_PERSONNES, m_ITERATIONS, m_GENOME_INIT_H, m_GENOME_DIVERSITY_H, m_GENOME_INIT_AP, m_VITESSE_MUTATIONS_AP, m_CHARGE_VIRALE, m_PUISSANCE, m_TRAINEE, m_SURVIE_AP);
    test_variables_coherence2();
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
    //test_is_Pointer_array_to_null(m_TAILLE_SYSTEME, m_Pointer_array_H, m_Pointer_array_AP);
}

void Simulation::Pointer_array_to_NULL()
{
    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j < m_TAILLE_SYSTEME; j++)
        {
            m_Pointer_array_H[i][j] = NULL;
            m_Pointer_array_AP[i][j] = NULL;
        }
    }
}

void Simulation::Model_init()
{
    //* Initaliser des génomes pour les humains
    Generate_human_genome_diversity();
    //test : vérifier la diversité des génomes
    test_diversity_genome(m_Liste_H, m_NOMBRE_PERSONNES, m_GENOME_DIVERSITY_H, m_GENOME_INIT_H);
    //* Ajouter des objets humain
    Add_human_obj_to_grid();
    // test : vérifier que chaque humain ait des coordonnées dans ses attributs + aucun conflit entre les humains
    test_humain_coords_conflits(m_Liste_H, m_NOMBRE_PERSONNES);
    Patient_zero();
}

void Simulation::Add_human_obj_to_grid()
{
    uniform_int_distribution<int> rand_int_taille_systeme(0, m_TAILLE_SYSTEME - 1);
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        //* Générer les indices [i][j] de la matrice de pointeurs
        while (1)
        {
            int ligne, colonne;
            ligne = rand_int_taille_systeme(generator);
            colonne = rand_int_taille_systeme(generator);
            //* Assigner un pointeur à chaque humain
            if (m_Pointer_array_H[ligne][colonne] == NULL) // pointeur libre
            {
                m_Pointer_array_H[ligne][colonne] = m_Liste_H[i]; // assignation faite
                //* Enregistrer les coordonnées de l'humain dans ses attributs
                m_Liste_H[i]->SetXH(ligne);
                m_Liste_H[i]->SetYH(colonne);
                break;
            }
        }
    }
}

void Simulation::Generate_human_genome_diversity()
{
    uniform_int_distribution<int> rand_int_size(0, 31);
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        //* Initaliser des génomes pour les humains
        int rand_int_list_octet[m_GENOME_DIVERSITY_H]; // indices des génomes à complémenter
        for (int j = 0; j < m_GENOME_DIVERSITY_H; j++)
        {
            rand_int_list_octet[j] = rand_int_size(generator); // générer aléatoirement des indices
        }
        m_Liste_H[i]->SetgenomeH(Generate_Genome(m_GENOME_DIVERSITY_H, m_GENOME_INIT_H, rand_int_list_octet));
    }
}

void Simulation::File_init()
{
    //* Initialiser les fichier .csv
    Create_and_initialize_csv();
    //* Open .csv files to append
    Open_append_mode_csv();
}

void Simulation::Open_append_mode_csv()
{
    m_Humain_contamine.open("./data/Humain_contamine.csv", std::ios::app);
    m_Humain_genomeAP.open("./data/Humain_genomeAP.csv", std::ios::app);
    m_Humain_genomeH.open("./data/Humain_genomeH.csv", std::ios::app);
    m_Humain_hx.open("./data/Humain_hx.csv", std::ios::app);
    m_Humain_hy.open("./data/Humain_hy.csv", std::ios::app);
    m_Humain_immune.open("./data/Humain_immune.csv", std::ios::app);
}

void Simulation::Create_and_initialize_csv()
{
    m_Humain_contamine.open("./data/Humain_contamine.csv");
    m_Humain_genomeAP.open("./data/Humain_genomeAP.csv");
    m_Humain_genomeH.open("./data/Humain_genomeH.csv");
    m_Humain_hx.open("./data/Humain_hx.csv");
    m_Humain_hy.open("./data/Humain_hy.csv");
    m_Humain_immune.open("./data/Humain_immune.csv");

    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        m_Humain_contamine << "Humain_" << i << ',';
        m_Humain_genomeAP << "Humain_" << i << ',';
        m_Humain_genomeH << "Humain_" << i << ',';
        m_Humain_hx << "Humain_" << i << ',';
        m_Humain_hy << "Humain_" << i << ',';
        m_Humain_immune << "Humain_" << i << ',';
    }
    m_Humain_contamine << '\n';
    m_Humain_genomeAP << '\n';
    m_Humain_genomeH << '\n';
    m_Humain_hx << '\n';
    m_Humain_hy << '\n';
    m_Humain_immune << '\n';

    m_Humain_contamine.close();
    m_Humain_genomeAP.close();
    m_Humain_genomeH.close();
    m_Humain_hx.close();
    m_Humain_hy.close();
    m_Humain_immune.close();
}

void Simulation::Delete_obj()
{
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        delete m_Liste_H[i];
    }

    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j > m_TAILLE_SYSTEME; j++)
        {
            delete m_Pointer_array_H[i][j];
            delete m_Pointer_array_AP[i][j];
        }
    }

    //* Supprimer tous les objets agent_pathogene
    m_Liste_AP.remove_all();
}

void Simulation::Update_csv()
{
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        m_Humain_contamine << m_Liste_H[i]->Getcontamine() << ',';
        m_Humain_genomeAP << m_Liste_H[i]->GetgenomeAP() << ',';
        m_Humain_genomeH << m_Liste_H[i]->GetgenomeH() << ',';
        m_Humain_hx << m_Liste_H[i]->GetXH() << ',';
        m_Humain_hy << m_Liste_H[i]->GetYH() << ',';
        vector<unsigned int> liste_immunite = m_Liste_H[i]->Getimmune();
        int vsize = m_Liste_H[i]->Getimmune().size();
        for (int j = 0; j < vsize; j++)
        {
            m_Humain_immune << liste_immunite[j] << ' ';
        }
        m_Humain_immune << ',';
    }
    m_Humain_contamine << '\n';
    m_Humain_genomeAP << '\n';
    m_Humain_genomeH << '\n';
    m_Humain_hx << '\n';
    m_Humain_hy << '\n';
    m_Humain_immune << '\n';
}

void Simulation::Iterations()
{
    for (int iteration = 0; iteration < m_ITERATIONS; iteration++)
    {
        //* Print les itérations (avancement)
        //Print_progression(iteration, ITERATIONS);

        //* Write to .csv file
        Update_csv();

        //* Print ASCII grid to screen
        Print_ASCII_grid(m_TAILLE_SYSTEME, m_Pointer_array_H, m_Pointer_array_AP);

        //* Construire la permutations de la liste humain
        int *permuted_liste;
        permuted_liste = new int[m_NOMBRE_PERSONNES];

        for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
        {
            permuted_liste[i] = i;
        }
        Knuth_Shuffle(permuted_liste, m_NOMBRE_PERSONNES);

        //* Parcours du domaine (liste agents pathogènes)
        Update_AP(&m_Liste_AP, m_Pointer_array_AP, m_SURVIE_AP);

        //* Parcours du domaine (liste humains)
        for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
        {
            int index_H = permuted_liste[i];
            int x = m_Liste_H[index_H]->GetXH();
            int y = m_Liste_H[index_H]->GetYH();
            vector<pair<int, int>> coordonnees; // vecteur de paire de int
            //* Push les coordonnées des 4 voisins
            Get_coords_voisins(&coordonnees, m_TAILLE_SYSTEME, x, y);

            //* Déterminer les cas
            if (m_Liste_H[index_H]->Getcontamine()) //* contaminé
            {
                Humain_hote(index_H, m_Liste_H, m_PUISSANCE, m_VITESSE_MUTATIONS_AP);
            }
            else //* pas contaminé
            {
                //* Un AP se trouve sur la même cellule
                Collision_H_AP(m_Liste_H, index_H, m_Pointer_array_AP, x, y, m_CHARGE_VIRALE);

                //* Analyse du voisinage
                Analyse_voisinage(&coordonnees, m_Pointer_array_H, m_Liste_H, index_H, m_CHARGE_VIRALE);
            }
            //* Mouvements
            Mouvement(m_Pointer_array_H, m_Pointer_array_AP, &m_Liste_AP, m_TRAINEE, &coordonnees, x, y);
        }
        //* Sleep (FPS)
        this_thread::sleep_for(chrono::seconds(1));
        //* Supprimer la permutation
        delete[] permuted_liste;
    }
}

void Simulation::Patient_zero()
{
    //* Contaminer un humain (patient zéro)
    m_Liste_H[0]->Setcontamine(true);
    m_Liste_H[0]->SetgenomeAP(m_GENOME_INIT_AP);
}

void Simulation::Set_Pointer_array()
{
    //* Déclaration des matrices de pointeurs pour les humains
    m_Pointer_array_H = new Humain **[m_TAILLE_SYSTEME];
    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        m_Pointer_array_H[i] = new Humain *[m_TAILLE_SYSTEME];
    }
    //* Déclaration des matrices de pointeurs pour les agents pathogènes
    m_Pointer_array_AP = new node **[m_TAILLE_SYSTEME];
    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        m_Pointer_array_AP[i] = new node *[m_TAILLE_SYSTEME];
    }
}

void Simulation::Set_Liste_H()
{
    m_Liste_H = new Humain *[m_NOMBRE_PERSONNES];
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        m_Liste_H[i] = new Humain;
    }
}

void Simulation::Assign_variables()
{
    for (int i = 0; i < m_configuration_file_data.size(); i++)
    {
        string key = m_configuration_file_data.at(i).first;
        string value = m_configuration_file_data.at(i).second;
        if (key == "TAILLE_SYSTEME")
        {
            m_TAILLE_SYSTEME = stoi(value);
        }
        else if (key == "NOMBRE_PERSONNES")
        {
            m_NOMBRE_PERSONNES = stoi(value);
        }
        else if (key == "ITERATIONS")
        {
            m_ITERATIONS = stoi(value);
        }
        else if (key == "GENOME_INIT_H")
        {
            m_GENOME_INIT_H = stoul(value);
        }
        else if (key == "GENOME_DIVERSITY_H")
        {
            m_GENOME_DIVERSITY_H = stoi(value);
        }
        else if (key == "GENOME_INIT_AP")
        {
            m_GENOME_INIT_AP = stoul(value);
        }
        else if (key == "VITESSE_MUTATIONS_AP")
        {
            m_VITESSE_MUTATIONS_AP = stof(value);
        }
        else if (key == "CHARGE_VIRALE")
        {
            m_CHARGE_VIRALE = stof(value);
        }
        else if (key == "PUISSANCE")
        {
            m_PUISSANCE = stoul(value);
        }
        else if (key == "TRAINEE")
        {
            m_TRAINEE = stof(value);
        }
        else if (key == "SURVIE_AP")
        {
            m_SURVIE_AP = stof(value);
        }
    }
}
