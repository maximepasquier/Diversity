#include <iostream>
#include <chrono>
#include <string.h>
#include <sstream>
#include <thread>
#include <fstream>
#include <random>
#include <bitset>
#include <vector>
#include "Humain.h"
#include "Agent_Pathogene.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"

using namespace std;

int main(int argc, char const *argv[])
{
    //* Read from config file
    ifstream config;
    config.open("./Configuration/config.txt");
    string line;
    vector<pair<string, string>> file_data;
    while (getline(config, line))
    {
        istringstream is_line(line);
        string key;
        if (getline(is_line, key, '='))
        {
            string value;
            if (getline(is_line, value))
            {
                file_data.push_back(make_pair(key, value));
            }
        }
    }

    //* Déclaration des paramètres globaux
    int TAILLE_SYSTEME;          // largeur de la grille
    int NOMBRE_PERSONNES;        // nombre de personnes initialement (densité)
    int ITERATIONS;              // nombre d'itérations de la simulation
    unsigned int GENOME_INIT_H;  // unsigned char pour le génome humain initial
    int GENOME_DIVERSITY_H;      // diversité des génomes humains
    unsigned int GENOME_INIT_AP; // unsigned char pour le génome AP initial
    float VITESSE_MUTATIONS_AP;  // définit la vitesse à laquelle les pathogènes mutent
    float CHARGE_VIRALE;         // charge virale (niveau de contagion)
    unsigned int PUISSANCE;      // puissance des termes dans la fonction de génome match
    float TRAINEE;               // détermine la probabilité de contaminer une cellule
    float SURVIE_AP;             // probabilité que le pathogène contaminant une cellule reste en vie

    //* Assignation des paramètres globaux
    for (int i = 0; i < file_data.size(); i++)
    {
        string key = file_data.at(i).first;
        string value = file_data.at(i).second;
        if (key == "TAILLE_SYSTEME")
        {
            TAILLE_SYSTEME = stoi(value);
        }
        else if (key == "NOMBRE_PERSONNES")
        {
            NOMBRE_PERSONNES = stoi(value);
        }
        else if (key == "ITERATIONS")
        {
            ITERATIONS = stoi(value);
        }
        else if (key == "GENOME_INIT_H")
        {
            GENOME_INIT_H = stoul(value);
        }
        else if (key == "GENOME_DIVERSITY_H")
        {
            GENOME_DIVERSITY_H = stoi(value);
        }
        else if (key == "GENOME_INIT_AP")
        {
            GENOME_INIT_AP = stoul(value);
        }
        else if (key == "VITESSE_MUTATIONS_AP")
        {
            VITESSE_MUTATIONS_AP = stof(value);
        }
        else if (key == "CHARGE_VIRALE")
        {
            CHARGE_VIRALE = stof(value);
        }
        else if (key == "PUISSANCE")
        {
            PUISSANCE = stoul(value);
        }
        else if (key == "TRAINEE")
        {
            TRAINEE = stof(value);
        }
        else if (key == "SURVIE_AP")
        {
            SURVIE_AP = stof(value);
        }
    }

    //* Initialiser un générateur de nombres aléatoire
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    //* Générer les distributions et leur portée
    uniform_int_distribution<int> rand_int_taille_systeme(0, TAILLE_SYSTEME - 1); // 0 et TAILLE_SYSTEME inclus
    uniform_int_distribution<int> rand_int_size(0, 31);                           // rand sur la longueur d'un int
    uniform_real_distribution<float> rand_float(0.0, 1.0);                        // rand pour les probabilités

    //* Déclaration des matrices de pointeurs
    Humain *Pointer_array_H[TAILLE_SYSTEME][TAILLE_SYSTEME]; // pointeurs sur objets humains
    node *Pointer_array_AP[TAILLE_SYSTEME][TAILLE_SYSTEME];  // pointeurs sur objets agents pathogènes

    //* Déclaration des listes d'objets
    Humain Liste_H[NOMBRE_PERSONNES]; // liste de taille fixe
    Linked_list Liste_AP;             // création d'une instance de Linked_list

    //* Réinitialisation des matrices de pointeurs (NULL)
    for (int i = 0; i < TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j < TAILLE_SYSTEME; j++)
        {
            Pointer_array_H[i][j] = NULL;
            Pointer_array_AP[i][j] = NULL;
        }
    }

    //* Ajouter des objets humain
    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        //* Initaliser des génomes pour les humains
        int rand_int_list_octet[GENOME_DIVERSITY_H]; // indices des génomes à complémenter
        for (int j = 0; j < GENOME_DIVERSITY_H; j++)
        {
            rand_int_list_octet[j] = rand_int_size(generator); // générer aléatoirement des indices
        }
        Liste_H[i].SetgenomeH(Generate_Genome(GENOME_DIVERSITY_H, GENOME_INIT_H, rand_int_list_octet));
        //* Générer les indices [i][j] de la matrice de pointeurs
        while (1)
        {
            int ligne, colonne;
            ligne = rand_int_taille_systeme(generator);
            colonne = rand_int_taille_systeme(generator);
            //* Assigner un pointeur à chaque humain
            if (Pointer_array_H[ligne][colonne] == NULL) // pointeur libre
            {
                Pointer_array_H[ligne][colonne] = &Liste_H[i]; // assignation faite
                //* Enregistrer les coordonnées de l'humain dans ses attributs
                Liste_H[i].SetXH(ligne);
                Liste_H[i].SetYH(colonne);
                break;
            }
        }
    }

    //* Contaminer un humain (patient zéro)
    Liste_H[0].Setcontamine(true);
    Liste_H[0].SetgenomeAP(GENOME_INIT_AP);

    //* Initialiser les fichier .csv
    ofstream Humain_contamine, Humain_genomeAP, Humain_genomeH, Humain_hx, Humain_hy, Humain_immune;
    Humain_contamine.open("./data/Humain_contamine.csv");
    Humain_genomeAP.open("./data/Humain_genomeAP.csv");
    Humain_genomeH.open("./data/Humain_genomeH.csv");
    Humain_hx.open("./data/Humain_hx.csv");
    Humain_hy.open("./data/Humain_hy.csv");
    Humain_immune.open("./data/Humain_immune.csv");

    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        Humain_contamine << "Humain_" << i << ',';
        Humain_genomeAP << "Humain_" << i << ',';
        Humain_genomeH << "Humain_" << i << ',';
        Humain_hx << "Humain_" << i << ',';
        Humain_hy << "Humain_" << i << ',';
        Humain_immune << "Humain_" << i << ',';
    }
    Humain_contamine << '\n';
    Humain_genomeAP << '\n';
    Humain_genomeH << '\n';
    Humain_hx << '\n';
    Humain_hy << '\n';
    Humain_immune << '\n';

    Humain_contamine.close();
    Humain_genomeAP.close();
    Humain_genomeH.close();
    Humain_hx.close();
    Humain_hy.close();
    Humain_immune.close();

    //* Open .csv files to append
    Humain_contamine.open("./data/Humain_contamine.csv", std::ios::app);
    Humain_genomeAP.open("./data/Humain_genomeAP.csv", std::ios::app);
    Humain_genomeH.open("./data/Humain_genomeH.csv", std::ios::app);
    Humain_hx.open("./data/Humain_hx.csv", std::ios::app);
    Humain_hy.open("./data/Humain_hy.csv", std::ios::app);
    Humain_immune.open("./data/Humain_immune.csv", std::ios::app);

    //* Itérations
    for (int iteration = 0; iteration < ITERATIONS; iteration++)
    {
        //* Write to .csv file
        for (int i = 0; i < NOMBRE_PERSONNES; i++)
        {
            Humain_contamine << Liste_H[i].Getcontamine() << ',';
            Humain_genomeAP << Liste_H[i].GetgenomeAP() << ',';
            Humain_genomeH << Liste_H[i].GetgenomeH() << ',';
            Humain_hx << Liste_H[i].GetXH() << ',';
            Humain_hy << Liste_H[i].GetYH() << ',';
            vector<unsigned int> liste_immunite = Liste_H[i].Getimmune();
            int vsize = Liste_H[i].Getimmune().size();
            for (int j = 0; j < vsize; j++)
            {
                Humain_immune << liste_immunite[j] << ' ';
            }
            Humain_immune << ',';
        }
        Humain_contamine << '\n';
        Humain_genomeAP << '\n';
        Humain_genomeH << '\n';
        Humain_hx << '\n';
        Humain_hy << '\n';
        Humain_immune << '\n';

#if (1)
        //* Clear screen
        printf("\x1b[2J"); // clear screen
        printf("\x1b[H");  // returning the cursor to the home position

        //* Parcours du domaine pour l'affichage
        for (int i = 0; i < TAILLE_SYSTEME; i++)
        {
            for (int j = 0; j < TAILLE_SYSTEME; j++)
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
#endif

        //* Construire la permutations de la liste humain
        int liste[NOMBRE_PERSONNES]; // sorted list of consecutif int
        for (int i = 0; i < NOMBRE_PERSONNES; i++)
        {
            liste[i] = i;
        }
        int taille = sizeof(liste) / sizeof(liste[0]);
        Knuth_Shuffle(liste, taille);

        //* Parcours du domaine (liste agents pathogènes)
        node *tmp = Liste_AP.Get_head();
        while (tmp != NULL)
        {
            float rand_f = rand_float(generator);
            if (rand_f > SURVIE_AP)
            {
                //* Destruction de l'agent pathogène
                int x, y;
                x = tmp->AP.GetXAP();
                y = tmp->AP.GetYAP();
                Liste_AP.remove_element(Pointer_array_AP[x][y]);
                Pointer_array_AP[x][y] = NULL;
            }
            tmp = tmp->suivant;
        }

        //* Parcours du domaine (liste humains)
        for (int i = 0; i < NOMBRE_PERSONNES; i++)
        {
            int index_H, x, y;
            index_H = liste[i];
            x = Liste_H[index_H].GetXH();
            y = Liste_H[index_H].GetYH();
            vector<pair<int, int>> coordonnees; // vecteur de paire de int
            //* Push les coordonnées des 4 voisins
            coordonnees.push_back(make_pair(x, (y - 1 + TAILLE_SYSTEME) % TAILLE_SYSTEME));
            coordonnees.push_back(make_pair(x, (y + 1) % TAILLE_SYSTEME));
            coordonnees.push_back(make_pair((x - 1 + TAILLE_SYSTEME) % TAILLE_SYSTEME, y));
            coordonnees.push_back(make_pair((x + 1) % TAILLE_SYSTEME, y));

            //* Déterminer les cas
            if (Liste_H[index_H].Getcontamine()) //* contaminé
            {
                //* Déterminer si il y a déjà une immunité
                bool immunise = false;
                vector<unsigned int> liste_immunite = Liste_H[index_H].Getimmune();
                for (int j = 0; j < liste_immunite.size(); j++)
                {
                    if (liste_immunite[j] == Liste_H[index_H].GetgenomeAP())
                    {
                        immunise = true;
                        Liste_H[index_H].Setcontamine(false);
                        Liste_H[index_H].SetgenomeAP(0);
                        break;
                    }
                }
                if (!immunise)
                {
                    //* Déterminer la probabilité de s'immuniser à ce tour (en fonction des génomes)
                    float chance; // % entre 0 et 1
                    //* Chance de se débarrasser du pathogène
                    chance = Genome_Match(Liste_H[index_H].GetgenomeH(), Liste_H[index_H].GetgenomeAP(), PUISSANCE);

                    float rand_f = rand_float(generator);
                    if (rand_f < chance) // on se débarrasse du pathogène
                    {
                        //* Immune
                        Liste_H[index_H].Setcontamine(false);
                        Liste_H[index_H].Setimmune(Liste_H[index_H].GetgenomeAP());
                        Liste_H[index_H].SetgenomeAP(0);
                    }
                    else // le pathogène reste
                    {
                        //* Le pathogène mute
                        float rand_f = rand_float(generator);
                        if (rand_f < VITESSE_MUTATIONS_AP)
                        {
                            int index = rand_int_size(generator);
                            Liste_H[index_H].SetgenomeAP(Mutations_AP(Liste_H[index_H].GetgenomeAP(), index));
                        }
                    }
                }
            }
            else //* pas contaminé
            {
                //* Un AP se trouve sur la même cellule
                if (Pointer_array_AP[x][y] != NULL)
                {
                    if (!Liste_H[index_H].Getcontamine()) // l'humain doit être sain pour être contaminé par ce pahogène
                    {
                        float rand_f = rand_float(generator);
                        if (rand_f < CHARGE_VIRALE)
                        {
                            //* L'humain est contaminé par ce pathogène
                            Liste_H[index_H].Setcontamine(true);
                            Liste_H[index_H].SetgenomeAP(Pointer_array_AP[x][y]->AP.GetgenomeAP());
                        }
                    }
                }
                //* Analyse du voisinage
                for (int i = 0; i < coordonnees.size(); i++)
                {
                    if (Pointer_array_H[coordonnees.at(i).first][coordonnees.at(i).second] != NULL) // un humain occupe cette case voisine
                    {
                        if (Pointer_array_H[coordonnees.at(i).first][coordonnees.at(i).second]->Getcontamine()) // ce voisin est contaminé
                        {
                            float rand_f = rand_float(generator);
                            if (rand_f < CHARGE_VIRALE) // charge virale
                            {
                                //* Notre humain a été infecté par ce voisin
                                Liste_H[index_H].Setcontamine(true);
                                Liste_H[index_H].SetgenomeAP(Pointer_array_H[coordonnees.at(i).first][coordonnees.at(i).second]->GetgenomeAP());
                            }
                        }
                    }
                }
            }

            //* Mouvements
            uniform_int_distribution<int> randInt(0, 3);
            //* Choix d'une case voisine
            int choix = randInt(generator);
            if (Pointer_array_H[coordonnees.at(choix).first][coordonnees.at(choix).second] == NULL) // cellule libre
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
                            Liste_AP.remove_element(Pointer_array_AP[x][y]);
                            Pointer_array_AP[x][y] = NULL;
                        }
                        Agent_Pathogene *AP;
                        AP = new Agent_Pathogene();
                        Pointer_array_AP[x][y] = Liste_AP.add_node(*AP);
                        Pointer_array_AP[x][y]->AP.SetgenomeAP(Pointer_array_H[x][y]->GetgenomeAP());
                        //* Sauver les coordonnées de l'agent pathogène dans ses attributs
                        Pointer_array_AP[x][y]->AP.SetXAP(x);
                        Pointer_array_AP[x][y]->AP.SetYAP(y);
                    }
                }
                //* Mise à jour des coordonnées de l'humain
                Pointer_array_H[x][y]->SetXH(coordonnees.at(choix).first);
                Pointer_array_H[x][y]->SetYH(coordonnees.at(choix).second);
                //* Swap les pointeurs
                Pointer_array_H[coordonnees.at(choix).first][coordonnees.at(choix).second] = Pointer_array_H[x][y]; // le pointeur voisin pointe sur notre humain
                Pointer_array_H[x][y] = NULL;                                                                       // le pointeur actuel cesse de pointer sur notre humain
            }
        }
        //* Sleep (FPS)
        this_thread::sleep_for(chrono::seconds(1));
    }

    //* Close files
    Humain_contamine.close();
    Humain_genomeAP.close();
    Humain_genomeH.close();
    Humain_hx.close();
    Humain_hy.close();
    Humain_immune.close();

    //* Supprimer tous les objets agent_pathogene
    Liste_AP.remove_all();
    return 0;
}