# Sokoban

Ce TP étant long, il est possible de le rendre en groupe de 2 à 4.

L'objectif de ce TP est de présenter les résultats obtenus sur des problèmes de sokoban (https://en.wikipedia.org/wiki/Sokoban).

Il s'agit d'étudier des variantes de Sokoban et de résoudre chaque problème le plus rapidement possible, tous les précalculs possibles et réalisables étant autorisés.
Si des précalculs sont utilisés, il est attendu de les réaliser par application de procédures et sans intervention humaine (similaire à une génération procédurale).
Comme dans le cas de génération procédurale, il s'agit d'appliquer une procédure par exemple pour définir les positions bloquantes (i.e. interdites) ou les positions les plus interessantes. Les procédures utilisées peuvent ne pas être déterminites (i.e. ne pas garantir d'obtenir le même résultat à chaque exécution).
Deux variantes de Sokoban sont à étudier dans ce TP. Pour chaque variante, un ensemble de 10 problèmes est à résoudre (screen-0.txt à screen-1.txt).

Quand on demande la résolution d'un problème, on le fait par la ligne de commande: ./a.out 1 Screens-1/screen-1.txt

Le répertoire Screens-1 contient 10 problèmes à 1 joueur
Le répertoire Screens-2 contient 10 problèmes à 2 joueurs

Dans tous les problèmes :
Les caisses sont des "$"
Les cases objectifs sont des "."
Les murs sont des "#"

Les mouvements possibles sont udlrw pour chaque joueur, u pour up, d pour down, l pour left, r pour right, w pour wait.

Avec 1 joueur, on déplace 1 joueur (noté 1) à chaque instant.
Avec 2 joueur, on déplace 2 joueurs (notés 1 et 2) à chaque instant. uw fait monter le 1 et ne fait rien sur le 2. wu fait rien sur le 1 et monte le 2.

Pour chaque problème de Screens-1, on recherche les solutions permettant de déplacer 1, 2, 3, ... caisses sur les cases objectifs.
Pour chaque problème de Screens-2, ayant 2 joueurs, on recherche les solutions pour 2, 3, ... caisses vers 2,3, ... cases objectifs.
Ces problèmes étant difficiles, il est fort probable que nous ne réussissiez pas à déplacer toutes les caisses vers toutes les cases objectifs.
(même si une solution existe pour chaque problème)
On notera que Screens-1/screen-0.txt et Screens-2/screen-0.txt ne sont pas les mêmes problèmes et que leur solution diffère.

Extraire sokoban-2023.tgz
Aller dans le répertoire sokoban-2023
Le répertoire src contient le début du TP
Le répertoire Screens-1 (respect. 2) contient les problèmes à 1 joueur (respect. 2 joueurs)
Dans src :
La commande "make" crée l'executable r0
Lancer "./r0 ../Screens-1/screen-0.txt" permet de lire et afficher le problème considéré

#####################################################################

Ecrire un programme C/C++ résolvant ces problèmes.
Ecrire un programme Prolog résolvant ces problèmes (qui sera probablement plus lent que le programme C/C++ mais peut être plus simple).

Dans un rapport pdf en une ou deux pages :
Présenter l'algorithme correspondant aux calculs déployés.
Si des précalculs sont utilisés, présenter les algorithmes correspondants.
Pour chaque problème, présenter dans une table de résultats :

- le nombre max de caisses déplacées sur les cases objectifs
- la solution correspondante
- le temps de calcul utilisé (en cas de résolution non déterministe, donner le meilleur temps, le temps moyen et le nombre d'essais pour obtenir ces résultats)
- le temps de précalcul (si précalcul vous avez utilisé)

Pour l'ensemble des calculs, préciser cpu et ram de l'ordinateur utilisé.

#####################################################################
