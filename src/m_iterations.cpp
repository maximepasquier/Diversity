#include <chrono>
#include <random>
#include "Individu.h"
#include "AP_linked_list_node.h"
#include "AP_linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

void Simulation::Iterations()
{
    for (int iteration = 0; iteration < m_ITERATIONS; iteration++)
    {
        //* Print les itérations (avancement)
        Print_progression(iteration, m_ITERATIONS);
        //* Print ASCII grid to screen
        //Print_ASCII_grid(m_TAILLE_SYSTEME, m_Pointer_array_H, m_Pointer_array_AP);
        One_iteration(iteration);
    }
}

void Simulation::One_iteration(int iteration)
{
    //* Compter le nombre de contaminés
    m_nombre_contamine = Update_infected_number();

    //* Compter le nombre d'agents pathogènes différents
    m_nombre_AP_diff = Update_nombre_AP_diff();

    //* Write to .csv file
    //Update_csv_all_data(iteration);
    Update_csv();

    //* Construire la permutations de la liste humain
    int *permuted_liste = new int[m_NOMBRE_PERSONNES];
    Permutation(permuted_liste, m_NOMBRE_PERSONNES);

    //* Parcours du domaine (liste agents pathogènes)
    Update_all_AP();
    //* Parcours du domaine (liste humains)
    Update_all_H(permuted_liste);
    //* Sleep (FPS)
    //this_thread::sleep_for(chrono::seconds(1));
    //* Supprimer la permutation
    delete[] permuted_liste;
}

void Simulation::Update_all_AP()
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    AP_linked_list_node *tmp = m_Liste_AP.Get_head();
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
    int x = m_Liste_I[index_H]->GetXH();
    int y = m_Liste_I[index_H]->GetYH();
    vector<pair<int, int>> coordonnees(4);

    //* Push les coordonnées des 4 voisins
    Get_coords_voisins(coordonnees, m_TAILLE_SYSTEME, x, y);

    Contamination_cases(&coordonnees, x, y, index_H);

    //* Mouvements
    Mouvement(&coordonnees, x, y);
}

void Simulation::Mouvement(vector<pair<int, int>> *coordonnees, int x, int y)
{
    uniform_int_distribution<int> randInt(0, 3);
    //* Choix d'une case voisine
    int choix = randInt(generator);
    if (m_Pointer_array_I[coordonnees->at(choix).first][coordonnees->at(choix).second] == NULL) // cellule libre
    {
        Moving(coordonnees, x, y, choix);
    }
}

void Simulation::Moving(vector<pair<int, int>> *coordonnees, int x, int y, int choix)
{
    //* Si l'individu est contaminé
    if (m_Pointer_array_I[x][y]->Getcontamine())
    {
        Contaminate_cell(x, y);
    }
    Pointer_move_update(coordonnees, x, y, choix);
}

void Simulation::Pointer_move_update(vector<pair<int, int>> *coordonnees, int x, int y, int choix)
{
    //* Mise à jour des coordonnées de l'humain
    m_Pointer_array_I[x][y]->SetXH(coordonnees->at(choix).first);
    m_Pointer_array_I[x][y]->SetYH(coordonnees->at(choix).second);
    //* Swap les pointeurs
    m_Pointer_array_I[coordonnees->at(choix).first][coordonnees->at(choix).second] = m_Pointer_array_I[x][y]; // le pointeur voisin pointe sur notre humain
    m_Pointer_array_I[x][y] = NULL;
}

void Simulation::Contaminate_cell(int x, int y)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
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
        Add_AP_to_cell(x, y);
    }
}

void Simulation::Add_AP_to_cell(int x, int y)
{
    Agent_Pathogene *AP;
    AP = new Agent_Pathogene();
    m_Pointer_array_AP[x][y] = m_Liste_AP.add_node(*AP);
    m_Pointer_array_AP[x][y]->AP.SetgenomeAP(m_Pointer_array_I[x][y]->GetgenomeAP());
    //* Sauver les coordonnées de l'agent pathogène dans ses attributs
    m_Pointer_array_AP[x][y]->AP.SetXAP(x);
    m_Pointer_array_AP[x][y]->AP.SetYAP(y);
}

void Simulation::Contamination_cases(vector<pair<int, int>> *coordonnees, int x, int y, int index_H)
{
    //* Déterminer les cas
    if (m_Liste_I[index_H]->Getcontamine()) //* contaminé
    {
        Humain_hote(index_H);
    }
    else //* pas contaminé
    {
        //* Un AP se trouve sur la même cellule
        Collision_H_AP(x, y, index_H);

        //* Analyse du voisinage
        Analyse_voisinage(coordonnees, index_H);

        //* Si contaminé à cette itération alors on vérifie si il y a résistance naturelle
        if (m_Liste_I[index_H]->Getcontamine())
        {
            Resistance_naturelle(index_H);
        }
    }
}

void Simulation::Analyse_voisinage(vector<pair<int, int>> *coordonnees, int index_H)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    for (int i = 0; i < coordonnees->size(); i++)
    {
        if (m_Pointer_array_I[coordonnees->at(i).first][coordonnees->at(i).second] != NULL) // un humain occupe cette case voisine
        {
            if (m_Pointer_array_I[coordonnees->at(i).first][coordonnees->at(i).second]->Getcontamine()) // ce voisin est contaminé
            {
                if (!Is_immune(index_H, m_Pointer_array_I[coordonnees->at(i).first][coordonnees->at(i).second]->GetgenomeAP()))
                {
                    float rand_f = rand_float(generator);
                    if (rand_f < m_CHARGE_VIRALE) // charge virale
                    {
                        //* Notre humain a été infecté par ce voisin
                        m_Liste_I[index_H]->Setcontamine(true);
                        m_Liste_I[index_H]->SetgenomeAP(m_Pointer_array_I[coordonnees->at(i).first][coordonnees->at(i).second]->GetgenomeAP());
                        m_Liste_I[index_H]->SetHamming(hammingDistance(m_Liste_I[index_H]->GetgenomeH(), m_Liste_I[index_H]->GetgenomeAP()));
                    }
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
        if (!m_Liste_I[index_H]->Getcontamine()) // l'humain doit être sain pour être contaminé par ce pahogène
        {
            if (!Is_immune(index_H, m_Pointer_array_AP[x][y]->AP.GetgenomeAP()))
            {
                float rand_f = rand_float(generator);
                if (rand_f < m_CHARGE_VIRALE)
                {
                    //* L'humain est contaminé par ce pathogène
                    m_Liste_I[index_H]->Setcontamine(true);
                    m_Liste_I[index_H]->SetgenomeAP(m_Pointer_array_AP[x][y]->AP.GetgenomeAP());
                    m_Liste_I[index_H]->SetHamming(hammingDistance(m_Liste_I[index_H]->GetgenomeH(), m_Liste_I[index_H]->GetgenomeAP()));
                }
            }
        }
    }
}

void Simulation::Resistance_naturelle(int index_H)
{
    //* Déterminer si l'individu est résistant au pathogène contracté
    float chance = Genome_Match(m_Liste_I[index_H]->GetHamming(), sizeof(m_Liste_I[index_H]->GetgenomeH()), m_PUISSANCE);
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    float rand_f = rand_float(generator);
    if (rand_f < chance) // on se débarrasse du pathogène, on est résistant
    {
        m_Liste_I[index_H]->Setcontamine(false);
    }
    else
    {
        m_Liste_I[index_H]->IncrNombreDeFoisContamine();
    }
}

void Simulation::Humain_hote(int index_H)
{
    //* Déterminer la probabilité de s'immuniser à ce tour (en fonction des génomes)
    //float chance; // % entre 0 et 1
    //* Chance de se débarrasser du pathogène
    //int distance = hammingDistance(m_Liste_H[index_H]->GetgenomeH(), m_Liste_H[index_H]->GetgenomeAP());
    float chance = Genome_Match(m_Liste_I[index_H]->GetHamming(), sizeof(m_Liste_I[index_H]->GetgenomeH()), m_PUISSANCE);
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    float rand_f = rand_float(generator);
    if (rand_f < chance) // on se débarrasse du pathogène
    {
        Get_immunity(index_H);
    }
    else // le pathogène reste
    {
        AP_mutation(index_H);
    }
}

void Simulation::Get_immunity(int index_H)
{
    //* Immune
    m_Liste_I[index_H]->Setcontamine(false);
    m_Liste_I[index_H]->Setimmune(m_Liste_I[index_H]->GetgenomeAP());
    //m_Liste_H[index_H]->SetgenomeAP(0);
}

void Simulation::AP_mutation(int index_H)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    uniform_int_distribution<int> rand_int_size(0, 31);
    //* Le pathogène mute
    float rand_f = rand_float(generator);
    if (rand_f < m_VITESSE_MUTATIONS_AP)
    {
        int index = rand_int_size(generator);
        m_Liste_I[index_H]->SetgenomeAP(Mutations_AP(m_Liste_I[index_H]->GetgenomeAP(), index));
    }
}

bool Simulation::Is_immune(int index_H, unsigned int genome_AP)
{
    vector<unsigned int> liste_immunite = m_Liste_I[index_H]->Getimmune();
    for (int j = 0; j < liste_immunite.size(); j++)
    {
        if (liste_immunite[j] == genome_AP)
        {
            return true;
        }
    }
    return false;
}
