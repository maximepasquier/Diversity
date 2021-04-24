#include <random>

float Genome_Match(int distance, int genome_size, unsigned int puissance);
unsigned int Generate_Genome(int deviation, unsigned int init, int *rand_int_list_octet);
unsigned int Mutations_AP(unsigned int genome_AP, int index);
int hammingDistance(unsigned int n1, unsigned int n2);
void Knuth_Shuffle(int *liste, int taille);
void Permutation(int *liste, int taille);
void Pointer_array_to_NULL(int taille, Humain ***Pointer_array_H, node ***Pointer_array_AP);
void Generate_human_genome_diversity(int nb_personnes, int genome_diversity_h, unsigned int genome_init_h, Humain **Liste_H);
void Add_human_obj_to_grid(int nb_personnes, int taille_systeme, Humain **Liste_H, Humain ***Pointer_array_H);
void Print_progression(int current_iteration, int total);
void Print_ASCII_grid(int taille, Humain ***Pointer_array_H, node ***Pointer_array_AP);
void Update_AP(Linked_list *Liste_AP, node ***Pointer_array_AP, float survie_ap);
void Get_coords_voisins(std::vector<std::pair<int, int>> &coords, int taille_sys, int x, int y);
void Humain_hote(int index_H, Humain **Liste_H, unsigned int PUISSANCE, float vitesse_mutation_ap);
void Collision_H_AP(Humain **Liste_H, int index_H, node ***Pointer_array_AP, int x, int y, float CHARGE_VIRALE);
void Analyse_voisinage(std::vector<std::pair<int, int>> *coordonnees, Humain ***Pointer_array_H, Humain **Liste_H, int index_H, float CHARGE_VIRALE);
void Mouvement(Humain ***Pointer_array_H, node ***Pointer_array_AP, Linked_list *Liste_AP, float TRAINEE, std::vector<std::pair<int, int>> *coordonnees, int x, int y);