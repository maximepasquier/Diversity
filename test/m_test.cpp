#include <iostream>
#include <math.h>
#include "Individu.h"
#include "AP_linked_list_node.h"
#include "AP_linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

void Simulation::test_variables_coherence()
{
    //* TAILLE_SYSTEME non valide
    if (m_TAILLE_SYSTEME <= 0)
    {
        cout << "Valeur de TAILLE_SYSTEME non valide !" << endl;
        exit(EXIT_FAILURE);
    }

    //* NOMBRE_PERSONNES non valide
    if (m_NOMBRE_INDIVIDUS <= 0)
    {
        cout << "Valeur de NOMBRE_PERSONNES non valide !" << endl;
        exit(EXIT_FAILURE);
    }

    //* ITERATIONS non valide
    if (m_ITERATIONS <= 0)
    {
        cout << "Valeur de ITERATIONS non valide !" << endl;
        exit(EXIT_FAILURE);
    }

    //* GENOME_INIT_H non valide
    if (m_GENOME_INIT_I < 0 || m_GENOME_INIT_I > pow(2, 8 * sizeof(m_GENOME_INIT_I)))
    {
        cout << "Valeur de GENOME_INIT_H non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 2^" << 8 * sizeof(m_GENOME_INIT_I) << endl;
        exit(EXIT_FAILURE);
    }

    //* GENOME_DIVERSITY_H non valide
    if (m_GENOME_DIVERSITY_I < 0 || m_GENOME_DIVERSITY_I > 8 * sizeof(m_GENOME_DIVERSITY_I))
    {
        cout << "Valeur de GENOME_DIVERSITY_H non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et " << 8 * sizeof(m_GENOME_DIVERSITY_I) << endl;
        exit(EXIT_FAILURE);
    }

    //* GENOME_INIT_AP non valide
    if (m_GENOME_INIT_AP < 0 || m_GENOME_INIT_AP > pow(2, 8 * sizeof(m_GENOME_INIT_AP)))
    {
        cout << "Valeur de GENOME_INIT_AP non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 2^" << 8 * sizeof(m_GENOME_INIT_AP) << endl;
        exit(EXIT_FAILURE);
    }

    //* VITESSE_MUTATIONS_AP non valide
    if (m_VITESSE_MUTATIONS_AP < 0 || m_VITESSE_MUTATIONS_AP > 1)
    {
        cout << "Valeur de VITESSE_MUTATIONS_AP non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* CHARGE_VIRALE non valide
    if (m_CHARGE_VIRALE < 0 || m_CHARGE_VIRALE > 1)
    {
        cout << "Valeur de CHARGE_VIRALE non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* PUISSANCE non valide
    if (m_PARAMETRE_FONCTION <= 0 || m_PARAMETRE_FONCTION > 20)
    {
        cout << "Valeur de PUISSANCE non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 20" << endl;
        exit(EXIT_FAILURE);
    }

    //* TRAINEE non valide
    if (m_CELLULE_AP < 0 || m_CELLULE_AP > 1)
    {
        cout << "Valeur de TRAINEE non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* SURVIE_AP non valide
    if (m_SURVIE_AP < 0 || m_SURVIE_AP > 1)
    {
        cout << "Valeur de SURVIE_AP non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* Matrice suffisamment grande pour le nombre de personnes
    if (m_NOMBRE_INDIVIDUS > m_TAILLE_SYSTEME * m_TAILLE_SYSTEME)
    {
        cout << "Système trop petit pour le nombre de personnes !" << endl;
        cout << "Augmentez la valeur de TAILLE_SYSTEME ou réduisez la valeur de NOMBRE_PERSONNES du fichier config." << endl;
        exit(EXIT_FAILURE);
    }
}

void Simulation::test_is_Pointer_array_to_null()
{
    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j < m_TAILLE_SYSTEME; j++)
        {
            if (m_Pointer_array_I[i][j] != NULL || m_Pointer_array_AP[i][j] != NULL)
            {
                cout << "Les matrices de pointeurs n'ont pas été correctement initialisée à NULL !" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void Simulation::test_diversity_genome()
{
    //! Erreur si un bit est permuté deux fois, à modifier
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        //* La divergence des génomes par rapport à l'initial vaut la valeur de diversité
        if (hammingDistance(m_Liste_I[i]->GetgenomeI(), m_GENOME_INIT_I) != m_GENOME_DIVERSITY_I)
        {
            cout << "La génération de génomes pour les humains a rencontré une erreur !" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

void Simulation::test_humain_coords_conflits()
{
    //! Erreur avec cette fonction : temps exponentiel pour exécution
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        int x = m_Liste_I[i]->GetXI();
        int y = m_Liste_I[i]->GetYI();
        for (int j = 0; j < m_NOMBRE_INDIVIDUS; j++)
        {
            //* Deux individus sur la même ligne
            if(i != j && x == m_Liste_I[j]->GetXI())
            {
                //* Deux individus sur la même colonne
                if(y == m_Liste_I[j]->GetYI())
                {
                    cout << "Un collision s'est produite entre deux humains !" << endl;
                    cout << "Deux individus semblent se trouver sur la même cellule" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }   
    }
}