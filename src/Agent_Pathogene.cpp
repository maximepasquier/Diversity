#include "Agent_Pathogene.h"

using namespace std;

Agent_Pathogene::Agent_Pathogene() : m_genome_AP(999)
{

}

Agent_Pathogene::~Agent_Pathogene() // déconstructeur
{

}

double Agent_Pathogene::GetgenomeAP()
{
    return m_genome_AP;
}

void Agent_Pathogene::SetgenomeAP(double genomeAP)
{
    m_genome_AP = genomeAP;
}