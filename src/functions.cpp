#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include <bits/stdc++.h>

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
/*
int *permutation(int n)
{
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> rand_int(0, n - 1); // 0 et n-1 inclus !

    //* Générer une séquence de n entiers (0,n-1)
    int *liste;
    liste = (int *)malloc(n * sizeof(int));

    int liste1[n]; // sorted list of consecutif int
    for (int i = 0; i < n; i++)
    {
        liste1[i] = i;
    }

    //* Générer les indices permutés
    for (int i = 0; i < n; i++)
    {
        int nombre = rand_int(generator);
        int tmp;
        tmp = liste1[i];
        liste1[i] = liste1[nombre];
        liste1[nombre] = tmp;
    }
#if (1)
    for (int i = n - 1; i >= 0; i--)
    {
        int nombre = rand_int(generator);
        int tmp;
        tmp = liste1[i];
        liste1[i] = liste1[nombre];
        liste1[nombre] = tmp;
    }
#endif

    int count = 0;
    for (int i : liste1)
    {
        liste[count] = i;
        count += 1;
    }

    return liste;
}
*/

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
    //float chance = pow(distance, 4) / pow(8, 4);
    //cout << "distance : " << distance << ", chance : " << chance << endl;
    return pow(distance, puissance) / pow(sizeof(Genome_H)*8, puissance);
}

unsigned int Generate_Genome(int deviation, unsigned int init, int *rand_int_list_octet)
{
    unsigned int mask = 0;
    for (int i = 0; i < deviation; i++)
    {
        int index = rand_int_list_octet[i];
        //cout << nombre << " ";
        //mask += pow(2, nombre);
        mask += 1 << index;
    }
    //cout << endl;
    return init ^ mask;
}

unsigned int Mutations_AP(unsigned int genome_AP, int index)
{
    unsigned int mask = 0;
    //mask = pow(2, index);
    mask = 1 << index;
    return genome_AP ^ mask;
}