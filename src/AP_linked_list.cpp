#include <iostream>
#include "AP_linked_list.h"

AP_linked_list::AP_linked_list()
{
    head = NULL;
    tail = NULL;
}
AP_linked_list_node *AP_linked_list::Get_head()
{
    return head;
}
AP_linked_list_node *AP_linked_list::add_node(Agent_Pathogene ap)
{
    AP_linked_list_node *tmp = new AP_linked_list_node;
    tmp->AP = ap;
    tmp->suivant = NULL;

    if (head == NULL)
    {
        head = tmp;
        tail = tmp;
        tmp->precedent = NULL;
    }
    else
    {
        tail->suivant = tmp;
        tmp->precedent = tail;
        tail = tmp;
    }
    return tmp;
}
void AP_linked_list::display()
{
    AP_linked_list_node *tmp = head;
    while (tmp != NULL)
    {
        std::cout << "Je suis : " << tmp << ", Précédent est : " << tmp->precedent << ", Suivant est : " << tmp->suivant << std::endl;
        tmp = tmp->suivant;
    }
}
void AP_linked_list::remove_all()
{
    AP_linked_list_node *tmp = head;
    while (tmp != NULL)
    {
        head = tmp->suivant; // faire que la head soit le prochain node
        delete tmp;          // delete l'objet courant et toutes ses données
        tmp = head;          // replacer le pointeur sur le nouveau début de la chaine
    }
}
void AP_linked_list::remove_element(AP_linked_list_node *n)
{
    AP_linked_list_node *precedent = n->precedent;
    AP_linked_list_node *suivant = n->suivant;

    if (precedent != NULL) // premier maillon
    {
        precedent->suivant = n->suivant;
    }
    else
    {
        head = n->suivant;
    }

    if (suivant != NULL) // dernier maillon
    {
        suivant->precedent = n->precedent;
    }
    else
    {
        tail = n->precedent;
    }
    delete n;
}