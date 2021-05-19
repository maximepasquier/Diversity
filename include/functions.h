/**
 * Les fichiers "functions" contiennent toutes les fonctions
 * n'étant pas directement liée aux classes du programme.
 * Il y figure donc toutes les fonction à usage universel.
 */

float Genome_Match(int distance, int genome_size, unsigned int puissance);
unsigned int Generate_Genome(int deviation, unsigned int init, int *rand_int_list_octet);
unsigned int Mutations_AP(unsigned int genome_AP, int index);
int hammingDistance(unsigned int n1, unsigned int n2);
void Knuth_Shuffle(int *liste, int taille);
void Permutation(int *liste, int taille);
void Print_progression(int current_iteration, int total);
void Print_ASCII_grid(int taille, Individu ***Pointer_array_I, AP_linked_list_node ***Pointer_array_AP);
void Get_coords_voisins(std::vector<std::pair<int, int>> &coords, int taille_sys, int x, int y);