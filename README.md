# Diversity

Automate cellulaire simulant la contamination d'une population par un agent pathogène en fonction de divers facteurs. Le travail se focalise sur l'impacte des diversités des génomes sur la propagation de pandémies.

Le système se présente sous forme d'une matrice carrée de taille configurable représentant une surface. Initialement sont disposés des humains aléatoirement sur surface. Leur nombre, ainsi que leur caractéristiques sont configurables. Un agent pathogène est assigné à l'un d'eux afin d'obtenir un point de départ de la propagation du pathogène.

Chaque itération de la simulation se déroule en deux phases. La première est une étape de mise à jour permettant à chaque être humain du système de modifier ses variables internes et donc son état. La mise à jour s'effectue en considérant le voisinage ainsi que les attributs de l'individu. La deuxième est une phase de mouvement. A chaque itération, chaque être humain a la possibilité de se déplacer si cela est possible. 

## Installation

#### Code source

https://github.com/maximepasquier/Diversity

#### Méthode 1 : clone, fork

Cloner ou forker le projet sur votre machine.

#### Méthode 2 : Download ZIP

1. Télécharger le .zip du projet
2. Extraire le contenu

#### Méthode 3 : Docker

Nécessite d'avoir docker déjà installé.

```bash
docker run pasquiermaxime/diversity
```

La commande téléchargera l'image du projet ainsi que le compilateur **gcc** et exécutera le code automatiquement. 

## Compiler

Une fois le code source installé sur votre machine, ouvrez un terminal à la racine du projet.

```bash
cd emplacement/du/projet
```

Puis afin de compiler le projet (création d'un exécutable).

```bash
make compile
```

Cette dernière étape nécessite d'avoir un compilateur C++ installé.

## Configurer les paramètres
Dans le dossier **Configuration** se trouvant à la racine du projet vous trouverez un fichier : **config.txt**

Voici un exemple de son contenu :

```bash
TAILLE_SYSTEME=20			# taille de la matrice carrée
NOMBRE_PERSONNES=100		# nombre de personnes dans le système
ITERATIONS=20				# nombre d'itérations de la simulation
GENOME_INIT_H=0				# génome initial pour les humains
GENOME_DIVERSITY_H=1		# facteur de diversité appliqué au génome initial humain
GENOME_INIT_AP=0			# génome initial de l'unique agent pathogène
VITESSE_MUTATIONS_AP=0.01	# vitesse de mutation de l'agent pathogène
CHARGE_VIRALE=0.7			# facteur de contagion
PUISSANCE=5					# facteur de compatibilité entre humain et agent pathogène
TRAINEE=0.1					# facteur de probabilité de contamination de cellule
SURVIE_AP=0.8				# facteur de probabilité de survie d'un agent pathogène contaminant une cellule
```

Tous les paramètres du système sont listés et une valeur leur est assignée.

Modifiez les valeurs afin de paramétrer votre simulation. **Il est nécessaire de conserver la structure du fichier !** (ne pas inclure d'espaces)

Référez vous l'api pour davantage d'informations sur ces paramètres : 

```bash
cd emplacement/du/projet/Api
```

## Run
Après avoir compilé et configuré les paramètres vous pouvez lancer la simulation.

Retournez à la racine du projet :

```bash
cd emplacement/du/projet
```

Lancer la simulation :

```bash
make run
```