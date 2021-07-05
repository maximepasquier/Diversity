#include <string>
#include "Individu.h"
#include "AP_linked_list.h"
#include "Simulation.h"

using namespace std;

//* Traduction des informations du fichier congif en variables
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
        else if (key == "NOMBRE_INDIVIDUS")
        {
            m_NOMBRE_INDIVIDUS = stoi(value);
        }
        else if (key == "ITERATIONS")
        {
            m_ITERATIONS = stoi(value);
        }
        else if (key == "GENOME_INIT_I")
        {
            m_GENOME_INIT_I = stoul(value);
        }
        else if (key == "GENOME_DIVERSITY_I")
        {
            m_GENOME_DIVERSITY_I = stoi(value);
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
        else if (key == "PARAMETRE_FONCTION")
        {
            m_PARAMETRE_FONCTION = stoul(value);
        }
        else if (key == "CELLULE_AP")
        {
            m_CELLULE_AP = stof(value);
        }
        else if (key == "SURVIE_AP")
        {
            m_SURVIE_AP = stof(value);
        }
        else if (key == "NOMBRE_MOUVEMENT")
        {
            m_NOMBRE_MOUVEMENT = stoi(value);
        }
        else if (key == "TEMPS_AVANT_IMMUNITE")
        {
            m_TEMPS_AVANT_IMMUNITE = stoi(value);
        }
        else if (key == "RERUN_LIMIT")
        {
            m_RERUN_LIMIT = stoi(value);
        }
        else if (key == "FAIL_SEUIL")
        {
            m_FAIL_SEUIL = stoi(value);
        }
        else if (key == "PERFECT_MIX")
        {
            if (value.compare("true") == 0)
            {
                m_PERFECT_MIX = true;
            }
            if (value.compare("false") == 0)
            {
                m_PERFECT_MIX = false;
            }
        }
        else if (key == "IMMUNITE_MECANISME")
        {
            if (value.compare("true") == 0)
            {
                m_IMMUNITE_MECANISME = true;
            }
            if (value.compare("false") == 0)
            {
                m_IMMUNITE_MECANISME = false;
            }
        }
        else if (key == "RESISTANCE_MECANISME")
        {
            if (value.compare("true") == 0)
            {
                m_RESISTANCE_MECANISME = true;
            }
            if (value.compare("false") == 0)
            {
                m_RESISTANCE_MECANISME = false;
            }
        }
    }
}

//* Allocation des matrices (représentation spatiale)
void Simulation::Set_Pointer_array()
{
    //* Déclaration des matrices de pointeurs pour les individus
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

//* Création de la liste contanant tous les individus
void Simulation::Set_Liste_I()
{
    m_Liste_I = new Individu *[m_NOMBRE_INDIVIDUS];
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
    {
        m_Liste_I[i] = new Individu;
    }
}

//* Suppression des allocations sur le tas
void Simulation::Delete_obj()
{
    for (int i = 0; i < m_NOMBRE_INDIVIDUS; i++)
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

//* Initialise les matrices de pointeurs à NULL
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