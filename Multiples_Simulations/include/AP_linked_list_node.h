#ifndef AP_LINKED_LIST_NODE
#define AP_LINKED_LIST_NODE

#include "Agent_Pathogene.h"

/**
 * Cette structure contient les instances de noeuds de la liste des
 * agents pathogènes contaminant les cellules. Par conséquent,
 * une instance de cette classe représente un maillon de la
 * chaîne et contient un agent pathogène.
 * 
 * La structure qui est un maillon de la chaîne contient un 
 * agent pathogène ainsi que un lien sur le noeud précédent 
 * ainsi qu'un autre lien sur le noeud suivant.
 */
struct AP_linked_list_node
{
    Agent_Pathogene AP;
    AP_linked_list_node *suivant;
    AP_linked_list_node *precedent;
};

#endif