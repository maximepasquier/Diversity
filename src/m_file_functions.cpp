#include <iostream>
#include <math.h>
#include <string>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"
#include "Simulation.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void Simulation::Read_Configuration_file()
{
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
                m_configuration_file_data.push_back(make_pair(key, value));
            }
        }
    }
}

void Simulation::Close_files_all_data()
{
    m_Humain_contamine.close();
    m_Humain_genomeAP.close();
    m_Humain_genomeH.close();
    m_Humain_hx.close();
    m_Humain_hy.close();
    m_Humain_immune.close();
    m_times.close();
    m_HammingDistance.close();
}

void Simulation::Close_files()
{
    m_nombre_contamine_file.close();
    m_nombre_AP_diff_file.close();
    m_times.close();
}

void Simulation::File_init_all_data()
{
    //* Initialiser les fichier .csv
    Create_and_initialize_csv_all_data();
    //* Open .csv files to append
    Open_append_mode_csv_all_data();
}

void Simulation::File_init()
{
    //* Initialiser les fichier .csv
    Create_and_initialize_csv();
    //* Open .csv files to append
    Open_append_mode_csv();
}

void Simulation::Open_append_mode_csv_all_data()
{
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");

    m_Humain_contamine.open(path_copy + "/Humain_contamine.csv", std::ios::app);
    m_Humain_genomeAP.open(path_copy + "/Humain_genomeAP.csv", std::ios::app);
    m_Humain_genomeH.open(path_copy + "/Humain_genomeH.csv", std::ios::app);
    m_Humain_hx.open(path_copy + "/Humain_hx.csv", std::ios::app);
    m_Humain_hy.open(path_copy + "/Humain_hy.csv", std::ios::app);
    m_Humain_immune.open(path_copy + "/Humain_immune.csv", std::ios::app);
    m_HammingDistance.open(path_copy + "/HammingDistance.csv", std::ios::app);
}

void Simulation::Open_append_mode_csv()
{
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");

    m_nombre_contamine_file.open(path_copy + "/m_nombre_contamine.csv", std::ios::app);
    m_nombre_AP_diff_file.open(path_copy + "/m_nombre_AP.csv", std::ios::app);
}

void Simulation::Create_and_initialize_csv_all_data()
{
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");
    const char *file_path = path_copy.c_str();
    int directory_fd = mkdir(file_path, 0777);

    m_Humain_contamine.open(path_copy + "/Humain_contamine.csv");
    m_Humain_genomeAP.open(path_copy + "/Humain_genomeAP.csv");
    m_Humain_genomeH.open(path_copy + "/Humain_genomeH.csv");
    m_Humain_hx.open(path_copy + "/Humain_hx.csv");
    m_Humain_hy.open(path_copy + "/Humain_hy.csv");
    m_Humain_immune.open(path_copy + "/Humain_immune.csv");
    m_times.open(path_copy + "/times.csv");
    m_HammingDistance.open(path_copy + "/HammingDistance.csv");

    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        m_Humain_contamine << "Humain_" << i;
        m_Humain_genomeAP << "Humain_" << i;
        m_Humain_genomeH << "Humain_" << i;
        m_Humain_hx << "Humain_" << i;
        m_Humain_hy << "Humain_" << i;
        m_Humain_immune << "Humain_" << i;
        m_HammingDistance << "Humain_" << i;

        if (i != m_NOMBRE_PERSONNES - 1)
        {
            m_Humain_contamine << ',';
            m_Humain_genomeAP << ',';
            m_Humain_genomeH << ',';
            m_Humain_hx << ',';
            m_Humain_hy << ',';
            m_Humain_immune << ',';
            m_HammingDistance << ',';
        }
    }
    //* Write to times.csv file

    m_times << "Init" << ',';
    m_times << "Run" << ',';
    m_times << "Iterations" << ',';
    m_times << "Update_csv" << ',';
    m_times << "Permutations" << ',';
    m_times << "Update_AP" << ',';
    m_times << "Update_H" << ',';
    m_times << "Coords" << ',';
    m_times << "Contamination_cases" << ',';
    m_times << "Mouvement" << ',';
    m_times << "Total" << ',';
    m_times << '\n';

    m_Humain_contamine << '\n';
    m_Humain_genomeAP << '\n';
    m_Humain_genomeH << '\n';
    m_Humain_hx << '\n';
    m_Humain_hy << '\n';
    m_Humain_immune << '\n';
    m_HammingDistance << '\n';

    Close_files_all_data();
}

void Simulation::Create_and_initialize_csv()
{
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");
    const char *file_path = path_copy.c_str();
    int directory_fd = mkdir(file_path, 0777);

    m_nombre_contamine_file.open(path_copy + "/m_nombre_contamine.csv");
    m_nombre_AP_diff_file.open(path_copy + "/m_nombre_AP.csv");
    m_times.open(path_copy + "/times.csv");
    m_nombre_contamine_file << "Nombre de contaminés";
    m_nombre_AP_diff_file << "Nombre AP";

    //* Write to times.csv file
    m_times << "Init" << ',';
    m_times << "Run" << ',';
    m_times << "Iterations" << ',';
    m_times << "Update_csv" << ',';
    m_times << "Permutations" << ',';
    m_times << "Update_AP" << ',';
    m_times << "Update_H" << ',';
    m_times << "Coords" << ',';
    m_times << "Contamination_cases" << ',';
    m_times << "Mouvement" << ',';
    m_times << "Total" << ',';
    m_times << '\n';

    Close_files();
}

void Simulation::Update_csv_all_data(int iteration)
{
    // char buff[64];
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        /*
        sprintf(buff, "%d,", m_Liste_H[i]->Getcontamine());
        m_Humain_contamine << buff;
        sprintf(buff, "%d,", m_Liste_H[i]->GetgenomeAP());
        m_Humain_genomeAP << buff;
        sprintf(buff, "%d,", m_Liste_H[i]->GetgenomeH());
        m_Humain_genomeH << buff;
        sprintf(buff, "%d,", m_Liste_H[i]->GetXH());
        m_Humain_hx << buff;
        sprintf(buff, "%d,", m_Liste_H[i]->GetYH());
        m_Humain_hy << buff;
        */

        m_Humain_contamine << m_Liste_H[i]->Getcontamine();
        if (m_Liste_H[i]->Getcontamine())
        {
            m_Humain_genomeAP << m_Liste_H[i]->GetgenomeAP();
            m_HammingDistance << m_Liste_H[i]->GetHamming();
        }
        else
        {
            m_Humain_genomeAP << NAN;
            m_HammingDistance << NAN;
        }
        m_Humain_genomeH << m_Liste_H[i]->GetgenomeH();
        m_Humain_hx << m_Liste_H[i]->GetXH();
        m_Humain_hy << m_Liste_H[i]->GetYH();

        vector<unsigned int> liste_immunite = m_Liste_H[i]->Getimmune();
        int vsize = m_Liste_H[i]->Getimmune().size();
        for (int j = 0; j < vsize; j++)
        {
            m_Humain_immune << liste_immunite[j] << ' ';
        }
        if (vsize == 0)
        {
            m_Humain_immune << NAN;
        }

        if (i != m_NOMBRE_PERSONNES - 1)
        {
            m_Humain_contamine << ',';
            m_Humain_genomeAP << ',';
            m_Humain_genomeH << ',';
            m_Humain_hx << ',';
            m_Humain_hy << ',';
            m_Humain_immune << ',';
            m_HammingDistance << ',';
        }
    }
    if (iteration != m_ITERATIONS - 1)
    {
        m_Humain_contamine << '\n';
        m_Humain_genomeAP << '\n';
        m_Humain_genomeH << '\n';
        m_Humain_hx << '\n';
        m_Humain_hy << '\n';
        m_Humain_immune << '\n';
        m_HammingDistance << '\n';
    }
}

void Simulation::Update_csv()
{
    m_nombre_contamine_file << '\n' << m_nombre_contamine;
    m_nombre_AP_diff_file << '\n' << m_nombre_AP_diff;
}