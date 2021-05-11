#include <iostream>
#include <math.h>
#include "Humain.h"
#include "node.h"
#include "Linked_list.h"
#include "functions.h"
#include "Simulation.h"

using namespace std;

extern default_random_engine generator;

int Simulation::Update_infected_number()
{
    int infected_number = 0;
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        infected_number += int(m_Liste_H[i]->Getcontamine());
    }
    return infected_number;
}