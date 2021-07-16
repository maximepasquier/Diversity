#include <algorithm>
#include <random>
#include "Individu.h"
#include "AP_linked_list_node.h"
#include "AP_linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

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

//* Compte le nombre de fois que les individus ont été contaminés
void Simulation::Nombre_de_fois_contamine()
{
    int somme_contaminations = 0;
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        somme_contaminations += m_Liste_I[i]->GetNombreDeFoisContamine();
    }
    m_nombre_de_fois_contamine_file << '\n'
                                    << (float)somme_contaminations / (float)m_NOMBRE_INDIVIDUS;
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