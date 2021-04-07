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

/*
void Pointer_array_to_NULL(int taille, Humain *Pointer_array_H[][], node *Pointer_array_AP[][])
{
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            //Pointer_array_H[i][j] = NULL;
            //Pointer_array_AP[i][j] = NULL;
            int a = 0;
        }
    }
}
*/