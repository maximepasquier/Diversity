#ifndef DEF_AGENT_PATHOGENE
#define DEF_AGENT_PATHOGENE

#include <iostream>
#include <string>

class Agent_Pathogene
{
public:
    Agent_Pathogene();
    ~Agent_Pathogene();
    int GetgenomeAP();
    void SetgenomeAP(int genomeAP);

    int GetXAP();
    void SetXAP(int x);
    int GetYAP();
    void SetYAP(int y);

private:
    int m_genome_AP;
    int m_X;
    int m_Y;
};

#endif