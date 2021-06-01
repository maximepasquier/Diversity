#include "Individu.h"

Individu::Individu() : m_contamine(false), m_pre_contamine(false), m_nombre_de_fois_contamine(0), m_temps_contamine(0)
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

bool Individu::Getprecontamine()
{
    return m_pre_contamine;
}

void Individu::Setprecontamine(bool pre_contamine)
{
    m_pre_contamine = pre_contamine;
}

unsigned int Individu::GetgenomeI()
{
    return m_genome_I;
}

void Individu::SetgenomeI(unsigned int genome_I)
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

int Individu::GetXI()
{
    return m_X;
}

void Individu::SetXI(int x)
{
    m_X = x;
}

int Individu::GetYI()
{
    return m_Y;
}

void Individu::SetYI(int y)
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

int Individu::GetTempsContamine()
{
    return m_temps_contamine;
}

void Individu::SetTempsContamine(int temps)
{
    m_temps_contamine = temps;
}

void Individu::IncrTempsContamine()
{
    m_temps_contamine += 1;
}
