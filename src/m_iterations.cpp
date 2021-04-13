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
        One_iteration();
    }
}

void Simulation::One_iteration()
{
    //* Print les itérations (avancement)
    //Print_progression(iteration, ITERATIONS);

    //* Write to .csv file
    Update_csv();

    //* Print ASCII grid to screen
    Print_ASCII_grid(m_TAILLE_SYSTEME, m_Pointer_array_H, m_Pointer_array_AP);

    //* Construire la permutations de la liste humain
    int *permuted_liste = new int[m_NOMBRE_PERSONNES];
    Permutation(permuted_liste, m_NOMBRE_PERSONNES);

    //* Parcours du domaine (liste agents pathogènes)
    Update_all_AP();

    //* Parcours du domaine (liste humains)
    Update_all_H(permuted_liste);
    //* Sleep (FPS)
    this_thread::sleep_for(chrono::seconds(1));
    //* Supprimer la permutation
    delete[] permuted_liste;
}

void Simulation::Update_all_AP()
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    node *tmp = m_Liste_AP.Get_head();
    while (tmp != NULL)
    {
        float rand_f = rand_float(generator);
        if (rand_f > m_SURVIE_AP)
        {
            //* Destruction de l'agent pathogène
            int x = tmp->AP.GetXAP();
            int y = tmp->AP.GetYAP();
            m_Liste_AP.remove_element(m_Pointer_array_AP[x][y]);
            m_Pointer_array_AP[x][y] = NULL;
        }
        tmp = tmp->suivant;
    }
}

void Simulation::Update_all_H(int *permuted_liste)
{
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        int index_H = permuted_liste[i];
        Update_one_H(index_H);
    }
}

void Simulation::Update_one_H(int index_H)
{
    int x = m_Liste_H[index_H]->GetXH();
    int y = m_Liste_H[index_H]->GetYH();
    vector<pair<int, int>> coordonnees; // vecteur de paire de int
    //* Push les coordonnées des 4 voisins
    Get_coords_voisins(&coordonnees, m_TAILLE_SYSTEME, x, y);

    Contamination_cases(&coordonnees, x, y, index_H);

    //* Mouvements
    Mouvement(&coordonnees, x, y);
}

void Simulation::Mouvement(vector<pair<int, int>> *coordonnees, int x, int y)
{
    uniform_int_distribution<int> randInt(0, 3);
    //* Choix d'une case voisine
    int choix = randInt(generator);
    if (m_Pointer_array_H[coordonnees->at(choix).first][coordonnees->at(choix).second] == NULL) // cellule libre
    {
        Moving(coordonnees, x, y, choix);
    }
}

void Simulation::Moving(vector<pair<int, int>> *coordonnees, int x, int y, int choix)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    //* Si l'individu est contaminé
    if (m_Pointer_array_H[x][y]->Getcontamine())
    {
        //* Déterminer si l'humain contamine la cellule qu'il quitte
        float rand_f = rand_float(generator);
        if (rand_f < m_TRAINEE)
        {
            //* Cellule contaminée (avant de bouger)
            if (m_Pointer_array_AP[x][y] != NULL)
            {
                //* Un AP a déjà contaminé la cellule (on l'écrase)
                m_Liste_AP.remove_element(m_Pointer_array_AP[x][y]);
                m_Pointer_array_AP[x][y] = NULL;
            }
            Agent_Pathogene *AP;
            AP = new Agent_Pathogene();
            m_Pointer_array_AP[x][y] = m_Liste_AP.add_node(*AP);
            m_Pointer_array_AP[x][y]->AP.SetgenomeAP(m_Pointer_array_H[x][y]->GetgenomeAP());
            //* Sauver les coordonnées de l'agent pathogène dans ses attributs
            m_Pointer_array_AP[x][y]->AP.SetXAP(x);
            m_Pointer_array_AP[x][y]->AP.SetYAP(y);
        }
    }
    //* Mise à jour des coordonnées de l'humain
    m_Pointer_array_H[x][y]->SetXH(coordonnees->at(choix).first);
    m_Pointer_array_H[x][y]->SetYH(coordonnees->at(choix).second);
    //* Swap les pointeurs
    m_Pointer_array_H[coordonnees->at(choix).first][coordonnees->at(choix).second] = m_Pointer_array_H[x][y]; // le pointeur voisin pointe sur notre humain
    m_Pointer_array_H[x][y] = NULL;                                                                           // le pointeur actuel cesse de pointer sur notre humain
}

void Simulation::Contamination_cases(vector<pair<int, int>> *coordonnees, int x, int y, int index_H)
{
    //* Déterminer les cas
    if (m_Liste_H[index_H]->Getcontamine()) //* contaminé
    {
        Humain_hote(index_H);
    }
    else //* pas contaminé
    {
        //* Un AP se trouve sur la même cellule
        Collision_H_AP(x, y, index_H);

        //* Analyse du voisinage
        Analyse_voisinage(coordonnees, index_H);
    }
}

void Simulation::Analyse_voisinage(vector<pair<int, int>> *coordonnees, int index_H)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    for (int i = 0; i < coordonnees->size(); i++)
    {
        if (m_Pointer_array_H[coordonnees->at(i).first][coordonnees->at(i).second] != NULL) // un humain occupe cette case voisine
        {
            if (m_Pointer_array_H[coordonnees->at(i).first][coordonnees->at(i).second]->Getcontamine()) // ce voisin est contaminé
            {
                float rand_f = rand_float(generator);
                if (rand_f < m_CHARGE_VIRALE) // charge virale
                {
                    //* Notre humain a été infecté par ce voisin
                    m_Liste_H[index_H]->Setcontamine(true);
                    m_Liste_H[index_H]->SetgenomeAP(m_Pointer_array_H[coordonnees->at(i).first][coordonnees->at(i).second]->GetgenomeAP());
                }
            }
        }
    }
}

void Simulation::Collision_H_AP(int x, int y, int index_H)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    if (m_Pointer_array_AP[x][y] != NULL)
    {
        if (!m_Liste_H[index_H]->Getcontamine()) // l'humain doit être sain pour être contaminé par ce pahogène
        {
            float rand_f = rand_float(generator);
            if (rand_f < m_CHARGE_VIRALE)
            {
                //* L'humain est contaminé par ce pathogène
                m_Liste_H[index_H]->Setcontamine(true);
                m_Liste_H[index_H]->SetgenomeAP(m_Pointer_array_AP[x][y]->AP.GetgenomeAP());
            }
        }
    }
}

void Simulation::Humain_hote(int index_H)
{
    //* Déterminer si il y a déjà une immunité
    bool immunise = false;
    vector<unsigned int> liste_immunite = m_Liste_H[index_H]->Getimmune();
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    uniform_int_distribution<int> rand_int_size(0, 31);
    for (int j = 0; j < liste_immunite.size(); j++)
    {
        if (liste_immunite[j] == m_Liste_H[index_H]->GetgenomeAP())
        {
            immunise = true;
            m_Liste_H[index_H]->Setcontamine(false);
            m_Liste_H[index_H]->SetgenomeAP(0);
            break;
        }
    }
    if (!immunise)
    {
        //* Déterminer la probabilité de s'immuniser à ce tour (en fonction des génomes)
        float chance; // % entre 0 et 1
        //* Chance de se débarrasser du pathogène
        chance = Genome_Match(m_Liste_H[index_H]->GetgenomeH(), m_Liste_H[index_H]->GetgenomeAP(), m_PUISSANCE);

        float rand_f = rand_float(generator);
        if (rand_f < chance) // on se débarrasse du pathogène
        {
            //* Immune
            m_Liste_H[index_H]->Setcontamine(false);
            m_Liste_H[index_H]->Setimmune(m_Liste_H[index_H]->GetgenomeAP());
            m_Liste_H[index_H]->SetgenomeAP(0);
        }
        else // le pathogène reste
        {
            //* Le pathogène mute
            float rand_f = rand_float(generator);
            if (rand_f < m_VITESSE_MUTATIONS_AP)
            {
                int index = rand_int_size(generator);
                m_Liste_H[index_H]->SetgenomeAP(Mutations_AP(m_Liste_H[index_H]->GetgenomeAP(), index));
            }
        }
    }
}