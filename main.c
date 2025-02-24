#include <stdio.h>
#include "fonctions.h"

int main()
{
    char nomJoueur1[10] = "Joueur1";
    char nomJoueur2[10] = "Joueur2";
    int scoreJoueur1 = 10;
    int scoreJoueur2 = 15;
    int toursJoues = 3;
    int toursTotaux = 5;
    char grille[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

    // Test de la fonction de sauvegarde
    printf("Test de la fonction de sauvegarde :\n");
    sauvegarderPartie(nomJoueur1, nomJoueur2, scoreJoueur1, scoreJoueur2, toursJoues, toursTotaux, grille);

    // Test de la fonction de chargement
    printf("\nTest de la fonction de chargement :\n");
    char nomJoueur1Charge[10];
    char nomJoueur2Charge[10];
    int scoreJoueur1Charge, scoreJoueur2Charge, toursJouesCharge, toursTotauxCharge;
    char grilleCharge[9];

    if (chargerPartie(nomJoueur1Charge, nomJoueur2Charge, &scoreJoueur1Charge, &scoreJoueur2Charge, &toursJouesCharge, &toursTotauxCharge, grilleCharge)) {
        printf("Partie chargée avec succès.\n");
        printf("Nom Joueur 1: %s\n", nomJoueur1Charge);
        printf("Nom Joueur 2: %s\n", nomJoueur2Charge);
        printf("Score Joueur 1: %d\n", scoreJoueur1Charge);
        printf("Score Joueur 2: %d\n", scoreJoueur2Charge);
        printf("Tours joués: %d\n", toursJouesCharge);
        printf("Tours totaux: %d\n", toursTotauxCharge);
        printf("Grille: ");
        for (int i = 0; i < 9; i++) {
            printf("%c", grilleCharge[i]);
        }
        printf("\n");
    } else {
        printf("Échec du chargement de la partie.\n");
    }

    return 0;
}