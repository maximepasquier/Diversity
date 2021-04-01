#include <iostream>
#include <chrono>
#include <string.h>
#include <sstream>
#include <thread>
#include <fstream>
#include <random>
#include <bitset>
#include <vector>

using namespace std;

void Knuth_Shuffle(int liste[], int taille)
{
    srand(time(NULL));
    for (int i = taille - 1; i > 0; i--)
    {
        int index = rand() % (i + 1);
        cout << "index : " << index << endl;
        int tmp = liste[i];
        liste[i] = liste[index];
        liste[index] = tmp;
    }
}

int main(int argc, char const *argv[])
{
    //* Read form config file
    ifstream config;
    config.open("/home/kilian/Documents/Automate_Cellulaire/Diversity/Configuration/config.txt");
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
                //cout << key << " : " << value << endl;
                file_data.push_back(make_pair(key, value));
            }
        }
    }

//* Déclaration des paramètres globaux
#if (1)
    int TAILLE_SYSTEME;          // largeur de la grille
    int NOMBRE_PERSONNES;        // nombre de personnes initialement (densité)
    int ITERATIONS;              // nombre d'itérations de la simulation
    unsigned int GENOME_INIT_H;  // unsigned char pour le génome humain initial
    int GENOME_DIVERSITY_H;      // diversité des génomes humains
    unsigned int GENOME_INIT_AP; // unsigned char pour le génome AP initial
    float VITESSE_MUTATIONS_AP;  // définit la vitesse à laquelle les pathogènes mutent
    float CHARGE_VIRALE;         // charge virale (niveau de contagion)

    for (int i = 0; i < file_data.size(); i++)
    {
        cout << file_data.at(i).first << " : " << file_data.at(i).second << endl;
        string key = file_data.at(i).first;
        if (key == "TAILLE_SYSTEME")
        {
            TAILLE_SYSTEME = stoi(file_data.at(i).second);
        }
        else if (key == "NOMBRE_PERSONNES")
        {
            NOMBRE_PERSONNES = stoi(file_data.at(i).second);
        }
        else if (key == "ITERATIONS")
        {
            ITERATIONS = stoi(file_data.at(i).second);
        }
        else if (key == "GENOME_INIT_H")
        {
            GENOME_INIT_H = stoul(file_data.at(i).second);
        }
        else if (key == "GENOME_DIVERSITY_H")
        {
            GENOME_DIVERSITY_H = stoi(file_data.at(i).second);
        }
        else if (key == "GENOME_INIT_AP")
        {
            GENOME_INIT_AP = stoul(file_data.at(i).second);
        }
        else if (key == "VITESSE_MUTATIONS_AP")
        {
            VITESSE_MUTATIONS_AP = stof(file_data.at(i).second);
        }
        else if (key == "CHARGE_VIRALE")
        {
            CHARGE_VIRALE = stof(file_data.at(i).second);
        }
    }
#endif

    cout << TAILLE_SYSTEME << " " << NOMBRE_PERSONNES << " " << ITERATIONS << " " << GENOME_INIT_H << " " << GENOME_DIVERSITY_H << " " << GENOME_INIT_AP << " " << VITESSE_MUTATIONS_AP << " " << CHARGE_VIRALE << endl;

    int n = 10;

    int liste[10]; // sorted list of consecutif int

    for (int i = 0; i < 10; i++)
    {
        liste[i] = i;
    }
    int taille = sizeof(liste) / sizeof(liste[0]);
    //cout << taille << endl;
    Knuth_Shuffle(liste, taille);

    for (int i = 0; i < 10; i++)
    {
        cout << i << " : " << liste[i] << endl;
    }
}