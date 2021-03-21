#ifndef DEF_LINKED_LIST
#define DEF_LINKED_LIST

#include <iostream>
#include <string>
#include "node.h"
#include "Agent_Pathogene.h"

class Linked_list
{
public:
    Linked_list();
    node *add_node(Agent_Pathogene ap);
    void display();
    void remove_all();
    void remove_element(node *n);

private:
    node *head;
    node *tail;
};

#endif