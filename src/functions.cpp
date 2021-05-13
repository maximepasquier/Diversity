#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <random>
#include "Individu.h"
#include "AP_linked_list.h"

using namespace std;

extern default_random_engine generator;

void Knuth_Shuffle(int *liste, int taille)
{
    uniform_int_distribution<int> rand_int(0,taille);
    for (int i = taille - 1; i > 0; i--)
    {
        int index = rand_int(generator) % (i + 1);
        int tmp = liste[i];
        liste[i] = liste[index];
        liste[index] = tmp;
    }
}

void Permutation(int *liste, int taille)
{
    for (int i = 0; i < taille; i++)
    {
        liste[i] = i;
    }
    Knuth_Shuffle(liste, taille);
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
float Genome_Match(int distance, int genome_size, unsigned int puissance)
{
    return pow(distance, puissance) / pow(genome_size * 8, puissance);
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
    return uint(genome_AP ^ mask);
}

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

void Print_ASCII_grid(int taille_sys, Individu ***Pointer_array_I, AP_linked_list_node ***Pointer_array_AP)
{
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

void Get_coords_voisins(vector<pair<int, int>> &coords, int taille_sys, int x, int y)
{  
    coords[0] = make_pair(x, (y - 1 + taille_sys) % taille_sys);
    coords[1] = make_pair(x, (y + 1) % taille_sys);
    coords[2] = make_pair((x - 1 + taille_sys) % taille_sys, y);
    coords[3] = make_pair((x + 1) % taille_sys, y);
}