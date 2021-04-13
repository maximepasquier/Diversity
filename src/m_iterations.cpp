#include <iostream>
#include <math.h>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

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