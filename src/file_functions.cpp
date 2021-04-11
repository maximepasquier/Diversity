#include <bits/stdc++.h>
#include <algorithm>
#include <math.h>
#include <bits/stdc++.h>
#include <vector>
#include "Humain.h"

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

void Create_and_initialize_csv(ofstream &Humain_contamine, ofstream &Humain_genomeAP, ofstream &Humain_genomeH, ofstream &Humain_hx, ofstream &Humain_hy, ofstream &Humain_immune)
{
    Humain_contamine.open("./data/Humain_contamine.csv");
    Humain_genomeAP.open("./data/Humain_genomeAP.csv");
    Humain_genomeH.open("./data/Humain_genomeH.csv");
    Humain_hx.open("./data/Humain_hx.csv");
    Humain_hy.open("./data/Humain_hy.csv");
    Humain_immune.open("./data/Humain_immune.csv");

    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        Humain_contamine << "Humain_" << i << ',';
        Humain_genomeAP << "Humain_" << i << ',';
        Humain_genomeH << "Humain_" << i << ',';
        Humain_hx << "Humain_" << i << ',';
        Humain_hy << "Humain_" << i << ',';
        Humain_immune << "Humain_" << i << ',';
    }
    Humain_contamine << '\n';
    Humain_genomeAP << '\n';
    Humain_genomeH << '\n';
    Humain_hx << '\n';
    Humain_hy << '\n';
    Humain_immune << '\n';

    Humain_contamine.close();
    Humain_genomeAP.close();
    Humain_genomeH.close();
    Humain_hx.close();
    Humain_hy.close();
    Humain_immune.close();
}

void Open_append_mode_csv(ofstream &Humain_contamine, ofstream &Humain_genomeAP, ofstream &Humain_genomeH, ofstream &Humain_hx, ofstream &Humain_hy, ofstream &Humain_immune)
{
    Humain_contamine.open("./data/Humain_contamine.csv", std::ios::app);
    Humain_genomeAP.open("./data/Humain_genomeAP.csv", std::ios::app);
    Humain_genomeH.open("./data/Humain_genomeH.csv", std::ios::app);
    Humain_hx.open("./data/Humain_hx.csv", std::ios::app);
    Humain_hy.open("./data/Humain_hy.csv", std::ios::app);
    Humain_immune.open("./data/Humain_immune.csv", std::ios::app);
}

void Update_csv(int NOMBRE_PERSONNES, Humain **Liste_H, std::ofstream &Humain_contamine, std::ofstream &Humain_genomeAP, std::ofstream &Humain_genomeH, std::ofstream &Humain_hx, std::ofstream &Humain_hy, std::ofstream &Humain_immune)
{
    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        Humain_contamine << Liste_H[i]->Getcontamine() << ',';
        Humain_genomeAP << Liste_H[i]->GetgenomeAP() << ',';
        Humain_genomeH << Liste_H[i]->GetgenomeH() << ',';
        Humain_hx << Liste_H[i]->GetXH() << ',';
        Humain_hy << Liste_H[i]->GetYH() << ',';
        vector<unsigned int> liste_immunite = Liste_H[i]->Getimmune();
        int vsize = Liste_H[i]->Getimmune().size();
        for (int j = 0; j < vsize; j++)
        {
            Humain_immune << liste_immunite[j] << ' ';
        }
        Humain_immune << ',';
    }
    Humain_contamine << '\n';
    Humain_genomeAP << '\n';
    Humain_genomeH << '\n';
    Humain_hx << '\n';
    Humain_hy << '\n';
    Humain_immune << '\n';
}

void Close_files(std::ofstream &Humain_contamine, std::ofstream &Humain_genomeAP, std::ofstream &Humain_genomeH, std::ofstream &Humain_hx, std::ofstream &Humain_hy, std::ofstream &Humain_immune)
{
    Humain_contamine.close();
    Humain_genomeAP.close();
    Humain_genomeH.close();
    Humain_hx.close();
    Humain_hy.close();
    Humain_immune.close();
}