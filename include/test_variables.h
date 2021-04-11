#include "Humain.h"
#include "node.h"

void test_variables_coherence(int TAILLE_SYSTEME, int NOMBRE_PERSONNES, int ITERATIONS, unsigned int GENOME_INIT_H, int GENOME_DIVERSITY_H, unsigned int GENOME_INIT_AP, float VITESSE_MUTATIONS_AP, float CHARGE_VIRALE, unsigned int PUISSANCE, float TRAINEE, float SURVIE_AP);
void test_is_Pointer_array_to_null(int TAILLE_SYSTEME, Humain ***Pointer_array_H, node ***Pointer_array_AP);
void test_diversity_genome(Humain **Liste_H, int NOMBRE_PERSONNES, int GENOME_DIVERSITY_H, unsigned int GENOME_INIT_H);
void test_humain_coords_conflits(Humain **Liste_H, int NOMBRE_PERSONNES);