#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>
#include "Humain.h"
#include "node.h"

using namespace std;

void Knuth_Shuffle(int liste[], int taille)
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

void Generate_human_genome_diversity(int nb_personnes, int genome_diversity_h, unsigned int genome_init_h, default_random_engine generator, Humain **Liste_H)
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

void Add_human_obj_to_grid(int nb_personnes, int taille_systeme, Humain **Liste_H, Humain ***Pointer_array_H, std::default_random_engine generator)
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