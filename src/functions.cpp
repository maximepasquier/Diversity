#include <sys/ioctl.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include <random>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"

using namespace std;

extern default_random_engine generator;

void Knuth_Shuffle(int *liste, int taille)
{
    srand(time(NULL));
    for (int i = taille - 1; i > 0; i--)
    {
        int index = rand() % (i + 1);
        int tmp = liste[i];
        liste[i] = liste[index];
        liste[index] = tmp;
    }
}

int hammingDistance(unsigned int n1, unsigned int n2)
{
    unsigned int x = n1 ^ n2;
    int distance = 0;
    while (x > 0)
    {
        distance += x & 1;
        x >>= 1;
    }
    return distance;
}

//* Détermine le match entre deux génomes donnés
float Genome_Match(unsigned int Genome_H, unsigned int Genome_AP, unsigned int puissance)
{
    int distance;
    distance = hammingDistance(Genome_H, Genome_AP);
    return pow(distance, puissance) / pow(sizeof(Genome_H) * 8, puissance);
}

unsigned int Generate_Genome(int deviation, unsigned int init, int *rand_int_list_octet)
{
    unsigned int mask = 0;
    for (int i = 0; i < deviation; i++)
    {
        int index = rand_int_list_octet[i];
        mask += 1 << index;
    }
    return init ^ mask;
}

unsigned int Mutations_AP(unsigned int genome_AP, int index)
{
    unsigned int mask = 0;
    mask = 1 << index;
    return genome_AP ^ mask;
}
/*
void Pointer_array_to_NULL(int taille, Humain ***Pointer_array_H, node ***Pointer_array_AP)
{
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            Pointer_array_H[i][j] = NULL;
            Pointer_array_AP[i][j] = NULL;
        }
    }
}

void Generate_human_genome_diversity(int nb_personnes, int genome_diversity_h, unsigned int genome_init_h, Humain **Liste_H)
{
    uniform_int_distribution<int> rand_int_size(0, 31);
    for (int i = 0; i < nb_personnes; i++)
    {
        //* Initaliser des génomes pour les humains
        int rand_int_list_octet[genome_diversity_h]; // indices des génomes à complémenter
        for (int j = 0; j < genome_diversity_h; j++)
        {
            rand_int_list_octet[j] = rand_int_size(generator); // générer aléatoirement des indices
        }
        Liste_H[i]->SetgenomeH(Generate_Genome(genome_diversity_h, genome_init_h, rand_int_list_octet));
    }
}


void Add_human_obj_to_grid(int nb_personnes, int taille_systeme, Humain **Liste_H, Humain ***Pointer_array_H)
{
    uniform_int_distribution<int> rand_int_taille_systeme(0, taille_systeme - 1);
    for (int i = 0; i < nb_personnes; i++)
    {
        //* Générer les indices [i][j] de la matrice de pointeurs
        while (1)
        {
            int ligne, colonne;
            ligne = rand_int_taille_systeme(generator);
            colonne = rand_int_taille_systeme(generator);
            //* Assigner un pointeur à chaque humain
            if (Pointer_array_H[ligne][colonne] == NULL) // pointeur libre
            {
                Pointer_array_H[ligne][colonne] = Liste_H[i]; // assignation faite
                //* Enregistrer les coordonnées de l'humain dans ses attributs
                Liste_H[i]->SetXH(ligne);
                Liste_H[i]->SetYH(colonne);
                break;
            }
        }
    }
}
*/
void Print_progression(int current_iteration, int total)
{
    printf("%c[2K", 27); // clear line
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    //printf("lines %d\n", w.ws_row);
    //printf("columns %d\n", w.ws_col);
    float ratio_done = (float)(current_iteration + 1) / (float)total;
    string progression = "[";
    cout << "Progress : [" << int(ratio_done * 100) << "%]";
    for (int i = 0; i < w.ws_col - 20; i++)
    {
        float a = (float)i / (float)(w.ws_col - 20);
        if (a < ratio_done)
        {
            progression.append("#");
        }
        else
        {
            progression.append(".");
        }
    }
    progression.append("]");
    cout << progression << '\r';
    cout.flush();
    if (current_iteration == total - 1)
    {
        cout << endl;
    }
}

void Print_ASCII_grid(int taille_sys, Humain ***Pointer_array_H, node ***Pointer_array_AP)
{
    printf("\x1b[2J"); // clear screen
    printf("\x1b[H");  // returning the cursor to the home position

    //* Parcours du domaine pour l'affichage
    for (int i = 0; i < taille_sys; i++)
    {
        for (int j = 0; j < taille_sys; j++)
        {
            int count = 3;
            if (Pointer_array_H[i][j] != NULL) // la cellule pointe sur un humain !
            {
                cout << Pointer_array_H[i][j]->Getcontamine();
                count--;
            }
            if (Pointer_array_AP[i][j] != NULL)
            {
                cout << '2';
                count--;
            }
            if (count == 3) // la cellule ne pointe sur rien
            {
                cout << "-- ";
                continue;
            }
            for (int i = 0; i < count; i++)
            {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void Update_AP(Linked_list *Liste_AP, node ***Pointer_array_AP, float survie_ap)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    node *tmp = Liste_AP->Get_head();
    while (tmp != NULL)
    {
        float rand_f = rand_float(generator);
        if (rand_f > survie_ap)
        {
            //* Destruction de l'agent pathogène
            int x = tmp->AP.GetXAP();
            int y = tmp->AP.GetYAP();
            Liste_AP->remove_element(Pointer_array_AP[x][y]);
            Pointer_array_AP[x][y] = NULL;
        }
        tmp = tmp->suivant;
    }
}

void Get_coords_voisins(vector<pair<int, int>> *coords, int taille_sys, int x, int y)
{
    coords->push_back(make_pair(x, (y - 1 + taille_sys) % taille_sys));
    coords->push_back(make_pair(x, (y + 1) % taille_sys));
    coords->push_back(make_pair((x - 1 + taille_sys) % taille_sys, y));
    coords->push_back(make_pair((x + 1) % taille_sys, y));
}

void Humain_hote(int index_H, Humain **Liste_H, unsigned int PUISSANCE, float vitesse_mutation_ap)
{
    //* Déterminer si il y a déjà une immunité
    bool immunise = false;
    vector<unsigned int> liste_immunite = Liste_H[index_H]->Getimmune();
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    uniform_int_distribution<int> rand_int_size(0, 31);
    for (int j = 0; j < liste_immunite.size(); j++)
    {
        if (liste_immunite[j] == Liste_H[index_H]->GetgenomeAP())
        {
            immunise = true;
            Liste_H[index_H]->Setcontamine(false);
            Liste_H[index_H]->SetgenomeAP(0);
            break;
        }
    }
    if (!immunise)
    {
        //* Déterminer la probabilité de s'immuniser à ce tour (en fonction des génomes)
        float chance; // % entre 0 et 1
        //* Chance de se débarrasser du pathogène
        chance = Genome_Match(Liste_H[index_H]->GetgenomeH(), Liste_H[index_H]->GetgenomeAP(), PUISSANCE);

        float rand_f = rand_float(generator);
        if (rand_f < chance) // on se débarrasse du pathogène
        {
            //* Immune
            Liste_H[index_H]->Setcontamine(false);
            Liste_H[index_H]->Setimmune(Liste_H[index_H]->GetgenomeAP());
            Liste_H[index_H]->SetgenomeAP(0);
        }
        else // le pathogène reste
        {
            //* Le pathogène mute
            float rand_f = rand_float(generator);
            if (rand_f < vitesse_mutation_ap)
            {
                int index = rand_int_size(generator);
                Liste_H[index_H]->SetgenomeAP(Mutations_AP(Liste_H[index_H]->GetgenomeAP(), index));
            }
        }
    }
}

void Collision_H_AP(Humain **Liste_H, int index_H, node ***Pointer_array_AP, int x, int y, float CHARGE_VIRALE)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    if (Pointer_array_AP[x][y] != NULL)
    {
        if (!Liste_H[index_H]->Getcontamine()) // l'humain doit être sain pour être contaminé par ce pahogène
        {
            float rand_f = rand_float(generator);
            if (rand_f < CHARGE_VIRALE)
            {
                //* L'humain est contaminé par ce pathogène
                Liste_H[index_H]->Setcontamine(true);
                Liste_H[index_H]->SetgenomeAP(Pointer_array_AP[x][y]->AP.GetgenomeAP());
            }
        }
    }
}

void Analyse_voisinage(std::vector<std::pair<int, int>> *coordonnees, Humain ***Pointer_array_H, Humain **Liste_H, int index_H, float CHARGE_VIRALE)
{
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    for (int i = 0; i < coordonnees->size(); i++)
    {
        if (Pointer_array_H[coordonnees->at(i).first][coordonnees->at(i).second] != NULL) // un humain occupe cette case voisine
        {
            if (Pointer_array_H[coordonnees->at(i).first][coordonnees->at(i).second]->Getcontamine()) // ce voisin est contaminé
            {
                float rand_f = rand_float(generator);
                if (rand_f < CHARGE_VIRALE) // charge virale
                {
                    //* Notre humain a été infecté par ce voisin
                    Liste_H[index_H]->Setcontamine(true);
                    Liste_H[index_H]->SetgenomeAP(Pointer_array_H[coordonnees->at(i).first][coordonnees->at(i).second]->GetgenomeAP());
                }
            }
        }
    }
}
void Mouvement(Humain ***Pointer_array_H, node ***Pointer_array_AP, Linked_list *Liste_AP, float TRAINEE, std::vector<std::pair<int, int>> *coordonnees, int x, int y)
{
    uniform_int_distribution<int> randInt(0, 3);
    uniform_real_distribution<float> rand_float(0.0, 1.0);
    //* Choix d'une case voisine
    int choix = randInt(generator);
    //float r = rand_float(generator);
    //cout << r << endl;
    if (Pointer_array_H[coordonnees->at(choix).first][coordonnees->at(choix).second] == NULL) // cellule libre
    {
        //* Si l'individu est contaminé
        if (Pointer_array_H[x][y]->Getcontamine())
        {
            //* Déterminer si l'humain contamine la cellule qu'il quitte
            float rand_f = rand_float(generator);
            if (rand_f < TRAINEE)
            {
                //* Cellule contaminée (avant de bouger)
                if (Pointer_array_AP[x][y] != NULL)
                {
                    //* Un AP a déjà contaminé la cellule (on l'écrase)
                    Liste_AP->remove_element(Pointer_array_AP[x][y]);
                    Pointer_array_AP[x][y] = NULL;
                }
                Agent_Pathogene *AP;
                AP = new Agent_Pathogene();
                Pointer_array_AP[x][y] = Liste_AP->add_node(*AP);
                Pointer_array_AP[x][y]->AP.SetgenomeAP(Pointer_array_H[x][y]->GetgenomeAP());
                //* Sauver les coordonnées de l'agent pathogène dans ses attributs
                Pointer_array_AP[x][y]->AP.SetXAP(x);
                Pointer_array_AP[x][y]->AP.SetYAP(y);
            }
        }
        //* Mise à jour des coordonnées de l'humain
        Pointer_array_H[x][y]->SetXH(coordonnees->at(choix).first);
        Pointer_array_H[x][y]->SetYH(coordonnees->at(choix).second);
        //* Swap les pointeurs
        Pointer_array_H[coordonnees->at(choix).first][coordonnees->at(choix).second] = Pointer_array_H[x][y]; // le pointeur voisin pointe sur notre humain
        Pointer_array_H[x][y] = NULL;                                                                         // le pointeur actuel cesse de pointer sur notre humain
    }
}