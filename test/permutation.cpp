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

int main()
{

    int n = 10;
    int *permu;
    double table[n];
    for (int i = 0; i < n; i++)
    {
        table[i] = 0;
    }
    for (int j = 0; j < 1000000; j++)
    {
        permu = permutation(n);
        for (int i = 0; i < n; i++)
        {
            table[i] += *(permu + i);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << table[i] / 1000000 << endl;
    }

    return 0;
}