#include <chrono>
#include <random>
#include <iostream>
#include "Individu.h"
#include "AP_linked_list_node.h"
#include "AP_linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

//* Ensemble de toutes les itérations de la simulation
void Simulation::Iterations()
{
    //* Itère sur le nombre d'itération de la simulation
    for (int iteration = 0; iteration < m_ITERATIONS; iteration++)
    {
        //* Print les itérations (avancement)
        Print_progression(iteration, m_ITERATIONS);
        //* Print ASCII grid to screen
        //Print_ASCII_grid(m_TAILLE_SYSTEME, m_Pointer_array_H, m_Pointer_array_AP);
        One_iteration(iteration);
    }
}

//* Une seule itération
void Simulation::One_iteration(int iteration)
{
    //* Compter le nombre de contaminés
    m_nombre_contamine = Update_infected_number();

    //* Compter le nombre d'agents pathogènes différents
    m_nombre_AP_diff = Update_nombre_AP_diff();

    //* Write to .csv file
    //Update_csv_all_data(iteration);
    Update_csv();

    //* Compter le nombre de recovered pour le modèle SIR
    m_SIR_recovered_file << '\n'
                         << SIR_recovered();

    //* Construire la permutations de la liste d'individus
    int *permuted_liste = new int[m_NOMBRE_INDIVIDUS];
    Permutation(permuted_liste, m_NOMBRE_INDIVIDUS);

    //* Parcours du domaine (liste agents pathogènes)
    Update_all_AP();
    //* Parcours du domaine (liste humains)
    Update_all_I(permuted_liste);
    //* Sleep (FPS)
    //this_thread::sleep_for(chrono::seconds(1));
    //* Supprimer la permutation
    delete[] permuted_liste;
}

//* Mise à jour de tous les agents pathogènes
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

//* Mise à jour de tous les individus
void Simulation::Update_all_I(int *permuted_liste)
{
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        int index_I = permuted_liste[i];
        Update_one_I(index_I);
    }
}

//* Mise à jour de l'individu indexé à index_I
void Simulation::Update_one_I(int index_I)
{
    bool RunOnce = true;
    for (int i = 0; i < m_NOMBRE_MOUVEMENT; i++)
    {
        //* Get coords de l'individu
        int x = m_Liste_I[index_I]->GetXI();
        int y = m_Liste_I[index_I]->GetYI();
        int coords[4][2] = {{x, (y - 1 + m_TAILLE_SYSTEME) % m_TAILLE_SYSTEME}, {x, (y + 1) % m_TAILLE_SYSTEME}, {(x - 1 + m_TAILLE_SYSTEME) % m_TAILLE_SYSTEME, y}, {(x + 1) % m_TAILLE_SYSTEME, y}};

        //* Mise à jour de l'état de l'individu
        if (RunOnce)
        {
            Contamination_cases(coords, x, y, index_I);
            RunOnce = false;
        }

        //* Mouvements
        Mouvement(coords, x, y);
    }
}

//* Permet de déplacer un individu
void Simulation::Mouvement(int coords[4][2], int x, int y)
{
    uniform_int_distribution<int> randInt(0, 3);
    //* Choix d'une case voisine
    int choix = randInt(generator);
    if (m_Pointer_array_I[coords[choix][0]][coords[choix][1]] == NULL) // cellule libre
    {
        Moving(coords, x, y, choix);
    }
}

//* Déplace un individu
void Simulation::Moving(int coords[4][2], int x, int y, int choix)
{
    //* Si l'individu est contaminé
    if (m_Pointer_array_I[x][y]->Getcontamine())
    {
        Contaminate_cell(x, y);
    }
    Pointer_move_update(coords, x, y, choix);
}

//* Modifier coordonnées individu
void Simulation::Pointer_move_update(int coords[4][2], int x, int y, int choix)
{
    //* Mise à jour des coordonnées de l'individu
    m_Pointer_array_I[x][y]->SetXI(coords[choix][0]);
    m_Pointer_array_I[x][y]->SetYI(coords[choix][1]);
    //* Swap les pointeurs
    m_Pointer_array_I[coords[choix][0]][coords[choix][1]] = m_Pointer_array_I[x][y]; // le pointeur voisin pointe sur notre individu
    m_Pointer_array_I[x][y] = NULL;
}

//* Contaminer la cellule
void Simulation::Contaminate_cell(int x, int y)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    //* Déterminer si l'humain contamine la cellule qu'il quitte
    float rand_f = rand_float(generator);
    if (rand_f < m_CELLULE_AP)
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

//* Ajouter un pathogène sur la cellule contaminée
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

//* Mise à jour de l'état de l'individu
void Simulation::Contamination_cases(int coords[4][2], int x, int y, int index_I)
{
    //* Déterminer les cas
    if (m_Liste_I[index_I]->Getcontamine()) //* contaminé
    {
        //* Incrémente le compteur d'itération contaminé
        m_Liste_I[index_I]->IncrTempsContamine();
        Individu_hote(index_I);
    }
    else //* pas contaminé
    {
        //* Un AP se trouve sur la même cellule
        Collision_I_AP(x, y, index_I);

        //* Analyse du voisinage
        Analyse_voisinage(coords, index_I);
    }
}

//* Interactions avec le voisinage
void Simulation::Analyse_voisinage(int coords[4][2], int index_I)
{
    /**
     * Regarder les 4 cellules voisines
     * Regarder si les individus sur ces cellules sont contaminés
     * Regarder si notre individu est déjà immunisé au pathogène du voisin
     * Passer la probabilité de la charge virale
     * Contaminer l'individu 
     */
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    for (int i = 0; i < 4; i++)
    {
        if (m_Pointer_array_I[coords[i][0]][coords[i][1]] != NULL) // un individus occupe cette case voisine
        {
            if (m_Pointer_array_I[coords[i][0]][coords[i][1]]->Getcontamine()) // ce voisin est contaminé
            {
                float rand_f = rand_float(generator);
                if (rand_f < m_CHARGE_VIRALE) // charge virale
                {
                    if (!Is_immune(index_I, m_Pointer_array_I[coords[i][0]][coords[i][1]]->GetgenomeAP()))
                    {
                        //* Notre humain a été infecté par ce voisin
                        m_Liste_I[index_I]->Setcontamine(true);
                        m_Liste_I[index_I]->SetgenomeAP(m_Pointer_array_I[coords[i][0]][coords[i][1]]->GetgenomeAP());
                        m_Liste_I[index_I]->SetHamming(hammingDistance(m_Liste_I[index_I]->GetgenomeI(), m_Liste_I[index_I]->GetgenomeAP()));
                    }
                }
            }
        }
    }
}

//* Individu sain sur la même cellule qu'un pathogène
void Simulation::Collision_I_AP(int x, int y, int index_I)
{
    /**
     * Vérifier si un pathogène est sur la même cellule que l'individu
     * Vérifier que l'individu n'est pas déjà immunisé à ce pathogène
     * Passer la probabilité de la charge virale
     * Contaminer l'individu 
     */
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    if (m_Pointer_array_AP[x][y] != NULL)
    {
        float rand_f = rand_float(generator);
        if (rand_f < m_CHARGE_VIRALE)
        {
            if (!Is_immune(index_I, m_Pointer_array_AP[x][y]->AP.GetgenomeAP()))
            {
                //* L'humain est contaminé par ce pathogène
                m_Liste_I[index_I]->Setcontamine(true);
                m_Liste_I[index_I]->SetgenomeAP(m_Pointer_array_AP[x][y]->AP.GetgenomeAP());
                m_Liste_I[index_I]->SetHamming(hammingDistance(m_Liste_I[index_I]->GetgenomeI(), m_Liste_I[index_I]->GetgenomeAP()));
            }
        }
    }
}

//* Mise à jour de l'individu contaminé
void Simulation::Individu_hote(int index_I)
{
    /**
     * Détermine la probabilité de s'immuniser en se basant 
     * sur la distance de hamming entre le génome de l'individu
     * et celui du pèathogène qui l'habite.
     * Si l'individu ne s'immunise pas alors le pathogène 
     * peut muter
     */
    //* Incrémente le nombre de fois contaminé
    if (m_Liste_I[index_I]->GetTempsContamine() == m_TEMPS_AVANT_IMMUNITE)
    {
        m_Liste_I[index_I]->IncrNombreDeFoisContamine();
    }

    //* Déterminer la probabilité de s'immuniser à ce tour (en fonction des génomes)
    float chance = Genome_Match(m_Liste_I[index_I]->GetHamming(), sizeof(m_Liste_I[index_I]->GetgenomeI()), m_PARAMETRE_FONCTION);
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    float rand_f = rand_float(generator);
    if (rand_f < chance) // on se débarrasse du pathogène
    {
        //* Déterminer si l'individu s'immunise ou est naturellement résistant
        if (m_Liste_I[index_I]->GetTempsContamine() < m_TEMPS_AVANT_IMMUNITE)
        {
            if (m_RESISTANCE_MECANISME)
            {
                Resistance_naturelle(index_I);
                //* Reset le compteur de temps étant contaminé
                m_Liste_I[index_I]->SetTempsContamine(0);
            }
        }
        else
        {
            if (m_IMMUNITE_MECANISME)
            {
                Get_immunity(index_I);
                //* Reset le compteur de temps étant contaminé
                m_Liste_I[index_I]->SetTempsContamine(0);
            }
        }
    }
    else // le pathogène reste
    {
        AP_mutation(index_I);
    }
}

//* Développe une immunité
void Simulation::Get_immunity(int index_I)
{
    //* Immune
    m_Liste_I[index_I]->Setcontamine(false);
    m_Liste_I[index_I]->Setimmune(m_Liste_I[index_I]->GetgenomeAP());
}

//* L'individu est résistant au pathogène
void Simulation::Resistance_naturelle(int index_I)
{
    m_Liste_I[index_I]->Setcontamine(false);
}

//* Mutation de l'agent pathogène
void Simulation::AP_mutation(int index_I)
{
    /**
     * Un paramètre du modèle définit la probabilité 
     * qu'un pathogène mute.
     * Une mutation ne consiste qu'à complémenter un
     * seul bit du génome. 
     */
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    uniform_int_distribution<int> rand_int_size(0, 31);
    //* Le pathogène mute
    float rand_f = rand_float(generator);
    if (rand_f < m_VITESSE_MUTATIONS_AP)
    {
        int index = rand_int_size(generator);
        m_Liste_I[index_I]->SetgenomeAP(Mutations_AP(m_Liste_I[index_I]->GetgenomeAP(), index));
    }
}

//* Vérifie si l'individu est déjà immunisé
bool Simulation::Is_immune(int index_I, unsigned int genome_AP)
{
    /**
     * Vérifie si l'individu d'index index_I est déjà 
     * immunié à pahtogène avec le génome genome_AP 
     */
    vector<unsigned int> liste_immunite = m_Liste_I[index_I]->Getimmune();
    for (int j = 0; j < liste_immunite.size(); j++)
    {
        if (liste_immunite[j] == genome_AP)
        {
            return true;
        }
    }
    return false;
}
