#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

// Définition des constantes
const int nbreJoueur = 2;
const int nbreTotalLettresGrille = 9;
const char voyelles[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
const char consonnes[20] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};


//Définition des variables
char nomJoueur1[10];
char nomJoueur2[10];
int numJoueurCommencerPartie;
int nbreTours;
char choixConsonneVoyelle;

// Définition des fonctions

/**
 * Sauvegarde l'état actuel de la partie dans un fichier texte (sauvegarde.txt).
 * Utilise la variable globale nbreTours pour le nombre total de tours.
 * Inclut l'historique des mots joués et leurs scores pour chaque joueur.
 */
void sauvegarderPartie(const char *nomJoueur1, const char *nomJoueur2, int scoreJoueur1, int scoreJoueur2, int toursJoues, const char grille[9], const char motsJoueur1[][20], const char motsJoueur2[][20], const int scoresJoueur1[], const int scoresJoueur2[]) {
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    fprintf(fichier, "Nom Joueur 1: %s\n", nomJoueur1);
    fprintf(fichier, "Nom Joueur 2: %s\n", nomJoueur2);
    fprintf(fichier, "Score Joueur 1: %d\n", scoreJoueur1);
    fprintf(fichier, "Score Joueur 2: %d\n", scoreJoueur2);
    fprintf(fichier, "Tours joués: %d\n", toursJoues);
    fprintf(fichier, "Tours totaux: %d\n", nbreTours);
    fprintf(fichier, "Grille: ");
    for (int i = 0; i < 9; i++) {
        fprintf(fichier, "%c", grille[i]);
    }
    fprintf(fichier, "\n");

    fprintf(fichier, "Review de la partie:\n");
    for (int i = 0; i < toursJoues; i++) {
        fprintf(fichier, "Tour %d:\n", i + 1);
        fprintf(fichier, "Joueur 1 - Mot: %s, Score: %d\n", motsJoueur1[i], scoresJoueur1[i]);
        fprintf(fichier, "Joueur 2 - Mot: %s, Score: %d\n", motsJoueur2[i], scoresJoueur2[i]);
    }

    fclose(fichier);
    printf("Partie sauvegardée avec succès.\n");
}

/**
 * Charge une partie précédemment sauvegardée à partir du fichier sauvegarde.txt.
 * Le nombre total de tours est chargé dans la variable globale nbreTours.
 */
int chargerPartie(char *nomJoueur1, char *nomJoueur2, int *scoreJoueur1, int *scoreJoueur2, int *toursJoues, char grille[9]) {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return 0;
    }

    // Lecture des noms des joueurs
    fscanf(fichier, "Nom Joueur 1: %s\n", nomJoueur1);
    fscanf(fichier, "Nom Joueur 2: %s\n", nomJoueur2);

    // Lecture des scores
    fscanf(fichier, "Score Joueur 1: %d\n", scoreJoueur1);
    fscanf(fichier, "Score Joueur 2: %d\n", scoreJoueur2);

    // Lecture du nombre de tours
    fscanf(fichier, "Tours joués: %d\n", toursJoues);
    fscanf(fichier, "Tours totaux: %d\n", &nbreTours);

    // Lecture de la grille
    fscanf(fichier, "Grille: %c%c%c%c%c%c%c%c%c\n", &grille[0], &grille[1], &grille[2], &grille[3], &grille[4], &grille[5], &grille[6], &grille[7], &grille[8]);

    fclose(fichier);
    printf("Partie chargée avec succès.\n");
    return 1;
}

/**
 * Affiche un résumé détaillé de la partie sauvegardée.
 * Montre les informations de base de la partie et l'historique des coups joués tour par tour.
 */
void reviewPartie() {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    char nomJoueur1[10], nomJoueur2[10];
    int scoreJoueur1, scoreJoueur2, toursJoues;
    char grille[9];
    char ligne[100];
    int toursTotauxTemp; // Variable temporaire pour lire la valeur

    // Lecture des informations de base
    fscanf(fichier, "Nom Joueur 1: %s\n", nomJoueur1);
    fscanf(fichier, "Nom Joueur 2: %s\n", nomJoueur2);
    fscanf(fichier, "Score Joueur 1: %d\n", &scoreJoueur1);
    fscanf(fichier, "Score Joueur 2: %d\n", &scoreJoueur2);
    fscanf(fichier, "Tours joués: %d\n", &toursJoues);
    fscanf(fichier, "Tours totaux: %d\n", &toursTotauxTemp);
    fscanf(fichier, "Grille: %c%c%c%c%c%c%c%c%c\n", &grille[0], &grille[1], &grille[2], &grille[3], &grille[4], &grille[5], &grille[6], &grille[7], &grille[8]);

    // Affichage des informations générales
    printf("Informations de la partie:\n");
    printf("Joueur 1: %s (Score: %d)\n", nomJoueur1, scoreJoueur1);
    printf("Joueur 2: %s (Score: %d)\n", nomJoueur2, scoreJoueur2);
    printf("Progression: %d tours joués sur %d\n", toursJoues, toursTotauxTemp);
    printf("Grille actuelle: ");
    for (int i = 0; i < 9; i++) {
        printf("%c ", grille[i]);
    }
    printf("\n\n");

    // Lecture de la ligne "Review de la partie:"
    fgets(ligne, sizeof(ligne), fichier);

    // Lecture de la review de la partie
    printf("Historique des tours:\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    fclose(fichier);
}