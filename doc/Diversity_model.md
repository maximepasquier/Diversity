# Diversity

[TOC]

### Modèle implémentation résumé

##### Phase d’initialisation

L’initialisation se compose de trois parties : 

1. Read() : 
   1. Lecture du/des fichier/s de configuration 
   2. Assignation aux variables de l'instance
2. Set() : 
   1. Création des structures de données (objets + listes + matrices)
   2. Initialisation du modèle :
      1. Générer les diversité des génomes humains
      2. Disposer les humains sur la grille 2D
      3. Contaminer un humain
3. File_init() :
   1. Créer et initialiser les fichiers csv
   2. Ouvrir les fichiers csv en append mode

##### Phase de simulation

La simulation se déroule en trois phases :

1. Itérations() : *pour chaque itération on fait*
   1. Mettre à jour les fichiers csv avec l'état courant
   2. Générer une permutation des indices pour la mise à jour des humains
   3. **Mettre à jour tous les agents pathogènes contaminant les cellules (et non les personnes)**
   4. **Mettre à jour tous les humains**
2. Close_files() :
   1. Ferme tous les fichiers csv
3. Delete_obj() :
   1. Libère toute la mémoire des allocations sur le tas

#### Détails supplémentaires sur la phase : Itérations()

##### Mettre à jour tous les agents pathogènes contaminant les cellules (et non les personnes)

1. Itère parmi tous les agents pathogènes indépendants (contaminant une cellule et non un humain)
2. **m_Survie_AP** détermine la probabilité de survie de l'agent pathogène
   1. Cas 1 : le pathogène reste sur la cellule
   2. Cas 2 : le pathogène est détruit

##### Mettre à jour tous les humains

1. Itère parmi tous les humains du système en suivant une permutation aléatoire des indices
2. **Mettre à jour un humain**

##### Mettre à jour un humain

1. Récupérer les coordonnées de l'humain (connaître sa position)
2. Calculer les coordonnées des $4$ voisins
3. Déterminer les différents cas :
   1. Cas 1 : humain contaminé
      1. Match des génomes $\implies$ immunité ou éventuelle mutation du pathogène
   2. Cas 2 : humain sain
      1. Vérifie si l'humain se trouve sur une cellule contaminée
      2. Vérifie si les voisins sont contaminés
4. Mouvements :
   1. Essaie de se déplacer dans une direction aléatoire si cellule libre
   2. Si il y a déplacement, probabilité de contaminer le cellule que l'humain quitte