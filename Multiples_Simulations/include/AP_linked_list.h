#ifndef DEF_AP_LINKED_LIST
#define DEF_AP_LINKED_LIST

#include "AP_linked_list_node.h"
#include "Agent_Pathogene.h"

/**
 * Cette classe peut initaliser des listes doublement chaînées.
 * Les noeuds de la chaîne servent à contenir les objects
 * "Agent_Pathogene". Donc il s'agit des agents pathogènes
 * contaminant des cellules et non des individus.
 * 
 * Une instance de cette classe est donc une liste de pathogènes.
 * Cette instance contient un pointeur sur le début ainsi que 
 * sur la fin de la chaîne pour pouvoir la parcourir. De plus
 * la classe a des méthodes pour afficher, ajouter, retirer,
 * effacer le contenu ainsi qu'une méthode pour récupérer le
 * premier élément de la chaîne.
 */
class AP_linked_list
{
public:
    AP_linked_list();
    AP_linked_list_node *add_node(Agent_Pathogene ap);
    void display();
    void remove_all();
    void remove_element(AP_linked_list_node *n);
    AP_linked_list_node *Get_head();

private:
    AP_linked_list_node *head;
    AP_linked_list_node *tail;
};

#endif