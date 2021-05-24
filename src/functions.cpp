#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <random>
#include "Individu.h"
#include "AP_linked_list.h"

using namespace std;

//extern default_random_engine generator;

//* Algirithme de shuffle
void Knuth_Shuffle(int *liste, int taille, default_random_engine generator)
{
    /**
     * Effectue un Knuth shuffle sur une liste passée par référence.
     * La liste doit être de longueur = taille. 
     */
    uniform_int_distribution<int> rand_int(0,taille);
    for (int i = taille - 1; i > 0; i--)
    {
        int index = rand_int(generator) % (i + 1);
        int tmp = liste[i];
        liste[i] = liste[index];
        liste[index] = tmp;
    }
}

//* Permutation de liste
void Permutation(int *liste, int taille, default_random_engine generator)
{
    /**
     * Initialise une liste passée par référence et le prépare
     * pour le Knuth_Shuffle 
     */
    for (int i = 0; i < taille; i++)
    {
        liste[i] = i;
    }
    Knuth_Shuffle(liste, taille, generator);
}

//* Caclul de distance de Hamming
int hammingDistance(unsigned int n1, unsigned int n2)
{
    /**
     * Calcul la distance de Hamming entre deux séquences (unsigned int).
     * Retourne un entier qui est le nombre de symboles différents
     * pour chaques indices des deux séquences. 
     */
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
float Genome_Match(int distance, int genome_size, unsigned int puissance)
{
    /**
     * Détermine la compatibilité entre deux génomes en fonction
     * de la distance de hamming, de la taille des génomes en bits ainsi
     * que d'un facteur puissance qui influence la sortie de la fonction. 
     */
    return pow(distance, puissance) / pow(genome_size * 8, puissance);
}

//* Génération de génomes pour les individus
unsigned int Generate_Genome(int deviation, unsigned int init, int *rand_int_list_octet)
{
    /**
     * Génère des génomes à partir d'un génome de référence (init)
     * Ce génome est le génome de base et nous venons complémenter 
     * un certain nombre de ces bits.
     * deviation = nombre de bits à complémenter
     * rand_int_list_octet = liste d'entiers aléatoires définissant 
     * les indies permutés. 
     */
    unsigned int mask = 0;
    for (int i = 0; i < deviation; i++)
    {
        int index = rand_int_list_octet[i];
        mask += 1 << index;
    }
    return init ^ mask;
}

//* Mutation d'un agent pathogène
unsigned int Mutations_AP(unsigned int genome_AP, int index)
{
    /**
     * Complémente un seul bit d'un génome d'un pathogène.
     * Le bit à l'indice (index) est complémenté 
     */
    unsigned int mask = 0;
    mask = 1 << index;
    return uint(genome_AP ^ mask);
}

//* Print l'avancement de la simulation
void Print_progression(int current_iteration, int total)
{
    printf("%c[2K", 27); // clear line
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

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

//* Print une grille ASCII montrant l'état du système à chaque itération
void Print_ASCII_grid(int taille_sys, Individu ***Pointer_array_I, AP_linked_list_node ***Pointer_array_AP)
{
    /**
     * L'affichage est sous forme d'une grille ASCII.
     * 0 = individu sain
     * 1 = individu contaminé
     * 2 = cellule contaminée par un agent pathogène
     * 02 = individus sain sur une cellule contaminée
     * 12 = individu contaminé sur une cellule déjà contaminée 
     */
    printf("\x1b[2J"); // clear screen
    printf("\x1b[H");  // returning the cursor to the home position

    //* Parcours du domaine pour l'affichage
    for (int i = 0; i < taille_sys; i++)
    {
        for (int j = 0; j < taille_sys; j++)
        {
            int count = 3;
            if (Pointer_array_I[i][j] != NULL) // la cellule pointe sur un humain !
            {
                cout << Pointer_array_I[i][j]->Getcontamine();
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