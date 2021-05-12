#include <iostream>
#include <math.h>
#include <algorithm>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

void Simulation::Nombre_de_fois_contamine()
{
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");

    m_nombre_de_fois_contamine_file.open(path_copy + "/m_nombre_de_fois_contamine_file.csv");

    m_nombre_de_fois_contamine_file << "Individu" << 0;
    for (int i = 1; i < m_NOMBRE_PERSONNES; i++)
    {
        m_nombre_de_fois_contamine_file << ",Individu" << i;
    }
    m_nombre_de_fois_contamine_file << '\n';

    m_nombre_de_fois_contamine_file << m_Liste_H[0]->GetNombreDeFoisContamine();
    for (int i = 1; i < m_NOMBRE_PERSONNES; i++)
    {
        m_nombre_de_fois_contamine_file << ',' << m_Liste_H[i]->GetNombreDeFoisContamine();
    }
}

int Simulation::Update_infected_number()
{
    int infected_number = 0;
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        infected_number += int(m_Liste_H[i]->Getcontamine());
    }
    return infected_number;
}

int Simulation::Update_nombre_AP_diff()
{
    vector<unsigned int> genomes;
    genomes.reserve(2 * m_NOMBRE_PERSONNES);
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        if (m_Liste_H[i]->Getcontamine())
        {
            genomes.push_back(m_Liste_H[i]->GetgenomeAP());
        }
    }
    node *tmp = m_Liste_AP.Get_head();
    while (tmp != NULL)
    {
        genomes.push_back(tmp->AP.GetgenomeAP());
        tmp = tmp->suivant;
    }

    //* Print all system AP
    /*
    for (vector<unsigned int>::const_iterator i = genomes.begin(); i != genomes.end(); ++i)
    {
        cout << *i << ' ';
    }
    cout << '\n';
    */

    sort(genomes.begin(), genomes.end());
    int uniqueCount = unique(genomes.begin(), genomes.end()) - genomes.begin();
    return uniqueCount;
}