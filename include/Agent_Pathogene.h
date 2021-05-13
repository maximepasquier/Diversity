#ifndef DEF_AGENT_PATHOGENE
#define DEF_AGENT_PATHOGENE

/**
 * La classe Agent_Pathogène regroupe tout les agents pathogènes
 * contaminant des cellule. Dès qu'un individu contamine une cellule,
 * l'agent pathogène contanu dans ce dernier se duplique et se dépose
 * sur la cellule. Quand cela se produit, nous créons une nouvelle 
 * instance de cette classe.
 * 
 * Un agent pathogène contaminant un espace et non un individu
 * possède un génome ainsi que des coordonnées sur la grille
 * définissant sa position.  
 */

class Agent_Pathogene
{
public:
    Agent_Pathogene();
    ~Agent_Pathogene();
    unsigned int GetgenomeAP();
    void SetgenomeAP(unsigned int genomeAP);

    int GetXAP();
    void SetXAP(int x);
    int GetYAP();
    void SetYAP(int y);

private:
    unsigned int m_genome_AP;
    int m_X;
    int m_Y;
};

#endif