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