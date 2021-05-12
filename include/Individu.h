#ifndef DEF_INDIVIDU
#define DEF_INDIVIDU

#include <vector>

/**
 * La classe individu désigne tous les hôtes potentiels pouvant 
 * contracter un agent pathogène. Il s'agit donc des individus
 * victimes de l'épidémie.
 * 
 * Un individu possède un état contaminé ou sain, un génome ainsi 
 * que celui d'un éventuel pathogène si contaminé, une liste de 
 * toutes ses immunités, des coordonnées donc un position sur la 
 * grille, une valeur de distance de Hamming avec le pathogène 
 * contracté si contaminé ainsi une valeur désignant le nombre de
 * fois que l'individu a été contaminé durant toute la simulation.
 */

class Individu
{
public:
    Individu();
    ~Individu();
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
    unsigned int m_genome_I;
    unsigned int m_genome_AP;
    std::vector<unsigned int> m_immune;
    int m_X;
    int m_Y;
    int m_hamming_distance;
    int m_nombre_de_fois_contamine;
};

#endif