#ifndef DEF_HUMAIN
#define DEF_HUMAIN

#include <iostream>
#include <string>

class Humain
{
public:
    Humain();
    ~Humain();
    bool Getcontamine();
    void Setcontamine(bool contamine);
    double GetgenomeH();
    void SetgenomeH(double genomeH);
    double GetgenomeAP();
    void SetgenomeAP(double genomeAP);
    int GetXH();
    void SetXH(int x);
    int GetYH();
    void SetYH(int y);

private:
    bool m_contamine;
    double m_genome_H;
    double m_genome_AP;
    int m_X;
    int m_Y;
};

#endif