#include <iostream>
#include <math.h>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

void Simulation::test_variables_coherence2()
{
    //* TAILLE_SYSTEME non valide
    if (m_TAILLE_SYSTEME <= 0)
    {
        cout << "Valeur de TAILLE_SYSTEME non valide !" << endl;
        exit(EXIT_FAILURE);
    }

    //* NOMBRE_PERSONNES non valide
    if (m_NOMBRE_PERSONNES <= 0)
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
    if (m_GENOME_INIT_H < 0 || m_GENOME_INIT_H > pow(2, 8 * sizeof(m_GENOME_INIT_H)))
    {
        cout << "Valeur de GENOME_INIT_H non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 2^" << 8 * sizeof(m_GENOME_INIT_H) << endl;
        exit(EXIT_FAILURE);
    }

    //* GENOME_DIVERSITY_H non valide
    if (m_GENOME_DIVERSITY_H < 0 || m_GENOME_DIVERSITY_H > 8 * sizeof(m_GENOME_DIVERSITY_H))
    {
        cout << "Valeur de GENOME_DIVERSITY_H non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et " << 8 * sizeof(m_GENOME_DIVERSITY_H) << endl;
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
    if (m_PUISSANCE <= 0 || m_PUISSANCE > 20)
    {
        cout << "Valeur de PUISSANCE non valide !" << endl;
        cout << "Les valeurs adimissibles sont comprises entre 0 et 20" << endl;
        exit(EXIT_FAILURE);
    }

    //* TRAINEE non valide
    if (m_TRAINEE < 0 || m_TRAINEE > 1)
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
    if (m_NOMBRE_PERSONNES > m_TAILLE_SYSTEME * m_TAILLE_SYSTEME)
    {
        cout << "Système trop petit pour le nombre de personnes !" << endl;
        cout << "Augmentez la valeur de TAILLE_SYSTEME ou réduisez la valeur de NOMBRE_PERSONNES du fichier config." << endl;
        exit(EXIT_FAILURE);
    }
}