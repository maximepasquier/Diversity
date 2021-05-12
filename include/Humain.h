#ifndef DEF_HUMAIN
#define DEF_HUMAIN

#include <iostream>
#include <string>
#include <vector>

class Humain
{
public:
    Humain();
    ~Humain();
    bool Getcontamine();
    void Setcontamine(bool contamine);
    unsigned int GetgenomeH();
    void SetgenomeH(unsigned int genomeH);
    unsigned int GetgenomeAP();
    void Setimmune(unsigned int genome);
    std::vector<unsigned int> Getimmune();
    void SetgenomeAP(unsigned int genomeAP);
    int GetXH();
    void SetXH(int x);
    int GetYH();
    void SetYH(int y);
    int GetHamming();
    void SetHamming(int distance);
    int GetNombreDeFoisContamine();
    void IncrNombreDeFoisContamine();
    void DecrNombreDeFoisContamine();

private:
    bool m_contamine;
    unsigned int m_genome_H;
    unsigned int m_genome_AP;
    std::vector<unsigned int> m_immune;
    int m_X;
    int m_Y;
    int m_hamming_distance;
    int m_nombre_de_fois_contamine;
};

#endif