#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

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

    int count = 0;
    for (int i : liste1)
    {
        liste[count] = i;
        count += 1;
    }

    return liste;
}

bool Genome_Match(double Genome_H, double Genome_AP)
{
    //* fake
    return true;
}