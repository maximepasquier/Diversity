#include <random>
#include <iostream>
#include "Individu.h"
#include "AP_linked_list_node.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

//* Contamination du premier individu
void Simulation::Patient_zero()
{
    //* Contaminer un humain (patient zéro)
    int index_I = 0;
    m_Liste_I[index_I]->Setcontamine(true);
    m_Liste_I[index_I]->SetgenomeAP(m_GENOME_INIT_AP);
    m_Liste_I[index_I]->SetHamming(hammingDistance(m_Liste_I[index_I]->GetgenomeI(), m_GENOME_INIT_AP));
}

//* Génère les génomes des individus
void Simulation::Generate_genome_diversity()
{
    /**
     * Génère une liste d'indice aléatoire représentant les positions des bits
     * à complémenter.
     */
    uniform_int_distribution<int> rand_int_size(0, 31);
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        //* Initaliser des génomes pour les humains
        int rand_int_list_octet[m_GENOME_DIVERSITY_I]; // indices des génomes à complémenter
        for (int j = 0; j < m_GENOME_DIVERSITY_I; j++)
        {
            rand_int_list_octet[j] = rand_int_size(m_generator); // générer aléatoirement des indices
        }
        m_Liste_I[i]->SetgenomeI(Generate_Genome(m_GENOME_DIVERSITY_I, m_GENOME_INIT_I, rand_int_list_octet));
    }
}

//* Dépose tous les individus sur la grille
void Simulation::Add_individu_obj_to_grid()
{
    /**
     * Dépose tous les individus aléatoirement sans que deux
     * individus ne se trouvent sur la même cellule.
     * Set les coordonnées des individus dans leurs attributs.
     */
    uniform_int_distribution<int> rand_int_taille_systeme(0, m_TAILLE_SYSTEME - 1);
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        //* Générer les indices [i][j] de la matrice de pointeurs
        while (1)
        {
            int ligne, colonne;
            ligne = rand_int_taille_systeme(m_generator);
            colonne = rand_int_taille_systeme(m_generator);
            //* Assigner un pointeur à chaque individu
            if (m_Pointer_array_I[ligne][colonne] == NULL) // pointeur libre
            {
                m_Pointer_array_I[ligne][colonne] = m_Liste_I[i]; // assignation faite
                //* Enregistrer les coordonnées de l'individu dans ses attributs
                m_Liste_I[i]->SetXI(ligne);
                m_Liste_I[i]->SetYI(colonne);
                break;
            }
        }
    }
}