#include "Agent_Pathogene.h"

Agent_Pathogene::Agent_Pathogene()
{
}

Agent_Pathogene::~Agent_Pathogene() // déconstructeur
{
}

unsigned int Agent_Pathogene::GetgenomeAP()
{
    return m_genome_AP;
}

void Agent_Pathogene::SetgenomeAP(unsigned int genomeAP)
{
    m_genome_AP = genomeAP;
}

int Agent_Pathogene::GetXAP()
{
    return m_X;
}

void Agent_Pathogene::SetXAP(int x)
{
    m_X = x;
}
int Agent_Pathogene::GetYAP()
{
    return m_Y;
}

void Agent_Pathogene::SetYAP(int y)
{
    m_Y = y;
}