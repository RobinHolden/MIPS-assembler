# Projet CS351 (2022-2023): Émulateur MIPS

---
title: Projet CS351 (2022-2023): Émulateur MIPS
author: GUIGUET_HOLDEN
date: 26/10/2022
---

## Rendu 1

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Vérifié que `make test-cli` ne renvoie pas d'erreur.
  - [x] Vérifié que `make tests` se plaint sur le nombre d'instructions et pas
      sur l'existence des fichiers de sortie.
  - [x] Vu que les soumissions se font avec `make tar`.


## Rendu 2

(Une dizaine de lignes devrait suffire à chaque fois)

* Comment avez-vous choisi de programmer l'analyse de texte (dont la lecture
des opérandes entières) ?

Nous avons choisi de stocker une par une les lignes du fichier d'entrée dans
une chaîne de caractères, en tronquant les éventuels caractères d'espacement
en début de ligne et les commentaires en fin de ligne.
Ensuite, le programme distingue l'opérateur des opérandes, et les enregistre
dans une structure `Inst`.
Cette structure sert ensuite à déterminer la valeur héxadécimale de
l'instruction, à l'aide de tableaux répertoriant les types et arguments de
chaque instruction. La lecture des opérandes entières se fait à l'aide de
l'appel de fonction `strtol(arg[i], p, 0)`, avec une vérification que la
valeur retournée soit supportée.

* Avez-vous vu des motifs récurrents émerger ? Avez-vous "factorisé" ces motifs
pour éviter de les répéter ? Si non, serait-ce difficile ?

Nous avons en effet "factorisé" certains aspects du programme.
L'exemple le plus flagrant serait le fait de regrouper les instructions par
type (`RTYPE`, `ITYPE`, `JTYPE`).
Nous avons également remarqué que nous avions besoin d'utiliser la même
fonctionnalité à plusieurs endroits du programme, ce qui nous a mené a
créer de nouvelles fonctions telles que `skipwhitespace`.
Si nous n'avions pas factorisé certains passages du programme, le code source
serait surement plus long, et potentiellement moins lisible.
Cependant, certains aspects de factorisation enlèvent une partie de
flexbilité du code, si par exemple on venait à apporter des modifications
assez large au jeu d'instruction MIPS.

* Comment avez-vous procédé pour écrire les tests ? Étes-vous confiant·e·s que
toutes les instructions gérées sont couvertes ? 

Nous avons écrit un fichier de test comprenant toutes les instructions
implémentées, avec les différents cas de syntaxe que l'on peut rencontrer:
 - Registres : $0, $ra, etc.
 - Valeurs entières :  0x150, -0x150, 10, -10 etc.
 - Espacements avant les instructions
 - Espacements entre opérateur et opérande, ou entre opérandes
 - Espacements autour des virgules séparant les opérandes
 - Espacements en fin de ligne
 - Commentaires en fin de ligne
 - Commentaires seuls sur une ligne
Les tests étants réalisés sur toutes les instructions, nous sommes confiants
qu'elles sont couvertes.

* Quelle a été votre expérience avec l'utilisation et la compréhension de la
documentation (ie. des annexes) ?

La longueur des annexes nous a d'abord un peu découragés, ce qui a conduit à
une compréhension trop partielle de l'ISA MIPS. Ceci a ralenti notre
vitesse de progression d'écriture du programme, et a conduit à de moins
bonnes implémentations, du code moins claire et moins structuré.
Après avoir prit le temps de bien comprendre l'entièreté des annexes, nous
nous sommes rendus compte qu'elles étaient indispensable à l'écriture d'un
programme bien structuré. Nous avons trouvé ces annexes très claires et
complètes, sans pour autant contenir des informations inutiles, ou
trop redondantes.

PS : Nous n'avons pas implémenté les instructions `NOP` et `SYSCALL`, car
elles n'étaient pas présentes dans la liste des instructions à implémenter
dans l'annexe 1, même si ce serait surement possible.

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :
  - [x] Implémenté la traduction pour des instructions de toutes les catégories
      (calcul, comparaisons, sauts, HI/LO, mémoire)
  - [x] Implémenté la traduction pour toutes les instructions de l'annexe 2
  - [x] Pris en compte les cas particuliers : valeurs négatives, hors limites,
      noms d'instructions ou opérandes invalides...


## Rendu 3

(10/15 lignes devrait suffire à chaque fois)

* Quelle structure en modules planifiez-vous d'utiliser pour l'émulateur ?

• Lecture des instructions texte dans un fichier:
    Conversion du flux venant du fichier d'entrée en structure `rawinst` contenant des chaînes de caractères (op et args).

• Conversion de structure `rawinst` vers une structure `inst`
    La structure `inst` contient les valeurs entières des éléments de `rawinst`.

• Ecriture des instructions en héxadécimal dans un fichier de sortie
    Calcul de la valeur héxadécimale de l'instruction grâce à un ensemble de tableaux et des éléments de factorisation.

• Décodage des instructions assemblées en hexadécimal.
    Utilisation d'opérations logiques permettant de distinguer les éléments des instructions.
    Résultat contenu dans un élément `inst`.
• Execution des instructions grâce à une simulation des registres et de la mémoire
    Fonctions individuelles, une pour chaque instruction

* Quelles seront les fonctions principales de chaque module ?

Lecture:
getrawargs, getrawop

Conversion:
getopn, getargs, immval, regval, targval

Ecriture:
write

Decodage:
decodehex

Execution:
Fonctions indivuelles
push
pop

* Quels avantages voyez vous à cette structure (à comparer à un unique fichier)?

La séparation en différents modules permet une lecture plus facile du programme:
 - Noms de fichier explicites permettant la compréhension globale
 - Fonctions utilisées pour un module regroupées, meilleure clarté
 - Plus facile de naviguer dans le code quand on le lit, car fichiers moins longs
 - Permet d'avoir une fonction principale d'éxecution du programme qui permet de bien voir la structure du programme en faisant appel aux différents modules.

Cela permet aussi de bien séparer les différentes fonctionnalités, qui peuvent être réutilisées dans différents contextes.



## Rendu 4

* Avez-vous réussi à suivre la structure prévue au rendu 3 ? Quelles
modifications ont été nécessaires ? Rétrospectivement, est-ce que cette
structure était bien prévue ?

[COMPLÉTER ICI]

* Avez-vous compris le fonctionnement de chaque instruction à partir de la
documentation fournie ? Si non, quels sont les points obscurs ?

[COMPLÉTER ICI]

* Quels exemples de programmes avez-vous choisi pour tester le calcul ? Les
comparaisons et sauts ? La mémoire ?

[COMPLÉTER ICI]

* Le sujet spécifie-t-il tous les détails nécessaires pour bien implémenter la
mémoire ? Quels choix avec-vous faits ?

[COMPLÉTER ICI]

* Reste-t-il des bugs que vous avez découverts et pas corrigés ?

[COMPLÉTER ICI]

* D'autres remarques sur votre programme ?

[COMPLÉTER ICI]

* Cochez (en remplaçant `[ ]` par `[x]`) si vous avez :**
  - [ ] Implémenté l'émulation de toutes les instructions gérées par le rendu 2.
  - [ ] Implémenté l'émulation de toutes les instructions.
  - [ ] Tous vos tests qui passent.
  - [ ] Vérifié que vous tests couvrent toutes les instructions émulées.
  - [ ] Testé les cas particuliers : valeurs négatives, overflows...
  - [ ] Testé les cas d'erreur : division par zéro, sauts invalides...
  - [ ] Un port fonctionnel de DOOM pour votre émulateur.

* Des retours sur le projet en général ?

[COMPLÉTER ICI]
