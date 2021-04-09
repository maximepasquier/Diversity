#include <iostream>
#include <chrono>
#include <string.h>
#include <sstream>
#include <thread>
#include <fstream>
#include <random>
#include <bitset>
#include <vector>

using namespace std;

int main()
{
    int NOMBRE_PERSONNES = 10000000;
    int liste[NOMBRE_PERSONNES]; // sorted list of consecutif int
    for (int i = 0; i < NOMBRE_PERSONNES; i++)
    {
        liste[i] = i;
    }
}