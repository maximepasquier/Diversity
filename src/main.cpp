#include <iostream>
#include <chrono>
#include <string.h>
#include <thread>
#include <random>
#include <vector>
#include "Humain.h"
#include "Agent_Pathogene.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"

using namespace std;

/**
 * * Fonctionnement du modèle :
 * 
 * * Initialisation :
 * 1) Définir les paramètres globaux : taille du système, nombre de personnes dans le système (humain)
 * 2) Création des structures de données : matrices de pointeurs (sur humain ou pathogene), 
 *    liste fixe du nombre d'humains, liste doublement chainée pour les agents pathogènes (non fixe), 
 * 3) Placer les humains de la liste sur le domaine (aléatoirement)
 * 4) Enregistrer les coordonnées dans les attributs de l'humain
 * 5) Contaminer un humain 
 * * Itérations :
 * 1) Construire une permutations des indices de la liste des humains
 * 2) Itérer parmi les humain en suivant la permutation
 * * Pour chaque humain on fait (séquentiellement) :
 * 3) Récupérer les coordonnées de l'humain (attributs) 
 * 4) Déterminer les cas : humain déjà contaminé ou non
 * 5) Si non contaminé : analyse des 4 voisins directs 
 * 6) Mettre à jour ses attributs
 * 7) Phase de mouvement : regarder les disponibilités
 * 8) Mémoriser les possibilités et en choisir une aléatoirement
 * 9) Se déplacer
 *10) Passer au prochain humain 
 */

//* Paramètres globaux
#define TAILLE_SYSTEME 20   // largeur de le grille
#define NOMBRE_PERSONNES 50 // nombre de personnes initialement = densité

int main(int argc, char const *argv[])
{
    //* Générateur de nombres aléatoire
    unsigned int seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    //* Déclaration des matrices de pointeurs (sur le tas)
    static Humain *H_array[TAILLE_SYSTEME][TAILLE_SYSTEME]; // alloué statiquement sur le tas
    static node *AP_array[TAILLE_SYSTEME][TAILLE_SYSTEME];  // alloué statiquement sur le tas

    //* Déclaration des listes d'objets
    Humain Liste_H[NOMBRE_PERSONNES]; // liste de taille fixe
    Linked_list Liste_AP;             // création d'une instance de Linked_list

    //* Réinitialisation des matrices de pointeurs (NULL)
    for (int i = 0; i < TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j < TAILLE_SYSTEME; j++)
        {
            H_array[i][j] = NULL;
            AP_array[i][j] = NULL;
        }
    }

//* Ajouter des objets agent_pathogene
#if (0)
    Agent_Pathogene *AP;
    AP = new Agent_Pathogene();
    AP_array[3][3] = Liste_AP.add_node(*AP);
    AP = new Agent_Pathogene();
    AP_array[2][3] = Liste_AP.add_node(*AP);

    //* Supprimer des objets agent_pathogene
    Liste_AP.remove_element(AP_array[3][3]);
    AP_array[3][3] = NULL;
#endif

    //* Ajouter des objets humain
    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        //* Initaliser des génomes pour les humains
        Liste_H[i].SetgenomeH(888);
        //* Générer les indices [i][j] de la matrice de pointeurs
        while (1)
        {
            uniform_int_distribution<int> Initialiser_H(0, TAILLE_SYSTEME - 1); // 0 et TAILLE_SYSTEME inclus !
            int ligne, colonne;
            ligne = Initialiser_H(generator);
            colonne = Initialiser_H(generator);
            //* Assigner un pointeur à chaque humain
            if (H_array[ligne][colonne] == NULL) // pointeur libre
            {
                H_array[ligne][colonne] = &Liste_H[i]; // assignation faite
                //* Enregistrer les coordonnées de l'humain dans ses attributs
                Liste_H[i].SetXH(ligne);
                Liste_H[i].SetYH(colonne);
                break;
            }
        }
    }

    //* Contaminer un humain (patient zéro)
    Liste_H[0].Setcontamine(true);
    Liste_H[0].SetgenomeAP(333);

    //* Itérations
    for (int iteration = 0; iteration < 50; iteration++)
    {
        //* Clear screen
        printf("\x1b[2J"); // clear screen
        printf("\x1b[H");  // returning the cursor to the home position

        //* Parcours du domaine pour l'affichage
        for (int i = 0; i < TAILLE_SYSTEME; i++)
        {
            for (int j = 0; j < TAILLE_SYSTEME; j++)
            {
                if (H_array[i][j] != NULL) // la cellule pointe sur un humain !
                {
                    cout << H_array[i][j]->Getcontamine() << " ";
                }
                else // la cellule ne pointe pas sur un humain !
                {
                    cout << "- ";
                }
            }
            cout << endl;
        }

        //* Construire la permutations de la liste humain
        int *permu;
        permu = permutation(NOMBRE_PERSONNES);

        //* Parcours du domaine (liste humains)
        for (int i = 0; i < NOMBRE_PERSONNES; i++)
        {
            int index_H, x, y;
            index_H = *(permu + i); // indice de l'humain à considérer maintenant
            x = Liste_H[index_H].GetXH();
            y = Liste_H[index_H].GetYH();
            // H_array[x][y] pointe sur cet humain

            //* Déterminer les cas
            if (Liste_H[index_H].Getcontamine()) //* contaminé
            {
                if (Genome_Match(Liste_H[index_H].GetgenomeH(), Liste_H[index_H].GetgenomeAP()))
                {
                    // L'humain garde la pathogène et est donc contaminé
                }
                else
                {
                    // L'humain ne garde pas le pathogène et est donc immunisé à ce dernier
                }
            }
            else //* pas contaminé
            {
                //* Un AP se trouve sur la même cellule
                if (AP_array[x][y] != NULL)
                {
                    if (Genome_Match(Liste_H[index_H].GetgenomeH(), AP_array[x][y]->AP.GetgenomeAP()))
                    {
                        // L'humain est contaminé par ce pathogène
                        Liste_H[index_H].Setcontamine(true);
                        Liste_H[index_H].SetgenomeAP(AP_array[x][y]->AP.GetgenomeAP());
                    }
                    else
                    {
                        // L'humain n'est pas contaminé par ce pathogène
                    }
                }
                //* Analyse du voisinage
                if (y > 0)
                {
                    if (H_array[x][y - 1] != NULL) // un humain occupe cette case voisine
                    {
                        if (H_array[x][y - 1]->Getcontamine()) // ce voisin est contaminé
                        {
                            if (Genome_Match(Liste_H[index_H].GetgenomeH(), H_array[x][y - 1]->GetgenomeAP()))
                            {
                                // Notre humain a été infecté par ce voisin
                                Liste_H[index_H].Setcontamine(true);
                                Liste_H[index_H].SetgenomeAP(H_array[x][y - 1]->GetgenomeAP());
                            }
                        }
                    }
                }
                else
                {
                    if (H_array[x][TAILLE_SYSTEME - 1] != NULL)
                    {
                        if (H_array[x][TAILLE_SYSTEME - 1]->Getcontamine()) // ce voisin est contaminé
                        {
                            if (Genome_Match(Liste_H[index_H].GetgenomeH(), H_array[x][TAILLE_SYSTEME - 1]->GetgenomeAP()))
                            {
                                // Notre humain a été infecté par ce voisin
                                Liste_H[index_H].Setcontamine(true);
                                Liste_H[index_H].SetgenomeAP(H_array[x][TAILLE_SYSTEME - 1]->GetgenomeAP());
                            }
                        }
                    }
                }
                if (H_array[x][(y + 1) % TAILLE_SYSTEME] != NULL)
                {
                    if (H_array[x][(y + 1) % TAILLE_SYSTEME]->Getcontamine()) // ce voisin est contaminé
                    {
                        if (Genome_Match(Liste_H[index_H].GetgenomeH(), H_array[x][(y + 1) % TAILLE_SYSTEME]->GetgenomeAP()))
                        {
                            // Notre humain a été infecté par ce voisin
                            Liste_H[index_H].Setcontamine(true);
                            Liste_H[index_H].SetgenomeAP(H_array[x][(y + 1) % TAILLE_SYSTEME]->GetgenomeAP());
                        }
                    }
                }
                if (x > 0)
                {
                    if (H_array[x - 1][y] != NULL)
                    {
                        if (H_array[x - 1][y]->Getcontamine()) // ce voisin est contaminé
                        {
                            if (Genome_Match(Liste_H[index_H].GetgenomeH(), H_array[x - 1][y]->GetgenomeAP()))
                            {
                                // Notre humain a été infecté par ce voisin
                                Liste_H[index_H].Setcontamine(true);
                                Liste_H[index_H].SetgenomeAP(H_array[x - 1][y]->GetgenomeAP());
                            }
                        }
                    }
                }
                else
                {
                    if (H_array[TAILLE_SYSTEME - 1][y] != NULL)
                    {
                        if (H_array[TAILLE_SYSTEME - 1][y]->Getcontamine()) // ce voisin est contaminé
                        {
                            if (Genome_Match(Liste_H[index_H].GetgenomeH(), H_array[TAILLE_SYSTEME - 1][y]->GetgenomeAP()))
                            {
                                // Notre humain a été infecté par ce voisin
                                Liste_H[index_H].Setcontamine(true);
                                Liste_H[index_H].SetgenomeAP(H_array[TAILLE_SYSTEME - 1][y]->GetgenomeAP());
                            }
                        }
                    }
                }
                if (H_array[(x + 1) % TAILLE_SYSTEME][y] != NULL)
                {
                    if (H_array[(x + 1) % TAILLE_SYSTEME][y]->Getcontamine()) // ce voisin est contaminé
                    {
                        if (Genome_Match(Liste_H[index_H].GetgenomeH(), H_array[(x + 1) % TAILLE_SYSTEME][y]->GetgenomeAP()))
                        {
                            // Notre humain a été infecté par ce voisin
                            Liste_H[index_H].Setcontamine(true);
                            Liste_H[index_H].SetgenomeAP(H_array[(x + 1) % TAILLE_SYSTEME][y]->GetgenomeAP());
                        }
                    }
                }
            }

            //* Mouvements
            // Disponibilités des voisins
            vector<pair<int, int>> coordonnees; // vecteur de paire de int
            if (y > 0)
            {
                if (H_array[x][y - 1] == NULL)
                {
                    // cellule libre permettant un déplacement
                    coordonnees.push_back(make_pair(x, y - 1));
                }
            }
            else
            {
                if (H_array[x][TAILLE_SYSTEME - 1] == NULL)
                {
                    // cellule libre permettant un déplacement
                    coordonnees.push_back(make_pair(x, TAILLE_SYSTEME - 1));
                }
            }
            if (H_array[x][(y + 1) % TAILLE_SYSTEME] == NULL)
            {
                // cellule libe permettant un déplacement
                coordonnees.push_back(make_pair(x, (y + 1) % TAILLE_SYSTEME));
            }
            if (x > 0)
            {
                if (H_array[x - 1][y] == NULL)
                {
                    // cellule libre permettant un déplacement
                    coordonnees.push_back(make_pair(x - 1, y));
                }
            }
            else
            {
                if (H_array[TAILLE_SYSTEME - 1][y] == NULL)
                {
                    // cellule libre permettant un déplacement
                    coordonnees.push_back(make_pair(TAILLE_SYSTEME - 1, y));
                }
            }
            if (H_array[(x + 1) % TAILLE_SYSTEME][y] == NULL)
            {
                // cellule libe permettant un déplacement
                coordonnees.push_back(make_pair((x + 1) % TAILLE_SYSTEME, y));
            }
            //* Déplacement
            uniform_int_distribution<int> randInt(0, 3); // 0 et 3 inclus !
            int choix = coordonnees.size();
            if (choix > 0)
            {
                int index = randInt(generator) % choix;
                //* Mise à jour des coordonnées de l'humain
                H_array[x][y]->SetXH(coordonnees.at(index).first);
                H_array[x][y]->SetYH(coordonnees.at(index).second);
                //* Swap les pointeurs
                H_array[coordonnees.at(index).first][coordonnees.at(index).second] = H_array[x][y]; // le pointeur voisin pointe sur notre humain
                H_array[x][y] = NULL;                                                               // le pointeur actuel cesse de pointer sur notre humain
            }
        }
        //* Libérer la mémoire de l'allocation
        free(permu);
        //* Sleep (FPS)
        this_thread::sleep_for(chrono::seconds(2));
    }

    //* Supprimer tous les objets agent_pathogene
    //Liste_AP.remove_all();
    return 0;
}