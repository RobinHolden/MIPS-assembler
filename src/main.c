// Projet MIPS 2022-2023
// Auteurs: GUIGUET_HOLDEN

#include <stdio.h>
#include <string.h>
#include "modes.h"

int main(int argc, char **argv)
{
    /* S'il n'y a pas d'arguments (argc==1), lancer le mode interactif. */	
	
	if (argc == 1){
		if (interMode()){
			printf("Error occurred during interactive mode\n");
			return 1;
		}
		else{
			printf("Interactive mode exited successfully\n");
			return 0;
		}
	}


    /* S'il y a 2 arguments (argc==3), lancer le mode automatique pas-à-pas.
       Le premier argument (argv[1]) est le nom du programme assembleur.
       Le second argument (argv[2]) est forcément "-pas". */
	
	if (argc == 3 && !strcmp(argv[2], "-pas")){
		if (stepMode(argv[1])){
			printf("Error occurred during step-by-step mode\n");
			return 1;
		}
		else{
			printf("Step-by-step mode exited successfully\n");
			return 0;
		}
	}


    /* S'il y a 3 arguments (argc==4), lancer le mode automatique.
       Le premier argument (argv[1]) est le nom du programme assembleur.
       Le second argument (argv[2]) est le nom du fichier où il faut
       enregistrer le code assemblé.
       Le troisième argument (argv[3]) est le nom du fichier où il faut
       enregistrer l'état final du programme à la fin de l'exécution. */

	if (argc == 4){
		if (autoMode(argv[1], argv[2], argv[3])){
			printf("Error occurred during automatic mode\n");
			return 1;	
		}
		else {
			printf("Automatic mode exited successfully\n");
			return 0;
		}
	}
    /* Les rendus seront testés par le mode automatique, il est donc important
       que ce mode fasse les choses suivantes :
       - Lire le programme assembleur. Ouvrez-le avec le mode "r" de fopen().
       - Produire les deux fichiers de sortie. Ouvrez-les avec le mode "w" de
         fopen() pour qu'ils soient créés s'ils n'existent pas encore.
       Pour commencer vous n'avez pas besoin d'utiliser les fichiers, il suffit
       de les ouvrir et de les fermer immédiatement. */

    /* Le Makefile fourni contient une commande "test-cli" qui vérifie que le
       mode automatique fonctionne et crée bien les deux fichiers de sortie.
       Tapez "make test-cli" pour effectuer le test. S'il n'y a pas d'erreur,
       c'est bon. */

    /* Supprimez ces commentaires une fois que c'est fait. */

    printf("Hello émulateur MIPS!\n");

    return 0;
}
