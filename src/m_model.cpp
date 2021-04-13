#include <iostream>
#include <math.h>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

void Simulation::Patient_zero()
{
    //* Contaminer un humain (patient zéro)
    m_Liste_H[0]->Setcontamine(true);
    m_Liste_H[0]->SetgenomeAP(m_GENOME_INIT_AP);
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