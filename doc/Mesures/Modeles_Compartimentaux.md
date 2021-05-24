# Modèles compartimentaux

Les modèles compartimentaux sont une catégorie de modèles mathématiques permettant de représenter l'évolution de maladies infectieuses au sein d'une population. Ces modèles épidémiologiques se basent sur la notion de classes épidémiologiques et de transitions entre ces différentes classes. Nous appelons ces classes des **compartiments** et les transitions entre les classes les **règles**. Un compartiment est un état possible dans lequel les acteurs du système peuvent se trouver. Chaque acteur du système se trouve à tous moment dans un compartiment et ce dernier définit son état. Une règle est une fonction de transition entre les compartiments. Les acteurs changent de compartiments lorsque leur état change. Nous pouvons donc définir des règles permettant de changer de compartiment.

Il existe $7$ type de compartiments différents. Le premier compartiment est $S$ et représente tous les individus sains du système. Le second est $I$ et désigne tous les acteurs contaminés. Le troisième est un compartiment de transition entre $S$ et $I$ et représente une période de latence. En effet, suivant les maladies il se peut qu'un acteur sain ne devienne pas directement contaminé après un contact positif. Le quatrième compartiment est $D$ et symbolise les individus morts. Le cinquième est $R$ pour "recovered" et inclut tous les individus qui ont développé une immunité suite à une période infecté. Le sixième compartiment est le compartiment $M$ et reflète ce que nous avons appelé "résistance naturelle" dans le modèle. C'est-à-dire le groupe d'individus naturellement insensible au pathogène. Finalement le dernier compartiment est $C$ et illustre les individus asymptotiques, c'est-à-dire les hôtes contaminés qui ne présentent aucun symptômes et semblent donc sains.

Le modèle actuel n'implémente pas tous les compartiments mais uniquement trois d'entre eux. Nous n'étudierons que les compartiments $S$, $I$ et $R$. Les règles dépendent du modèle et sont toutes explicités dans la description du modèle.

L'objectif de ce chapitre est valider le notre modèle sur les bases des modèles compartimentaux. Il s'agit donc de déterminer les paramètres du modèle afin d'observer des résultats suivant ces modèles. Les modèles compartimentaux sont des modèles mathématiques représentant l'évolution de pandémies et on prouvé leur validité par le passé. Pour tester notre implémentation du modèle, il est essentiel de le comparer à des résultats déjà prouvés. Dans ce chapitre, nous allons essayer de reproduire les résultats fournis par ces modèles bien connus et allons appliquer des variations sur les paramètres du modèle pour en constater l'impact.

### Modèle SI

Le modèle SI est le modèle épidémiologique le plus simple. Nous avons deux classes d'individus, les individus sains ($S$) et les individus contaminées ($I$). Les deux compartiments sont les seuls états possibles pour les acteurs du système. Cela signifie que les individus ne peuvent pas s'immuniser ou guérir. 

Initialement tous les individus sont dans le compartiment $S$ car tout le monde est sain. Pour lancer la simulation, nous infectons un individus. Par conséquent il passe dans le second compartiment $I$. Il s'agit ensuite d'étudier l'évolution du système.

Le modèle SI est décrit mathématiques par les équations différentielles ordinaires suivantes :
$$
\frac{dS}{dt}=-\frac{\beta S I}{N}\\
\frac{dI}{dt}=\frac{\beta S I}{N}
$$
La variable $N$ comptabilise tout la population d'individus de tous les compartiments confondus, par conséquent $N=S+I$. Le facteur $\beta$ est une valeur définie entre $0$ et $1$ et déterminant le taux d'infection du modèle. 

Les équations différentielles s'implémentent dans python de la manière suivante :

```python
S, I = S - beta * ((S * I / N)), I + beta * ((S * I) / N)
```

Python intègre un moyen de modifier simultanément plusieurs variables utilisé ci-dessus. Le compartiment $S$ du modèle ne fait que décroître et au contraire le compartiment $I$ ne fait qu'augmenter afin de conserver le total $N=S+I$. La modification du nombre d'individus par compartiment s'effectue en un certain nombre de pas représentant un écoulement dans le temps. Dans notre simulation ce sont les itérations qui font office de représentation temporelle.

Un modèle SI avec une population de $100$ individus, $99$ dans le compartiment $S$ et $1$ dans le compartiment $I$ avec un taux $\beta = 0.3$  et déroulé sur $40$ étapes, nous obtenons le graphique suivant.![SI_model](/home/maxime/Documents/Automate_Cellulaire/Diversity/Python/SI_model.png)

### Modèle SIR

Les modèles compartimentaux SIR sont comparables aux modèles SI sauf qu'ils ont un compartiment supplémentaire $R$ incluant tous les individus guéris. Initialement les individus commencent dans le compartiment $S$ et passent dans le compartiment $I$ si ils sont contaminés. Après une certaine période étant contaminés ils peuvent développer une immunité au pathogène et guérir. Tout individus développant une immunité à la maladie passe dans le dernier compartiment $R$. Ce modèle possède les même paramètres que le modèle SI avec l'ajout d'une variable $\gamma$ comprise entre $0$ et $1$ et définissant le taux de guérison.

Le modèle ayant trois compartiments, il est décrit par trois équations différentielles ordinaires.
$$
\frac{dS}{dt}=-\frac{\beta S I}{N}\\
\frac{dI}{dt}=\frac{\beta S I}{N} - \gamma I\\
\frac{dR}{dt}=\gamma I
$$
Le modèle mathématique est très similaire au précédent. La différence vient du fait que certains individus du compartiment $I$ migrent vers $R$ avec une certaine probabilité. Par conséquent, une quantité est tronquée à l'ajout du compartiment $I$ pour le compartiment $R$.

Comme pour le point précédent, python implémente les trois équations différentielles de la manière suivante :

```python
S, I, R = S - beta * ((S * I) / N), I + beta * ((S * I) / N) - gamma * I, R + gamma * I 
```

Les trois compartiments sont mis à jour à chaque pas de l'algorithme et ceci simultanément.

Une représentation graphique sur $100$ étapes avec les paramètres : $N = 100, S = 99, I = 1, R = 0, \beta = 0.3, \gamma = 0.1$

![SIR_model](/home/maxime/Documents/Automate_Cellulaire/Diversity/Python/SIR_model.png)

### Simulations de références

Les modèles SI et SIR ont été prouvés par le passé et ont par conséquent une certaine validité. L'objectif ici est de valider notre modèle en le comparant aux résultats des modèles SI et SIR. Il s'agit donc de paramétrer notre modèle afin de le faire correspondre aux courbes des modèles valides déjà existant. 

Notre modèle paramétré et validé par SI et SIR peut servir de référentiel pour des analyses. Cette simulation de base nous permettrait de quantifier les différences dans les résultats avec d'autres simulations paramétrées différemment. En effet la simulation crée son propre monde par conséquent un résultat seul ne révèle aucune information. Pour déduire des résultats de simulations il faut les comparer entre eux. C'est la raison pour laquelle nous établissons une simulation de référence validée par SI et SIR.

Afin d'établir une référence nous pouvons paramétrer les modèles SI et SIR directement ainsi que les paramètres de notre modèle. Les paramètres de notre modèles doivent être cohérent et les plus globaux possible. 

#### Simulation de référence SI

La simulation de référence est un point de départ aux analyses. On définit les paramètres du modèle afin que le système se comporte comme un modèle SI. Cette simulation servira de référence pour celles qui vont suivre afin d'étudier l'impacte des modification de paramètres par rapport à cette référence.



















Les paramètres de références sont les suivants :

```c++
TAILLE_SYSTEME=500
NOMBRE_PERSONNES=25000
ITERATIONS=1500
GENOME_INIT_H=0
GENOME_DIVERSITY_H=0
GENOME_INIT_AP=0
VITESSE_MUTATIONS_AP=0
CHARGE_VIRALE=1
PUISSANCE=5
TRAINEE=0
SURVIE_AP=0
```

La taille du système est de $500\times 500$ avec $25'000$ individus. Les itérations sont adaptées en fonction de la simulation afin d'observer tous les phénomènes, c'est-à-dire que  la simulation est arrêtée lorsque le système est dans une situation stable. Il n'y a aucune diversité dans cette simulation de référence, tous les génomes des individus sont les mêmes. Le premier agent pathogène possède le même génome que tous les individus par conséquent il a une forte compatibilité sur les individus. La vitesse de mutation est réduite à $0$ afin que les pathogènes ne mutent pas. La charge virale est définie à $1$, par conséquent le niveau de contagion lors de contactes entre individus est maximal. Finalement les individus contaminés ne peuvent pas contaminer de cellules à cause du paramètre TRAINEE qui vaut $0$.

##### Résultats et analyses

Nous voyons ici les singes d'un modèle SI. La courbe orange représente le nombre d'individus dans le compartiment $S$ et la courbe bleue exprime le nombre d'individus dans le compartiment $I$. Étant donné qu'il n'existe que deux compartiments, la somme des individus de $S$ et $I$ donne le total des individus de la simulation.

Les courbes suivent une tendance logistiques avec un départ progressif, une forte accélération avant de ralentir la progression. Assez rapidement nous finissons dans un état stationnaire ou tous les individus sont contaminés dont dans le compartiment $I$ et aucun dans le $S$.

![contaminations](/home/maxime/Documents/Automate_Cellulaire/Diversity/data/SI_Reference/contaminations.png)

Le bar plot indique le nombre de fois que les individus ont été contaminés durant la simulation. Étant donné que tous les individus finissent contaminés et que le pathogène ne peut pas muter dû aux paramètres de la simulation, le bar plot montre que la totalité de la population a été contaminée une seule fois.

![nb_times_contaminations](/home/maxime/Documents/Automate_Cellulaire/Diversity/data/SI_Reference/nb_times_contaminations.png)

Le paramètre de mutation défini à $0$, il est impossible qu'un pathogène. Nous avons donc que un seul type de pathogène à chaque itération de la simulation avec le même génome. 

![nb_AP](/home/maxime/Documents/Automate_Cellulaire/Diversity/data/SI_Reference/nb_AP.png)

### Modèle SIR

Les modèles compartimentaux SIR ont un compartiment supplémentaire $R$ incluant tous les individus guéris. Initialement les individus commencent dans le compartiment $S$ et passent dans le compartiment $I$ si ils sont contaminés. Après une certaine période étant contaminé ils peuvent développer une immunité au pathogène et guérir. Tout individus développant une immunité à la maladie passe dans le dernier compartiment $R$.

#### Simulation de référence SIR

Pour modéliser une situation reflétant un modèle SIR il faut un mécanisme d'immunités chez les individus. Notre modèle fournit un paramètre permettant d'activer ou de désactiver les processus d'immunités. Tout comme pour la référence SI, cette simulation servira comme bases pour les simulations à suivre.

```c++
TAILLE_SYSTEME=500
NOMBRE_PERSONNES=25000
ITERATIONS=1500
GENOME_INIT_H=0
GENOME_DIVERSITY_H=10
GENOME_INIT_AP=0
VITESSE_MUTATIONS_AP=0
CHARGE_VIRALE=1
PUISSANCE=5
TRAINEE=0
SURVIE_AP=0
```

La taille du système est de $500\times 500$ avec $25'000$ individus. Les itérations sont adaptées en fonction de la simulation afin d'observer tous les phénomènes, c'est-à-dire que  la simulation est arrêtée lorsque le système est dans une situation stable.

![contaminations](/home/maxime/Documents/Automate_Cellulaire/Diversity/data/SIR_Reference/contaminations.png)

![nb_times_contaminations](/home/maxime/Documents/Automate_Cellulaire/Diversity/data/SIR_Reference/nb_times_contaminations.png)

![nb_AP](/home/maxime/Documents/Automate_Cellulaire/Diversity/data/SIR_Reference/nb_AP.png)




























