#include <iostream>
#include <math.h>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

void Simulation::Read_Configuration_file()
{
    ifstream config;
    config.open(m_configuration_file_path);
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

void Simulation::Close_files()
{
    m_Humain_contamine.close();
    m_Humain_genomeAP.close();
    m_Humain_genomeH.close();
    m_Humain_hx.close();
    m_Humain_hy.close();
    m_Humain_immune.close();
}

void Simulation::File_init()
{
    //* Initialiser les fichier .csv
    Create_and_initialize_csv();
    //* Open .csv files to append
    Open_append_mode_csv();
}

void Simulation::Open_append_mode_csv()
{
    m_Humain_contamine.open("./data/Humain_contamine.csv", std::ios::app);
    m_Humain_genomeAP.open("./data/Humain_genomeAP.csv", std::ios::app);
    m_Humain_genomeH.open("./data/Humain_genomeH.csv", std::ios::app);
    m_Humain_hx.open("./data/Humain_hx.csv", std::ios::app);
    m_Humain_hy.open("./data/Humain_hy.csv", std::ios::app);
    m_Humain_immune.open("./data/Humain_immune.csv", std::ios::app);
}

void Simulation::Create_and_initialize_csv()
{
    m_Humain_contamine.open("./data/Humain_contamine.csv");
    m_Humain_genomeAP.open("./data/Humain_genomeAP.csv");
    m_Humain_genomeH.open("./data/Humain_genomeH.csv");
    m_Humain_hx.open("./data/Humain_hx.csv");
    m_Humain_hy.open("./data/Humain_hy.csv");
    m_Humain_immune.open("./data/Humain_immune.csv");

    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        m_Humain_contamine << "Humain_" << i << ',';
        m_Humain_genomeAP << "Humain_" << i << ',';
        m_Humain_genomeH << "Humain_" << i << ',';
        m_Humain_hx << "Humain_" << i << ',';
        m_Humain_hy << "Humain_" << i << ',';
        m_Humain_immune << "Humain_" << i << ',';
    }
    m_Humain_contamine << '\n';
    m_Humain_genomeAP << '\n';
    m_Humain_genomeH << '\n';
    m_Humain_hx << '\n';
    m_Humain_hy << '\n';
    m_Humain_immune << '\n';

    m_Humain_contamine.close();
    m_Humain_genomeAP.close();
    m_Humain_genomeH.close();
    m_Humain_hx.close();
    m_Humain_hy.close();
    m_Humain_immune.close();
}

void Simulation::Update_csv()
{
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        m_Humain_contamine << m_Liste_H[i]->Getcontamine() << ',';
        m_Humain_genomeAP << m_Liste_H[i]->GetgenomeAP() << ',';
        m_Humain_genomeH << m_Liste_H[i]->GetgenomeH() << ',';
        m_Humain_hx << m_Liste_H[i]->GetXH() << ',';
        m_Humain_hy << m_Liste_H[i]->GetYH() << ',';
        vector<unsigned int> liste_immunite = m_Liste_H[i]->Getimmune();
        int vsize = m_Liste_H[i]->Getimmune().size();
        for (int j = 0; j < vsize; j++)
        {
            m_Humain_immune << liste_immunite[j] << ' ';
        }
        m_Humain_immune << ',';
    }
    m_Humain_contamine << '\n';
    m_Humain_genomeAP << '\n';
    m_Humain_genomeH << '\n';
    m_Humain_hx << '\n';
    m_Humain_hy << '\n';
    m_Humain_immune << '\n';
}