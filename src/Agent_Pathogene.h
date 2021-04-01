#ifndef DEF_AGENT_PATHOGENE
#define DEF_AGENT_PATHOGENE

#include <iostream>
#include <string>

class Agent_Pathogene
{
public:
    Agent_Pathogene();
    ~Agent_Pathogene();
    double GetgenomeAP();
    void SetgenomeAP(double genomeAP);

private:
    int m_genome_AP;
};

#endif