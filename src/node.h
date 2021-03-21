#ifndef NODE
#define NODE

#include <iostream>
#include "Agent_Pathogene.h"

struct node
{
    Agent_Pathogene AP;
    node *suivant;
    node *precedent;
};

#endif