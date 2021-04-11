#include <iostream>
#include <math.h>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"


using namespace std;

void test_variables_coherence(int TAILLE_SYSTEME, int NOMBRE_PERSONNES, int ITERATIONS, unsigned int GENOME_INIT_H, int GENOME_DIVERSITY_H, unsigned int GENOME_INIT_AP, float VITESSE_MUTATIONS_AP, float CHARGE_VIRALE, unsigned int PUISSANCE, float TRAINEE, float SURVIE_AP)
{
    //* TAILLE_SYSTEME non valide
    if (TAILLE_SYSTEME <= 0)
    {
        cout << "Valeur de TAILLE_SYSTEME non valide !" << endl;
        exit(EXIT_FAILURE);
    }

    //* NOMBRE_PERSONNES non valide
    if (NOMBRE_PERSONNES <= 0)
    {
        cout << "Valeur de NOMBRE_PERSONNES non valide !" << endl;
        exit(EXIT_FAILURE);
    }

    //* ITERATIONS non valide
    if (ITERATIONS <= 0)
    {
        cout << "Valeur de ITERATIONS non valide !" << endl;
        exit(EXIT_FAILURE);
    }

    //* GENOME_INIT_H non valide
    if (GENOME_INIT_H < 0 || GENOME_INIT_H > pow(2, 8 * sizeof(GENOME_INIT_H)))
    {
        cout << "Valeur de GENOME_INIT_H non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 2^" << 8 * sizeof(GENOME_INIT_H) << endl;
        exit(EXIT_FAILURE);
    }

    //* GENOME_DIVERSITY_H non valide
    if (GENOME_DIVERSITY_H < 0 || GENOME_DIVERSITY_H > 8 * sizeof(GENOME_DIVERSITY_H))
    {
        cout << "Valeur de GENOME_DIVERSITY_H non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et " << 8 * sizeof(GENOME_DIVERSITY_H) << endl;
        exit(EXIT_FAILURE);
    }

    //* GENOME_INIT_AP non valide
    if (GENOME_INIT_AP < 0 || GENOME_INIT_AP > pow(2, 8 * sizeof(GENOME_INIT_AP)))
    {
        cout << "Valeur de GENOME_INIT_AP non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 2^" << 8 * sizeof(GENOME_INIT_AP) << endl;
        exit(EXIT_FAILURE);
    }

    //* VITESSE_MUTATIONS_AP non valide
    if (VITESSE_MUTATIONS_AP < 0 || VITESSE_MUTATIONS_AP > 1)
    {
        cout << "Valeur de VITESSE_MUTATIONS_AP non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* CHARGE_VIRALE non valide
    if (CHARGE_VIRALE < 0 || CHARGE_VIRALE > 1)
    {
        cout << "Valeur de CHARGE_VIRALE non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* PUISSANCE non valide
    if (PUISSANCE <= 0 || PUISSANCE > 20)
    {
        cout << "Valeur de PUISSANCE non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 20" << endl;
        exit(EXIT_FAILURE);
    }

    //* TRAINEE non valide
    if (TRAINEE < 0 || TRAINEE > 1)
    {
        cout << "Valeur de TRAINEE non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* SURVIE_AP non valide
    if (SURVIE_AP < 0 || SURVIE_AP > 1)
    {
        cout << "Valeur de SURVIE_AP non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 1" << endl;
        exit(EXIT_FAILURE);
    }

    //* Matrice suffisamment grande pour le nombre de personnes
    if (NOMBRE_PERSONNES > TAILLE_SYSTEME * TAILLE_SYSTEME)
    {
        cout << "Système trop petit pour le nombre de personnes !" << endl;
        cout << "Augmentez la valeur de TAILLE_SYSTEME ou réduisez la valeur de NOMBRE_PERSONNES du fichier config." << endl;
        exit(EXIT_FAILURE);
    }
}

void test_is_Pointer_array_to_null(int TAILLE_SYSTEME, Humain ***Pointer_array_H, node ***Pointer_array_AP)
{
    for (int i = 0; i < TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j < TAILLE_SYSTEME; j++)
        {
            if (Pointer_array_H[i][j] != NULL || Pointer_array_AP[i][j] != NULL)
            {
                cout << "Les matrices de pointeurs n'ont pas été correctement initialisée à NULL !" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void test_diversity_genome(Humain **Liste_H, int NOMBRE_PERSONNES, int GENOME_DIVERSITY_H, unsigned int GENOME_INIT_H)
{
    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        //* La divergence des génomes par rapport à l'initial vaut la valeur de diversité
        if (hammingDistance(Liste_H[i]->GetgenomeH(), GENOME_INIT_H) != GENOME_DIVERSITY_H)
        {
            cout << "La génération de génomes pour les humains a rencontré une erreur !" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

void test_humain_coords_conflits(Humain **Liste_H, int NOMBRE_PERSONNES)
{
    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        int x = Liste_H[i]->GetXH();
        int y = Liste_H[i]->GetYH();
        for (int j = 0; j < NOMBRE_PERSONNES; j++)
        {
            //* Deux individus sur la même ligne
            if(i != j && x == Liste_H[j]->GetXH())
            {
                //* Deux individus sur la même colonne
                if(y == Liste_H[j]->GetYH())
                {
                    cout << "Un collision s'est produite entre deux humains !" << endl;
                    cout << "Deux individus semblent se trouver sur la même cellule" << endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        
    }
    
}