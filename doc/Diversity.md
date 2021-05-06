# Diversity

### Résumé

Une pandémie est une épidémie présente sur une grande zone et affectant un grand nombre de personnes. Ces épidémies peuvent être causée par de multiples facteurs. L'espèce humaine est touchée par des pandémies à une fréquence d'une fois par siècle mais depuis les années 2000, ce rythme c'est grandement accéléré. En effet, nous avons été victime de pandémies comme Ebola en 2013, SARS-2 en 2008, COVID en 2020 et bien d'autres. Ces épidémies à grande échelle deviennent de plus en plus fréquente pour de multiples raisons que nous ne traiterons par ici.

Le travail se concentre sur l'aspect de diversité écologique des populations touchées lors de pandémies. La diversité d'une espèce est un facteur clef permettant sa survie et son évolution. L'objectif de l'étude est de constater l'impacte de la diversité des populations sur la propagations de pandémies. En effet, une grande diversité au sein d'une population ralenti la propagation d'une pandémie. Il s'agit dans ce travail d'étudier les différentes issues de simulations en modifiant le paramètre de diversité de la population observée. 

L'étude se concentre sur la réalisation d'une simulation permettant de modéliser une population avec des caractéristiques paramétrables. Nous contaminons un individu et observons au fil du temps la propagation ou non de l'épidémie.

La simulation se base sur le principe d'automate cellulaire. Le système se présente sous forme d'une grille bidimensionnelle tel un échiquier de taille voulu. La population navigue sur cet échiquier et les individus interagissent les uns avec les autres. Le but est de simuler les mouvement au sein d'une population et des contactes permettant la propagations d'agents pathogènes. Au fil du temps de la simulation nous pouvons étudier la propagation de la pandémie en fonction des paramètres du modèle.

L'objectif est d'étudier les résultats de simulations en faisant varier la diversité de la population et des autres facteurs. Les résultats permettraient de quantifier l'impacte qu'à la diversité d'une espèce sur une éventuelle pandémie.

###### Liste des résultats majeurs

### Table des matières

[toc]

### Introduction

L'élément principal de la recherche scientifique est l'étude de propagation de pandémies en fonction de la diversité de la population étudiée. Pour des questions de simplification, beaucoup de facteurs externes ont été ignorés. En effet, l'apparition et la propagation d'une épidémie est le résultat d'une multitude de facteurs complexes. La simulation se base exclusivement sur des paramètres simples tout en ignorant des aspects comme l'âge, la condition de vie ou encore l'accès aux soins. Le modèle se focalise sur le principe de génomes, mutations et immunités. D'autres facteurs sont paramétrables, comme la taille du système ou le nombre de personnes et bien d'autres mais les résultats recherchés sont basés sur l'aspect de diversité. 

La simulation ne comporte que deux types d'acteurs : des individus d'une population donnée et des agent pathogènes. L'espace représenté dans la simulation est une grille bidimensionnelle permettant au individus de se déplacer librement. Ce modèle simplifié permet de représenter les interactions entre les individus dans une population. Ici, nous considérons que deux individus sur des cellules voisines sont en contact et peuvent potentiellement potentiellement se contaminer les uns les autres. Initialement, un individu est contaminé et il s'agit de déterminer l'évolution de la situation. On cherche à observer si l'agent pathogène parvient à se propager ou non parmi la population d'individu. Une multitude d'autres paramètres peuvent être modifiés pour influencer la simulation. 

La recherche principale est d'observer et mesurer l'évolution du système en faisant varier les diversités des acteurs, en sachant que chaque acteur du système possède un indicateur représentant son code génétique.

La question que l'on se pose pour ce travail est de déterminer si la diversité d'une population touchée par une épidémie modifie la propagation d'un agent pathogène ou non. Il s'agit ici d'illustrer et de quantifier cet effet à l'aide de modèles numériques.

###### Etat des connaissances dans le domaine (ce qui a déjà été fait)

###### Evaluation des points faibles de ces connaissances (travaux précédents) expliquant l’existence de ce travail (définir le but du travail proposé)

###### Faire ressortir l'importance technique et scientifique pour répondre aux questions ouvertes

### Objectifs

Le premier objectif de la recherche est de produire un modèle numérique cohérent qui fournirait des résultats que l'on a pu observer par le passé. L'idée est d'obtenir une simulation qui reflète au maximum une situation réelle. Il s'agirait donc de soumettre au modèle des cas simples dont on peut inférer des résultats et de constater les résultats afin de valider le modèle. Pour ce faire on peut se référer au modèles compartimentaux en épidémiologie pour tester le modèle numérique. La validité du modèle sur des cas connus est nécessaire pour conclure de nouveaux résultats. 

Le second objectif est de déterminer les différences dans les résultats en faisant varier la diversité de la population étudiée. Il s'agit de comparer les mesures de la simulations avec différents paramètres et de quantifier ces différences. La variation d'autres paramètres peut aussi être étudie comme par exemple la vitesse de mutation des agents pathogènes. Il s'agit donc d'illustrer et de quantifier l'impacte qu'a ces paramètres sur l'émergence d'événement de grande taille comme les pandémies.

Avec ces objectif on veut pouvoir vérifier la cohérence du modèle numérique et utiliser ses résultats pour d'éventuelles prédictions mais aussi démontrer l'importance de la diversité écologique d'une population face à ces événement à grande échelle. 

###### Mettre en évidence l'originalité de la solution proposée

### Approche du problème, méthodes, outils utilisés

- Programmes de calcul utilisé : C++, Python
- type de modèle (Automate cellulaire)
- Mettre en évidence les améliorations apportées (solutions originales)
- description du modèle, méthodes afin de résoudre les problèmes
- Erreurs possibles, problèmes
- Limitations techniques ou théoriques

#### Approche du problème

##### Code génétique

Le travail se concentrant sur la notion de diversité il fallait un moyen pour représenter la diversité d'une population et les interactions entre différents acteurs en prenant en considération leur diversité. La méthode utilisée se base sur le principe de génome. On attribue un génome, qui représente le code génétique d'un être vivant, à chaque acteur du système. Par conséquent, chaque individu et chaque agent pathogène possède un génome. Ce génome se présente sous la forme d'un entier codé sur $4$ octets. Nous avons dont $32$ bits disponibles afin de représenter le génome d'un acteur. 

La notion de diversité d'une population peut à présent se définir par de grandes différences dans ces valeurs sur $32$ bits d'un individu à un autre. En effet, il y a une grande diversité au sein d'une population si les génomes des individus sont différents les uns des autres. Nous pouvons donc générer des séquences pour les génomes en prenant en compte le facteur de diversité du modèle. Il est possible de construire ces génomes, principalement pour la population d'individu, en complémentant un certain nombre de bits d'une séquence de référence. L'idée ici est d'attribuer à tous les humains un génome fixe et identique pour tout le monde. Dans cette configuration, nous avons une diversité nulle étant donné que tout le monde a le même code génétique. Dans le cas d'une diversité non nulle, nous modifions (complémentons) certains bits de la séquence de génome des individus. Ce processus se fait aléatoirement et le nombre de complémentation dépend du paramètre de diversité du modèle. Avec cette méthode on finit avec des génomes déviant plus ou moins d'un certain génome référentiel.

###### histogramme exemple de la distribution des génomes humains (gaussienne)

##### Match entre individu est agent pathogène

Les génomes étant défini, il reste à définir la manière dont les agents pathogènes et les individus réagissent les uns avec les autres. Le problème est l'utilisation des génomes, que ce soit ceux des agent pathogènes ou ceux des humains. Comment gérer les interactions entre individus et agents pathogènes en se basant sur des génomes de $32$ bits ? La technique utilisée est basée sur la distance de Hamming entre les séquences des génomes. Cette méthode fournit une solution interprétable suite à la rencontre entre un individu et un agent pathogène. En effet, il faut un moyen de traduire deux génomes en une contamination de l'individu ou non. 

La distance de Hamming est une notion mathématique qui permet de calculer les différences entre deux séquences binaires par exemple. Cette technique consiste simplement à compter le nombre de symboles différents pour deux suites du même nombre de bits. Il s'agit donc de parcourir une des séquence et pour chaque indice comparer avec le symbole correspondant de l'autre séquence. Pour chaque symbole différent, la distance de Hamming est incrémentée de $1$. 

Nous pouvons donc représenter le match entre un individu et un agent pathogène par cette distance sous forme d'un entier. Il s'agit ensuite de convertir cette valeur en une probabilité. En effet, dans notre exemple il existe uniquement $33$ valeurs possible de distance de Hamming qui caractérisent un match. Si on applique une fonction de seuillage sur si peu de valeurs, les résultats vont être trop tranchés. Par conséquent on convertit cette distance calculé entre deux génomes en probabilité. Cette probabilité peut ensuite être évaluée ce qui pourrait déterminer une immunisation à un pathogène ou une contamination par un pathogène. 

###### Attention posteriori, a priori !

### Outils

L'outil principal de la simulation est le C++, un langage puissant et performant. L'avantage de ce langage est qu'il est très rapide, ce qui est nécessaire pour exécuter des simulations de plus grande taille. De plus le C++ permet la programmation orientée objet, utilisé ici pour modéliser les individus ainsi que les agents pathogènes. 

Le langage utilisé permettant les analyses et représentations graphiques est Python. Ce langage à l'avantage d'être facile à manipuler et puissant pour faire de l'analyse. C'est donc un langage idéal pour des représentations de données. De plus Python dispose de bibliothèques logicielles comme Numpy ou encore Matplotlib qui permettent de faire du calcul scientifique ainsi que de représenter des données.

Le travail complet est disponible sur un dépositoire GitHub et est accessible. Ceci fournit de la transparence ainsi que le partage du projet. De plus toutes les versions antérieurs de la recherche y figure. 





# Diversity

### Modèle

Le modèle cherche à simuler la propagation de pandémies dans une population. Le système inclut donc des **acteurs** qui peuvent faire des actions ainsi qu'un **espace physique** sur lequel les acteurs peuvent se déplacer. Les acteurs sont des organismes vivants qui se déclinent en deux espèces distinctes. La première groupe fait partie des organismes victimes de l'épidémie et le second groupe est responsables de l'infection. Par conséquent nous sommes dans une situation ou une espèce en attaque une autre. Par contre dans le fonctionnement du modèle, il y a des restrictions sur la nature de l'espèce attaquante. Nous parlons ici d'organismes capables de contaminer un hôte. 

Les organismes évoluent dans une monde plat et parfaitement géométrique en deux dimensions. L'espace est comparable à un échiquier avec les acteurs étant des pions.

#### Acteurs

Il existe exclusivement deux espèces d'organismes dans le système : 

- Les **agents pathogènes** sont les agents infectieux responsable de l'épidémie.
- Les **hôtes potentiels**, constituant de la population victime de l'épidémie.

La classe "agents pathogènes" ne fait pas référence à une espèce en particulier mais peut reflète des organismes avec le pouvoir d'infecter une autre espèce. Il peut s'agir de virus, bactéries ou encore parasites. La caractéristique de ce groupe est qu'il a le pouvoir de rendre malade un hôte et donc d'affecter une espèce par une maladie qu'elle génère. Il peut s'agir de maladies touchant des humain ou de zoonoses suivant la nature des espèces du système.

Les "hôtes potentiels" sont les organismes susceptible de développer la maladie suite à la contamination par les agents pathogènes. Il peut s'agir d'humains tout comme d'animaux ou de plantes. La restriction est que cette espèce doive être affectée par les agents pathogènes ainsi que par la maladie. Le terme "hôte potentiel" signifie que l'organisme peut devenir l'hôte de l'agent pathogène. On parle de "hôte du pathogène" lorsque l'organisme est contaminé et porteur de l'agent pathogène.

##### Hôtes potentiels

Un hôte potentiel peut se présenter sous deux formes :

-  <img src="/home/maxime/Documents/Inkscape/humain_sain.png" alt="humain_sain" style="zoom:2%;" /> : hôte potentiel sain ne portant pas le pathogène.
- <img src="/home/maxime/Documents/Inkscape/humain_infecte.png" alt="humain_infecte" style="zoom:2%;" /> : hôte infecté par un agent pathogène.

Dans le premier cas, l'illustration représente un hôte potentiel qui n'est pas contaminé par un agent pathogène et donc n'est pas touché par la maladie. Contrairement à ce que l'on pourrait penser, l'illustration ne fait pas forcément référence à un humain mais à un individu potentiellement vulnérable à la classe des agents pathogènes.

Le second cas fait référence à la même espèce mais cette fois ci, l'individu est contaminé par un agent pathogène. Le modèle ne fait pas la distinction entre malade et porteur du virus. Par conséquent, un hôte porteur du pathogène est d'office considéré comme malade. De plus, le modèle définit un taux de contagion qui est paramétrable. Le niveau de contagion est donc constant pour tous les organismes contaminés et ceci tout du long de la simulation. Un hôte infecté par un agent pathogène est donc contagieux, ce qui signifie qu'il a la pouvoir de transmettre l'agent pathogène à d'autres individus de la même espèce. Tout comme le point précédent, l'illustration ne fait pas forcément référence à un humain.

##### Agents pathogènes

Un agent pathogène peut se présenter sous deux formes :

- <img src="/home/maxime/Documents/Inkscape/humain_infecte.png" alt="humain_infecte" style="zoom:2%;" /> : un agent pathogène peut être dans un hôte.
- <img src="/home/maxime/Documents/Inkscape/AP_multiple.png" alt="AP_multiple" style="zoom:2%;" /> : un agent pathogène peut contaminer un espace.

Le premier cas est identique à celui précédemment développé mais cette fois ci, la situation est perçue du point de vue de l'agent pathogène. Quand un hôte devient contaminé par un agent pathogène, ce dernier est absorbé par l'hôte. C'est-à-dire que l'agent pathogène n'est plus un entité distincte mais fait partie entière de l'individu. Par conséquent l'individu devient un hôte contaminé et non pas un hôte sain associé à un agent pathogène.

Le second cas indique qu'une zone physique est contaminée par un agent pathogène. Un hôte contaminé, en plus de contaminer d'autres individus sains, peut contaminer une surface. Si une surface est contaminée, une copie de l'agent pathogène de l'hôte se dépose sur la surface. Un agent pathogène qui contamine une surface est inerte, c'est-à-dire qu'il ne peut pas se déplacer ni muter par contre il a toujours le potentiel de contaminer des individus sains. Un agent pathogène isolé sur une surface ainsi n'a une durée de vie que très limitée, gérée par un paramètre du modèle.

#### Espace physique

L'espace physique est une surface plane sur laquelle on peut placer et déplacer des acteurs. La surface se présente sous la forme d'une grille régulière tel un échiquier. Cette grille contient des cellules dans lesquelles on peut y placer un acteur. Cet espace bidimensionnel est la seule représentation spatiale du modèle. Chaque acteur a des coordonnées dans cet espace qui définissent sa position. Par conséquent, chaque cellule de la grille est indexée par une paire d'entiers. 

Dans la représentation du modèle, une cellule n'a que $6$ états possibles, c'est-à-dire que chaque cellule de la grille ne peut se retrouver que dans $6$ situations différentes. L'état d'une cellule fait référence à l'acteur ou aux acteurs qui se trouvent dessus. Concrètement une cellule est simplement une surface carrée mais nous associons les acteurs se trouvant sur la cellule à cette dernière et ceci décrit l'état de la cellule. Les $6$ états possibles d'une cellule sont listés ci-dessous.

###### Cas 1 : 

La cellule est vide, aucun acteur ne l'occupe. Cette situation signifie simplement que la surface n'est occupée par aucun acteur et est libre pour en accueillir un.

###### Cas 2 : <img src="/home/maxime/Documents/Inkscape/humain_sain.png" alt="humain_sain" style="zoom:2%;" />

Un hôte potentiel se trouve sur la cellule.

###### Cas 3 : <img src="/home/maxime/Documents/Inkscape/humain_infecte.png" alt="humain_infecte" style="zoom:2%;" />

Un hôte infecté se trouve sur la cellule. 

###### Cas 4 : <img src="/home/maxime/Documents/Inkscape/AP_multiple.png" alt="AP_multiple" style="zoom:2%;" />

Un agent pathogène se trouve sur la cellule, infectant l'espace, sans hôte.

###### Cas 5 : <img src="/home/maxime/Documents/Inkscape/humain_sain_AP.png" alt="humain_sain_AP" style="zoom:45%;" />

Un hôte potentiel sain se trouve sur une cellule contaminée par un agent pathogène.

###### Cas 6 : <img src="/home/maxime/Documents/Inkscape/humain_infecte_AP.png" alt="humain_infecte_AP" style="zoom:9%;" />

Un hôte contaminé se trouve sur une cellule déjà contaminée par un agent pathogène.

##### Grille régulière

La grille régulière est l'espace dans lequel les acteurs évoluent. Chaque acteur est représenté au niveau spatial par ses coordonnées sur la grille. Par conséquent nous utilisons une grille contenant les acteurs du système et leur permettant de se déplacer et interagir. Cet espace est la seule représentation spatiale du modèle, c'est-à-dire que les acteurs ne peuvent spatialement évoluer qu'en respectant la géométrie de la grille. L'illustration suivante semble avoir des bords fixes mais en réalité ce sont des bords périodiques. Cela signifie qu'un acteur n'est pas bloqué par un bord du système. Dans le cas ou un individu souhaite se déplacer en dehors du système nous le faisons sauter à l'opposé de la grille. Par conséquent les bords sont connectés et permettent d'éviter les effets de bords. 

Un exemple de système en cours de simulation est illustré ci-dessous.

<img src="/home/maxime/Documents/Inkscape/grid.png" alt="grid" style="zoom:25%;" />

L'espace bidimensionnelle permet de donner une représentation spatiale aux acteurs mais également de les faire interagir les uns avec les autres. Les interactions se font par la notion de voisinage. 

##### Voisinage

La représentation spatiale permet de situer tous les acteurs du système relativement les uns aux autres. Nous définissons que dans cet espace, les acteurs avec des coordonnées proches sont géographiquement rapprochés et peuvent s'influencer. Le voisinage est la transcription de cette proximité entre les acteurs et permet de définir la portée de l'influence des acteurs. Le voisinage d'une cellule est l'espace avoisinant à la cellule. Dans le modèle, le voisinage est représentée ainsi :

<img src="/home/maxime/Documents/Inkscape/voisinage.png" alt="voisinage" style="zoom:25%;" />

Le voisinage de la cellule contenant un acteur est les $4$ cellules avoisinantes directes en plus de la cellule actuelle. Par conséquent notre humain dans cette cellule ne pourra interagir qu'avec d'autres acteurs dans les cellules voisines (en cyan) ou avec un autre acteur sur sa cellule. Le reste du système lui est hors de portée et donc invisible. Par conséquent, les actions et les états d'un acteur du système n'est influencé que par son propre état ainsi que les autres acteurs se trouvant dans son voisinage. Toues les autres cellules ainsi que leurs acteurs n'ont aucun impacte sur l'acteur.

#### Simulation

Afin d'initialiser une simulation nous commençons par définir la **taille de la grille** et le **nombre de personnes** et nous contaminons un humain. Il existe une multitude d'autres paramètres définissant les comportements des différentes mécaniques de la simulation que nous expliquerons plus loin. Par conséquent, une situation initiale se présente toujours sous la forme ci dessous. Notre population est saine sauf un seul individu qui porte l'agent pathogène initial. C'est le point de départ de toute épidémie avec la contamination du premier hôte. Il s'agit ensuite d'observer la propagation ou non du pathogène initial. Un exemple de configuration initiale pourrait être : 

<img src="/home/maxime/Documents/Inkscape/configuration_initiale.png" alt="configuration_initiale" style="zoom:25%;" />

Pour toutes configurations initiales, le placement des individus est aléatoire. A partir de là, un certain nombre d'itérations vont se produire permettant de faire évoluer le système.

##### Itérations

Depuis une configuration, le système peut évoluer par un itération. Une itération est une transition d'un état à un autre du système. Par exemple, depuis l'état initial de la simulation, donc l'état $0$ on peut passer dans l'état $1$ par une transition qui est la première itération. Cette itération modifie les états de tous les acteurs et leur permet d'effectuer une ou plusieurs actions.

Pour être plus précis, une itération du système consiste en deux phases. La première est de mettre à jour tous les acteurs du système et la seconde est de permettre aux acteurs de se déplacer dans l'espace. La phase de mise à jour comprend l'actualisation de tous les acteurs ainsi que d'effectuer toutes les interactions entre les différents acteurs. La phase de mouvement permet uniquement aux individus de se déplacer sur la grille. Le détail de ces deux phases est explicité plus loin.

La simulation se termine après le déroulement d'un certain nombre d'itérations défini. La notion d'itération représente une certaine évolution dans le temps d'un système. C'est la seule représentation temporelle de la simulation.

##### Mouvements des acteurs

La phase de mouvement permet simplement aux acteurs du système de physiquement se déplacer dans le domaine. Chaque acteur est sur une cellule caractérisée par des coordonnées et peut à cette phase bouger en changeant de cellule. Tous les acteurs ne peuvent pas se déplacer, seuls l'espèce hôte peut se mouvoir. Les agents pathogènes ne peuvent pas se déplacer par eux mêmes. Par conséquent, chaque individu peut se déplacer à chaque itération et ceci de une seule cellule. C'est-à-dire que un individu ne peut bouger que de une cellule à la fois et ne peut pas se déplacer en diagonale. La portée de déplacement est illustrée ci-dessous et un individu a l'impossibilité de se déplacer sur une cellule si celle-ci est déjà occupée par un autre individu.

<img src="/home/maxime/Documents/Inkscape/move_available.png" alt="move_available" style="zoom:25%;" />

Sur cet exemple, l'individu sur la cellule centrale souhaite se déplacer. Sur les $4$ cases possible pour un déplacement à cette itération, $3$ sont libres et $1$ occupée. Par conséquent notre humain ne peut pas de déplacer vers la droite. Le choix de l'individu pour le déplacement est aléatoire. 

La procédure pour se déplacer est la suivante. Tout d'abord, l'individu choisit aléatoirement une des $4$ cellule voisine. Il vérifie ensuite que la cellule choisie soit libre. Si la cellule est libre il s'y déplace, sinon il ne bouge pas à cette itération et par conséquent reste là ou il est.

##### Mise à jour des acteurs

La phase de mise à jour se déroule en deux étapes. La première est d'actualiser l'état interne de l'acteur et se produit dans deux situations. Le premier cas survient lorsqu'un agent pathogène contamine une cellule. Cet agent pathogène n'est dans aucun hôte donc sa survie est incertaine. Par conséquent il se peut que cet agent pathogène meurt. La phase de mise à jour interne de cet acteur sert à déterminer si il meurt à cette itération ou non. La deuxième situation ou l'actualisation de l'état interne d'un acteur est nécessaire est lorsqu'un hôte est contaminé par un agent pathogène. En effet, à chaque itération les hôtes contaminées peuvent développer une immunité au pathogène les contaminant. Cette vérification s'effectue à chaque itération  et consiste à recalculer la compatibilité entre l'individu et l'hôte. Si l'agent pathogène contaminant cet hôte survit à l'étape précédente, il a la possibilité de muter. La deuxième étape de la mise à jour d'un acteur est l'analyse du voisinage. A chaque itération, les acteurs analysent leur voisinage et interagissent avec les acteurs à proximité. Toues les différentes interactions entre acteurs sont explicités plus loin.

Par conséquent, le système peut évoluer de deux manières différentes. Premièrement, les acteurs appartenant à l'espèce hôte peuvent se déplacent à chaque itération, modifiant leur position sur la grille. Deuxièmement les états de tous les acteurs du système peut changer grâce aux interactions entre acteurs mais aussi à l'actualisation de leurs états internes.

Les interactions se basent sur la notion de voisinage. Un acteur ne prend en considération durant sa mise à jour que les autres acteurs dans les cases voisines. 

##### Interactions sur même cellule

Le premier groupe d'interaction est celui des collisions d'acteurs sur la même cellule. Étant donné que deux humains ne peuvent pas se trouver sur la même cellule à la même itération, nous analyserons que le cas ou un humain se trouve sur une cellule déjà contaminée par un agent pathogène. Il y a deux cas de collisions possible dans toutes simulation.

###### Cas 1

Le premier cas se produit quand un hôte potentiel sain se trouve sur une cellule déjà contaminée : <img src="/home/maxime/Documents/Inkscape/humain_sain_AP.png" alt="humain_sain_AP" style="zoom:45%;" /> 

Dans cette configuration, un individu sain se retrouve en contact direct avec un agent pathogène contaminant une cellule et risque donc d'être contaminé et de devenir hôte de cet agent pathogène. Il existe deux manières pour contaminer un humain initialement sain, ceci est la première.

###### Cas 2

Le second cas se produit lorsqu'un hôte déjà contaminé se retrouve sur une cellule déjà contaminée : <img src="/home/maxime/Documents/Inkscape/humain_infecte_AP.png" alt="humain_infecte_AP" style="zoom:9%;" />

L'agent pathogène contaminant la cellule n'a aucun impacte sur l'individu car ce dernier est déjà l'hôte d'un autre agent pathogène. Par conséquent, les deux acteurs n'ont aucune influence l'un sur l'autre dans cette configuration.

##### Interactions sur cellules voisines

Le deuxième type d'interactions se produit entre des acteurs qui sont spatialement proches, sur des cellules différentes. Afin de permettre aux acteurs d'interagir sans être sur la même cellule, ils doivent appartenir à leur voisinage respectif. Par exemple, deux individus sur des cellules adjacentes interagissent à cette itération. 

###### Cas 1

Dans le cas ou nous avons deux humains sains sur des cellules voisines, aucune interaction ne se produit.

<img src="/home/maxime/Documents/Inkscape/humain_humain.png" alt="humain_humain" style="zoom:25%;" />

###### Cas 2

Un cas plus intéressant survient lorsqu'un humain sain rentre en contact avec un humain contaminé.

<img src="/home/maxime/Documents/Inkscape/humain_humain_infecte.png" alt="humain_humain_infecte" style="zoom:25%;" />

Lors de cette interaction il se peut que l'humain sain soit contaminé par l'humain contaminé. L'agent pathogène contenu dans l'humain de droite pourrait avec une certaine probabilité se propager sur l'humain de gauche. Un humain sain peut donc être contaminé par un humain hôte seulement si l'individu hôte se trouve dans son voisinage. La contamination de humain à humain est la seconde méthode de contamination d'un être humain initialement sain.

###### Cas 3

Similairement au cas numéro $1$, si deux individus contaminés entrent en contact, aucune interaction ne se produit.

<img src="/home/maxime/Documents/Inkscape/humain_infecte_humain_infecte.png" alt="humain_infecte_humain_infecte" style="zoom:25%;" />

##### Contamination de cellule

Une cellule se trouve dans l'état <img src="/home/maxime/Documents/Inkscape/AP_multiple.png" alt="AP_multiple" style="zoom:2%;" /> si cet espace a été contaminé par un humain infecté. En effet, lorsqu’un humain infecté se déplace il a une certaine probabilité de contaminer l'espace qu'il occupait.

<img src="/home/maxime/Documents/Inkscape/infecte_cellule.png" alt="infecte_cellule" style="zoom:25%;" />

Après un déplacement, l'humain contaminé à une certaine probabilité d'avoir contaminé la cellule qu'il occupait précédemment. L'agent pathogène contaminant à présent la cellule est le même que celui contenu dans l'humain.

Un cas particulier peut se produire si un humain hôte contamine un espace déjà contaminé par un autre agent pathogène. On a dit précédemment que un humain déjà infecté n'était pas sensible à un agent pathogène externe contaminant une cellule par contre il se pourrait que notre humain contamine lui aussi cette cellule. Dans ce cas précis nous écrasons l'agent pathogène initialement présent et le remplaçons par l'agent pathogène de l'hôte.

### Diversité génétique

Le travail est orienté sur l'aspect de diversité génétique et ceci dicte l'issue des différentes interactions entre les acteurs. Pour simplifier nous nous contentons d'attribuer une valeur sous forme d'un entier à chaque acteur. Cette valeur se code sur $4$ octets donc $32$ bits et cette séquence représente le **code génétique**. Tous les agents du système ont un code génétique sur $4$ octets que ce soit des humains ou des agents pathogènes.

Lors d'une interaction entre deux acteurs, leurs code génétique est analysé afin de déterminer une action. La méthode permettant de comparer deux séquences de $32$ bits est la **distance de Hamming**.

#### Distance de Hamming

La distance de Hamming est un calcul s'effectuant sur deux séquences de symboles de même longueur. Il s'agit de quantifier la différences entre ces deux séquences par un entier. Un exemple sur deux séquences de $1$ octet est donné ci-dessous.

<img src="/home/maxime/Documents/Inkscape/hamming.png" alt="hamming" style="zoom:67%;" />

Dans cet exemple on peut voir en comparant les deux séquences de bits que sur $5$ positions les symboles diffèrent. Par conséquent la distance de Hamming entre la séquence $10101100$ et $11010110$ est égale à $5$.

Le calcul de la distance d Hamming s'effectue toujours entre le génome d'un humain et celui d'un agent pathogène et détermine la compatibilité des deux organismes.

La distance de Hamming s’interprète de la manière suivante dans le modèle :

- Une faible distance de Hamming donne l'ascendant à l'agent pathogène.
- Un grande distance de Hamming donne l'ascendant à l'humain.

Par conséquent, lors d'une interaction entre un humain et un agent pathogène, deux séquences de génome très proches implique une grande probabilité que l'agent pathogène contamine l'humain et s'installe. Par contre, deux séquences très différentes implique une grande probabilité que l'humain résiste à l'agent pathogène et ne soit pas contaminé. 

Le calcul de la distance de Hamming s'effectue dans plusieurs situations :

###### Cas 1

Un humain sain est en contact avec un voisin contaminé ou se trouve sur une cellule déjà contaminée par un agent pathogène. Dans cette situation, l'humain sain est exposé à cet agent pathogène, il reste à déterminer la compatibilité de ces deux organismes et de déterminer si notre humain devient hôte du pathogène ou reste sain. La compatibilité se calcule à partir de la distance de Hamming.

###### Cas 2

La deuxième situation ou la distance de Hamming est utilisé est pour déterminer l'évolution de l'état d'un humain contaminé. En effet un humain contaminé est l'hôte d'un agent pathogène et chacun essaie de prendre le dessus sur l'autre organisme. A chaque itération la distance de Hamming est recalculée entre les deux génomes afin de déterminer si l'humain s'immunise ou si le pathogène reste dans son hôte. 

### Immunisations

Le modèle intègre deux types d'immunisation, une **immunisation à priori** et une **immunisation à posteriori**. On parle d'immunisation à priori quand un être humain n'est pas affecté par un certain agent pathogène pour des questions génétiques. Par contre on parle d'immunisation à posteriori quand l'immunisation est acquise. C'est-à-dire que l'humain a développé une immunité en présence d'un agent pathogène.

### Mutations

Les agents pathogènes contaminant des humains sont les seuls à pouvoir muter. 

