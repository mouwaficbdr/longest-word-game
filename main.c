#include <stdio.h>
#include <string.h>
#include "fonctions.h"

int main()
{
    // Variables pour l'historique
    char motsJoueur1[3][20] = {"MOT1", "MOT2", "MOT3"};
    char motsJoueur2[3][20] = {"MOT4", "MOT5", "MOT6"};
    int scoresJoueur1[3] = {3, 4, 5};
    int scoresJoueur2[3] = {2, 3, 4};

    // Initialisation des variables globales pour le test
    strcpy(nomJoueur1, "Joueur1");
    strcpy(nomJoueur2, "Joueur2");
    scoreJoueur1 = 10;
    scoreJoueur2 = 15;
    toursJoues = 3;
    nbreTours = 5;
    
    // Initialisation de la grille
    char lettresGrille[nbreTotalLettresGrille] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    for (int i = 0; i < nbreTotalLettresGrille; i++) {
        grille[i] = lettresGrille[i];
    }

    // Test de la fonction de sauvegarde
    printf("Test de la fonction de sauvegarde :\n");
    sauvegarderPartie(motsJoueur1, motsJoueur2, scoresJoueur1, scoresJoueur2);

    // Test de la fonction de chargement
    printf("\nTest de la fonction de chargement :\n");
    
    // Modifier certaines valeurs pour vérifier si le chargement fonctionne
    strcpy(nomJoueur1, "TestModif");
    scoreJoueur1 = 0;
    
    if (chargerPartie()) {
        printf("Partie chargée avec succès.\n");
        printf("Nom Joueur 1: %s\n", nomJoueur1);
        printf("Nom Joueur 2: %s\n", nomJoueur2);
        printf("Score Joueur 1: %d\n", scoreJoueur1);
        printf("Score Joueur 2: %d\n", scoreJoueur2);
        printf("Tours joués: %d\n", toursJoues);
        printf("Tours totaux: %d\n", nbreTours);
        
        printf("Grille: ");
        for (int i = 0; i < nbreTotalLettresGrille; i++) {
            printf("%c", grille[i]);
        }
        printf("\n");

        // Appel de la fonction de review
        printf("\nReview de la partie:\n");
        reviewPartie();
    } else {
        printf("Échec du chargement de la partie.\n");
    }

    return 0;
}