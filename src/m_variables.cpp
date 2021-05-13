#include "Individu.h"
#include "AP_linked_list.h"
#include "Simulation.h"

using namespace std;

void Simulation::Assign_variables()
{
    for (int i = 0; i < m_configuration_file_data.size(); i++)
    {
        string key = m_configuration_file_data.at(i).first;
        string value = m_configuration_file_data.at(i).second;
        if (key == "TAILLE_SYSTEME")
        {
            m_TAILLE_SYSTEME = stoi(value);
        }
        else if (key == "NOMBRE_PERSONNES")
        {
            m_NOMBRE_PERSONNES = stoi(value);
        }
        else if (key == "ITERATIONS")
        {
            m_ITERATIONS = stoi(value);
        }
        else if (key == "GENOME_INIT_H")
        {
            m_GENOME_INIT_H = stoul(value);
        }
        else if (key == "GENOME_DIVERSITY_H")
        {
            m_GENOME_DIVERSITY_H = stoi(value);
        }
        else if (key == "GENOME_INIT_AP")
        {
            m_GENOME_INIT_AP = stoul(value);
        }
        else if (key == "VITESSE_MUTATIONS_AP")
        {
            m_VITESSE_MUTATIONS_AP = stof(value);
        }
        else if (key == "CHARGE_VIRALE")
        {
            m_CHARGE_VIRALE = stof(value);
        }
        else if (key == "PUISSANCE")
        {
            m_PUISSANCE = stoul(value);
        }
        else if (key == "TRAINEE")
        {
            m_TRAINEE = stof(value);
        }
        else if (key == "SURVIE_AP")
        {
            m_SURVIE_AP = stof(value);
        }
    }
}

void Simulation::Set_Pointer_array()
{
    //* Déclaration des matrices de pointeurs pour les humains
    m_Pointer_array_I = new Individu **[m_TAILLE_SYSTEME];
    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        m_Pointer_array_I[i] = new Individu *[m_TAILLE_SYSTEME];
    }
    //* Déclaration des matrices de pointeurs pour les agents pathogènes
    m_Pointer_array_AP = new AP_linked_list_node **[m_TAILLE_SYSTEME];
    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        m_Pointer_array_AP[i] = new AP_linked_list_node *[m_TAILLE_SYSTEME];
    }
}

void Simulation::Set_Liste_H()
{
    m_Liste_I = new Individu *[m_NOMBRE_PERSONNES];
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        m_Liste_I[i] = new Individu;
    }
}

void Simulation::Delete_obj()
{
    for (int i = 0; i < m_NOMBRE_PERSONNES; i++)
    {
        delete m_Liste_I[i];
    }
    delete[] m_Liste_I;

    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j > m_TAILLE_SYSTEME; j++)
        {
            delete m_Pointer_array_I[i][j];
            delete m_Pointer_array_AP[i][j];
        }
        delete[] m_Pointer_array_I[i];
        delete[] m_Pointer_array_AP[i];   
    }
    delete[] m_Pointer_array_I;
    delete[] m_Pointer_array_AP;

    //* Supprimer tous les objets agent_pathogene
    m_Liste_AP.remove_all();
}

void Simulation::Pointer_array_to_NULL()
{
    for (int i = 0; i < m_TAILLE_SYSTEME; i++)
    {
        for (int j = 0; j < m_TAILLE_SYSTEME; j++)
        {
            m_Pointer_array_I[i][j] = NULL;
            m_Pointer_array_AP[i][j] = NULL;
        }
    }
}