#include "Linked_list.h"

using namespace std;

Linked_list::Linked_list()
{
    head = NULL;
    tail = NULL;
}
node *Linked_list::Get_head()
{
    return head;
}
node *Linked_list::add_node(Agent_Pathogene ap)
{
    node *tmp = new node;
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
void Linked_list::display()
{
    node *tmp = head;
    while (tmp != NULL)
    {
        cout << "Je suis : " << tmp << ", Précédent est : " << tmp->precedent << ", Suivant est : " << tmp->suivant << endl;
        tmp = tmp->suivant;
    }
}
void Linked_list::remove_all()
{
    node *tmp = head;
    while (tmp != NULL)
    {
        head = tmp->suivant; // faire que la head soit le prochain node
        delete tmp;          // delete l'objet courant et toutes ses données
        tmp = head;          // replacer le pointeur sur le nouveau début de la chaine
    }
}
void Linked_list::remove_element(node *n)
{
    node *precedent = n->precedent;
    node *suivant = n->suivant;

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