#include "Individu.h"

Individu::Individu() : m_genome_I(0), m_genome_AP(0), m_contamine(false), m_X(0), m_Y(0), m_hamming_distance(0), m_nombre_de_fois_contamine(0)
{
}

Individu::~Individu() // déconstructeur
{
}

bool Individu::Getcontamine()
{
    return m_contamine;
}

void Individu::Setcontamine(bool contamine)
{
    m_contamine = contamine;
}

unsigned int Individu::GetgenomeH()
{
    return m_genome_I;
}

void Individu::SetgenomeH(unsigned int genome_I)
{
    m_genome_I = genome_I;
}

unsigned int Individu::GetgenomeAP()
{
    return m_genome_AP;
}

void Individu::SetgenomeAP(unsigned int genome_AP)
{
    m_genome_AP = genome_AP;
}

std::vector<unsigned int> Individu::Getimmune()
{
    return m_immune;
}

void Individu::Setimmune(unsigned int genome)
{
    m_immune.push_back(genome);
}

int Individu::GetXH()
{
    return m_X;
}

void Individu::SetXH(int x)
{
    m_X = x;
}

int Individu::GetYH()
{
    return m_Y;
}

void Individu::SetYH(int y)
{
    m_Y = y;
}

int Individu::GetHamming()
{
    return m_hamming_distance;
}

void Individu::SetHamming(int distance)
{
    m_hamming_distance = distance;
}

int Individu::GetNombreDeFoisContamine()
{
    return m_nombre_de_fois_contamine;
}

void Individu::IncrNombreDeFoisContamine()
{
    m_nombre_de_fois_contamine += 1;
}
