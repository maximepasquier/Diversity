# Diversity

Automate cellulaire simulant la contamination d'une population par un agent pathogène en fonction de divers facteurs. Le travail se focalise sur l'impacte des diversités écologiques sur la propagation de pandémies.

Le système se présente sous forme d'une matrice carrée de taille configurable représentant une surface. Initialement sont disposés aléatoirement des individus sur  la surface. Leur nombre, ainsi que leurs caractéristiques sont configurables. Un agent pathogène est assigné à l'un d'eux afin d'obtenir un point de départ à la propagation du pathogène.

Les simulations évoluent par itérations et enregistrent les données dans des fichiers csv. Les résultats sont ensuite visualisables par des analyses faites en Python.

Le rapport du projet détaille tout les points couverts dans le travail et illustre les différents résultats.

## Installation

#### Code source

https://github.com/maximepasquier/Diversity

#### Méthode 1 : clone, fork

Cloner ou forker le projet sur votre machine.

#### Méthode 2 : Download ZIP

1. Télécharger le .zip du projet
2. Extraire le contenu

## Initialiser des simulations

Pour lancer des simulations ouvrez le fichier ./src/main.cpp et ajoutez une ou plusieurs instances de simulations comme montré ci-dessous :
```c++
threads.push_back(std::thread(thread_function, "./path_exemple"));
```
Modifiez le chemin spécifié "./path_exemple" qui est la racine de la simulation. Un fichier de configuration dois se trouver dans ce dossier.

## Configurer les paramètres
Dans le dossier que vous avez précisé dans l'initialisation de la simulation, vous devez créer le fichier : **config.txt**

Voici un exemple de son contenu :

```bash
TAILLE_SYSTEME = 400
NOMBRE_INDIVIDUS = 20000
ITERATIONS = 300
RERUN_LIMIT = 1000
FAIL_SEUIL = 10
GENOME_INIT_I = 65535
GENOME_DIVERSITY_I = 0
GENOME_INIT_AP = 0
VITESSE_MUTATIONS_AP = 0
CHARGE_VIRALE = 1
PARAMETRE_FONCTION = 4
CELLULE_AP = 0
SURVIE_AP = 0
NOMBRE_MOUVEMENT = 1000
PERFECT_MIX = false
TEMPS_AVANT_IMMUNITE = 1
IMMUNITE_MECANISME = true
RESISTANCE_MECANISME = false
```

Tous les paramètres du système sont listés et une valeur leur est assignée. Modifiez les valeurs afin de paramétrer votre simulation.

## Compiler

Après la modification du code il est nécessaire de compiler le programme.

```bash
cd emplacement/du/projet
```

Puis afin de compiler le projet (création d'un exécutable).

```bash
make compile
```

Cette dernière étape nécessite d'avoir un compilateur gcc installé.

## Run
Après avoir compilé et configuré les paramètres vous pouvez lancer la ou les simulations.

Retournez à la racine du projet :

```bash
cd emplacement/du/projet
```

Lancer la simulation :

```bash
make run
```
