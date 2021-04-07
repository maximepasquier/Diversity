#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

extern int TAILLE_SYSTEME;          // largeur de la grille
extern int NOMBRE_PERSONNES;        // nombre de personnes initialement (densité)
extern int ITERATIONS;              // nombre d'itérations de la simulation
extern unsigned int GENOME_INIT_H;  // unsigned char pour le génome humain initial
extern int GENOME_DIVERSITY_H;      // diversité des génomes humains
extern unsigned int GENOME_INIT_AP; // unsigned char pour le génome AP initial
extern float VITESSE_MUTATIONS_AP;  // définit la vitesse à laquelle les pathogènes mutent
extern float CHARGE_VIRALE;         // charge virale (niveau de contagion)
extern unsigned int PUISSANCE;      // puissance des termes dans la fonction de génome match
extern float TRAINEE;               // détermine la probabilité de contaminer une cellule
extern float SURVIE_AP;             // probabilité que le pathogène contaminant une cellule reste en vie

void Read_Configuration_file(string configuration_file_path, vector<pair<string, string>> &file_data)
{
    ifstream config;
    config.open(configuration_file_path);
    string line;
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
}

void Assign_global_variables(vector<pair<string, string>> &configuration_file_data)
{
    for (int i = 0; i < configuration_file_data.size(); i++)
    {

        string key = configuration_file_data.at(i).first;
        string value = configuration_file_data.at(i).second;
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
}