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

// Définition des variables globales supplémentaires
int scoreJoueur1 = 0;           // Score du joueur 1, initialisé à 0
int scoreJoueur2 = 0;           // Score du joueur 2, initialisé à 0
int toursJoues = 0;             // Nombre de tours joués, initialisé à 0
char grille[9] = {0};          // Grille de jeu avec taille exacte pour stocker nbreTotalLettresGrille caractères

// Définition des fonctions

/**
 * Sauvegarde l'état actuel de la partie dans un fichier texte (sauvegarde.txt).
 * Utilise les variables globales pour les informations de la partie.
 * Inclut l'historique des mots joués et leurs scores pour chaque joueur.
 */
void sauvegarderPartie(const char motsJoueur1[][20], const char motsJoueur2[][20], const int scoresJoueur1[], const int scoresJoueur2[]) {
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
    
    // La grille n'est plus sauvegardée car elle sera régénérée à la reprise

    fprintf(fichier, "Review de la partie:\n");
    for (int i = 0; i < toursJoues; i++) {
        fprintf(fichier, "Tour %d:\n", i + 1);
        fprintf(fichier, "%s - Mot: %s, Score: %d\n", nomJoueur1, motsJoueur1[i], scoresJoueur1[i]);
        fprintf(fichier, "%s - Mot: %s, Score: %d\n", nomJoueur2, motsJoueur2[i], scoresJoueur2[i]);
    }

    fclose(fichier);
    printf("Partie sauvegardée avec succès.\n");
}

/**
 * Charge une partie précédemment sauvegardée à partir du fichier sauvegarde.txt.
 * Les données sont chargées directement dans les variables globales définies dans le module.
 * 
 * @return 1 si le chargement a réussi, 0 en cas d'échec
 */
int chargerPartie(void) {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return 0;
    }

    // Lecture des noms des joueurs
    fscanf(fichier, "Nom Joueur 1: %s\n", nomJoueur1);
    fscanf(fichier, "Nom Joueur 2: %s\n", nomJoueur2);

    // Lecture des scores
    fscanf(fichier, "Score Joueur 1: %d\n", &scoreJoueur1);
    fscanf(fichier, "Score Joueur 2: %d\n", &scoreJoueur2);

    // Lecture du nombre de tours
    fscanf(fichier, "Tours joués: %d\n", &toursJoues);
    fscanf(fichier, "Tours totaux: %d\n", &nbreTours);

    // La grille n'est plus chargée car elle sera régénérée à la reprise

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

    char nomJoueurSauvegarde1[10], nomJoueurSauvegarde2[10];
    int scoreJoueurSauvegarde1, scoreJoueurSauvegarde2, toursJouesSauvegarde;
    char ligne[100];
    int toursTotauxTemp; // Variable temporaire pour lire la valeur

    // Lecture des informations de base
    fscanf(fichier, "Nom Joueur 1: %s\n", nomJoueurSauvegarde1);
    fscanf(fichier, "Nom Joueur 2: %s\n", nomJoueurSauvegarde2);
    fscanf(fichier, "Score Joueur 1: %d\n", &scoreJoueurSauvegarde1);
    fscanf(fichier, "Score Joueur 2: %d\n", &scoreJoueurSauvegarde2);
    fscanf(fichier, "Tours joués: %d\n", &toursJouesSauvegarde);
    fscanf(fichier, "Tours totaux: %d\n", &toursTotauxTemp);
    
    // La grille n'est plus affichée car elle n'est plus sauvegardée

    // Affichage des informations générales
    printf("Informations de la partie:\n");
    printf("Joueur 1: %s (Score: %d)\n", nomJoueurSauvegarde1, scoreJoueurSauvegarde1);
    printf("Joueur 2: %s (Score: %d)\n", nomJoueurSauvegarde2, scoreJoueurSauvegarde2);
    printf("Progression: %d tours joués sur %d\n", toursJouesSauvegarde, toursTotauxTemp);
    
    // Lecture de la ligne "Review de la partie:"
    fgets(ligne, sizeof(ligne), fichier);

    // Lecture de la review de la partie
    printf("Historique des tours:\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    fclose(fichier);
}