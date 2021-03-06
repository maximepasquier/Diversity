#include <algorithm>
#include <random>
#include "Individu.h"
#include "AP_linked_list_node.h"
#include "AP_linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

//* Compte le nombre de fois que les individus ont été contaminés
void Simulation::Nombre_de_fois_contamine()
{
    string path_copy = m_configuration_file_path;
    path_copy.append("/data_csv");

    m_nombre_de_fois_contamine_file.open(path_copy + "/m_nombre_de_fois_contamine_file.csv");

    m_nombre_de_fois_contamine_file << "Individus" << '\n';

    m_nombre_de_fois_contamine_file << m_Liste_I[0]->GetNombreDeFoisContamine();
    for (int i = 1; i < m_NOMBRE_INDIVIDUS; i++)
    {
        m_nombre_de_fois_contamine_file << '\n'
                                        << m_Liste_I[i]->GetNombreDeFoisContamine();
    }
}

//* Compte le nombre de contaminés
int Simulation::Update_infected_number()
{
    int infected_number = 0;
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        infected_number += int(m_Liste_I[i]->Getcontamine());
    }
    return infected_number;
}

//* Compte le nombre de pathogènes avec des génomes différents
int Simulation::Update_nombre_AP_diff()
{
    vector<unsigned int> genomes;
    genomes.reserve(2 * m_NOMBRE_INDIVIDUS);
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        if (m_Liste_I[i]->Getcontamine())
        {
            genomes.push_back(m_Liste_I[i]->GetgenomeAP());
        }
    }
    AP_linked_list_node *tmp = m_Liste_AP.Get_head();
    while (tmp != NULL)
    {
        genomes.push_back(tmp->AP.GetgenomeAP());
        tmp = tmp->suivant;
    }
    sort(genomes.begin(), genomes.end());
    int uniqueCount = unique(genomes.begin(), genomes.end()) - genomes.begin();
    return uniqueCount;
}

//* Compte le nombre d'indivdus recovered
int Simulation::SIR_recovered()
{
    int recovered = 0;
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        if (m_Liste_I[i]->Getimmune().size() > 0 && m_Liste_I[i]->Getcontamine() == false)
        {
            recovered += 1;
        }
    }
    return recovered;
}