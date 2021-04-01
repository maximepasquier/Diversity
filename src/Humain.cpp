#include "Humain.h"

using namespace std;

Humain::Humain() : m_genome_H(0), m_genome_AP(0), m_contamine(false), m_X(0), m_Y(0)
{

}

Humain::~Humain() // déconstructeur
{

}

bool Humain::Getcontamine()
{
    return m_contamine;
}

void Humain::Setcontamine(bool contamine)
{
    m_contamine = contamine;
}


unsigned int Humain::GetgenomeH()
{
    return m_genome_H;
}

void Humain::SetgenomeH(unsigned int genome_H)
{
    m_genome_H = genome_H;
}

unsigned int Humain::GetgenomeAP()
{
    return m_genome_AP;
}

void Humain::SetgenomeAP(unsigned int genome_AP)
{
    m_genome_AP = genome_AP;
}

std::vector<unsigned int> Humain::Getimmune()
{
    return m_immune;
}

void Humain::Setimmune(unsigned int genome)
{
    m_immune.push_back(genome);
}

int Humain::GetXH()
{
    return m_X;
}

void Humain::SetXH(int x)
{
    m_X = x;
}

int Humain::GetYH()
{
    return m_Y;
}

void Humain::SetYH(int y)
{
    m_Y = y;
}