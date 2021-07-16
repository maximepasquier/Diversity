#include <math.h>
#include <algorithm>
#include <sstream>
#include <sys/stat.h>
#include "Simulation.h"

using namespace std;

//* Lecture du fichier config
void Simulation::Read_Configuration_file()
{
    /**
     * Lis le fichier config et le parse par le symbole "="
     * Nous avons donc des paires (clef,valeur) avec la clef 
     * étant la partie gauche du "=" et la valeur la partie
     * droite. Cette implémentation n'autorise pas les espaces !
     * Les paires sont ensuites push dans un vecteur.
     */
    ifstream config;
    string path_copy = m_configuration_file_path;
    path_copy.append("/config.txt");
    config.open(path_copy);
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
                string::iterator end_pos_key = remove(key.begin(), key.end(), ' ');
                key.erase(end_pos_key, key.end());
                string::iterator end_pos_value = remove(value.begin(), value.end(), ' ');
                value.erase(end_pos_value, value.end());
                m_configuration_file_data.push_back(make_pair(key, value));
            }
        }
    }
}

//* Ferme les fichiers csv
void Simulation::Close_files()
{
    m_nombre_echec_file.close();
    m_iteration_fin_simulation_file.close();
    m_max_contamines_file.close();
    m_iteration_max_contamines_file.close();
    m_taille_pandemie_file.close();
    m_nombre_AP_diff_file.close();
    m_nombre_de_fois_contamine_file.close();
}

//* Initialise les fichiers csv
void Simulation::File_init()
{
    //* Initialiser les fichier .csv
    Create_and_initialize_csv();
    //* Open .csv files to append
    Open_append_mode_csv();
}

//* Ouvre les fichier en mode append
void Simulation::Open_append_mode_csv()
{
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");

    m_nombre_echec_file.open(path_copy + "/m_nombre_echec_file.csv", std::ios::app);
    m_iteration_fin_simulation_file.open(path_copy + "/m_iteration_fin_simulation_file.csv", std::ios::app);
    m_max_contamines_file.open(path_copy + "/m_max_contamines_file.csv", std::ios::app);
    m_iteration_max_contamines_file.open(path_copy + "/m_iteration_max_contamines_file.csv", std::ios::app);
    m_taille_pandemie_file.open(path_copy + "/m_taille_pandemie_file.csv", std::ios::app);
    m_nombre_AP_diff_file.open(path_copy + "/m_nombre_AP_diff_file.csv", std::ios::app);
    m_nombre_de_fois_contamine_file.open(path_copy + "/m_nombre_de_fois_contamine_file.csv", std::ios::app);
}

//* Crée les fichiers csv et les initialise
void Simulation::Create_and_initialize_csv()
{
    /**
     * Récupère le path du projet
     * Crée un dossier qui va contenir les fichiers csv 
     */
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");
    const char *file_path = path_copy.c_str();
    int directory_fd = mkdir(file_path, 0777);

    //* Create
    m_nombre_echec_file.open(path_copy + "/m_nombre_echec_file.csv");
    m_iteration_fin_simulation_file.open(path_copy + "/m_iteration_fin_simulation_file.csv");
    m_max_contamines_file.open(path_copy + "/m_max_contamines_file.csv");
    m_iteration_max_contamines_file.open(path_copy + "/m_iteration_max_contamines_file.csv");
    m_taille_pandemie_file.open(path_copy + "/m_taille_pandemie_file.csv");
    m_nombre_AP_diff_file.open(path_copy + "/m_nombre_AP_diff_file.csv");
    m_nombre_de_fois_contamine_file.open(path_copy + "/m_nombre_de_fois_contamine_file.csv");

    //* Init colonne names
    m_nombre_echec_file << "Nombre_echec";
    m_iteration_fin_simulation_file << "Iteration_fin";
    m_max_contamines_file << "Max_contamines";
    m_iteration_max_contamines_file << "Iteration_max_contamines";
    m_taille_pandemie_file << "Taille de la pandémie";
    m_nombre_AP_diff_file << "Nombre AP";
    m_nombre_de_fois_contamine_file << "Individus";

    //* Ferme les fichiers
    Close_files();
}