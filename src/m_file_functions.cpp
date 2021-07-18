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
    m_nombre_contamine_file.close();
    m_nombre_AP_diff_file.close();
    m_times.close();
    m_SIR_recovered_file.close();
    m_X_mouvements_time.close();
    m_IX.close();
    m_IY.close();
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

    m_nombre_contamine_file.open(path_copy + "/m_nombre_contamine.csv", std::ios::app);
    m_nombre_AP_diff_file.open(path_copy + "/m_nombre_AP.csv", std::ios::app);
    m_SIR_recovered_file.open(path_copy + "/m_SIR_recovered_file.csv", std::ios::app);
    m_X_mouvements_time.open(path_copy + "/X_mouvements_time.csv", std::ios::app);
    m_IX.open(path_copy + "/IX.csv", std::ios::app);
    m_IY.open(path_copy + "/IY.csv", std::ios::app);
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
    m_nombre_contamine_file.open(path_copy + "/m_nombre_contamine.csv");
    m_nombre_AP_diff_file.open(path_copy + "/m_nombre_AP.csv");
    m_times.open(path_copy + "/times.csv");
    m_SIR_recovered_file.open(path_copy + "/m_SIR_recovered_file.csv");
    m_X_mouvements_time.open(path_copy + "/X_mouvements_time.csv");
    m_IX.open(path_copy + "/IX.csv");
    m_IY.open(path_copy + "/IY.csv");

    //* Init colonne names
    m_nombre_contamine_file << "Nombre de contaminés";
    m_nombre_AP_diff_file << "Nombre AP";
    m_SIR_recovered_file << "Recovered";
    m_X_mouvements_time << "X_mouvements";

    m_IX << "Individu_0";
    m_IY << "Individu_0";
    for (int i = 1; i < m_NOMBRE_INDIVIDUS; i++)
    {
        m_IX << ',' << "Individu_" << i;
        m_IY << ',' << "Individu_" << i;
    }

    //* Write to times.csv file
    m_times << "Init" << ',';
    m_times << "Run" << ',';
    m_times << "Mesures" << ',';
    m_times << "Close" << ',';
    m_times << "Total";
    m_times << '\n';

    //* Ferme les fichiers
    Close_files();
}

//* Mise à jour des fichiers csv à chaque itération
void Simulation::Update_csv()
{
    m_nombre_contamine_file << '\n'
                            << m_nombre_contamine;
    m_nombre_AP_diff_file << '\n'
                          << m_nombre_AP_diff;

//* Activation de la sauvegarde des coordonnées de tous les individus à chaque itération (très gourmand en mémoire !!!)
#if (0)
    // Vérifier si la personne est contaminé ou non
    int sign = 1;
    if (m_Liste_I[0]->Getcontamine())
    {
        sign = -1;
    }
    m_IX << '\n'
         << sign * (m_Liste_I[0]->GetXI() + 1);
    m_IY << '\n'
         << sign * (m_Liste_I[0]->GetYI() + 1);
    for (int i = 1; i < m_NOMBRE_INDIVIDUS; i++)
    {
        sign = 1;
        if (m_Liste_I[i]->Getcontamine())
        {
            sign = -1;
        }
        m_IX << ',' << sign * (m_Liste_I[i]->GetXI() + 1);
        m_IY << ',' << sign * (m_Liste_I[i]->GetYI() + 1);
    }
#endif
}