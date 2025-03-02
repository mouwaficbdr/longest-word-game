#ifndef FONCTIONS_H
#define FONCTIONS_H

// Déclaration des constantes
extern const int nbreJoueur;        // Nombre de joueurs dans la partie (fixé à 2)
extern const int nbreTotalLettresGrille;  // Nombre total de lettres dans la grille de jeu (9 lettres)
extern const char voyelles[6];      // Tableau contenant toutes les voyelles disponibles pour le jeu
extern const char consonnes[20];    // Tableau contenant toutes les consonnes disponibles pour le jeu

// Déclaration des variables
extern char nomJoueur1[10];         // Nom du premier joueur (limité à 9 caractères + terminateur)
extern char nomJoueur2[10];         // Nom du deuxième joueur (limité à 9 caractères + terminateur)
extern int numJoueurCommencerPartie; // Numéro du joueur qui commence la partie (1 ou 2)
extern int nbreTours;               // Nombre total de tours pour la partie complète
extern char choixConsonneVoyelle;   // Stocke le choix du joueur ('C' pour consonne, 'V' pour voyelle)

// Déclaration des fonctions

/**
 * Sauvegarde l'état actuel de la partie dans un fichier texte (sauvegarde.txt).
 * Utilise la variable globale nbreTours pour le nombre total de tours.
 * Inclut l'historique des mots joués et leurs scores pour chaque joueur.
 *
 * @param nomJoueur1    Nom du premier joueur
 * @param nomJoueur2    Nom du deuxième joueur
 * @param scoreJoueur1  Score actuel du premier joueur
 * @param scoreJoueur2  Score actuel du deuxième joueur
 * @param toursJoues    Nombre de tours déjà joués
 * @param grille        Tableau de caractères représentant les lettres dans la grille de jeu
 * @param motsJoueur1   Tableau des mots joués par le joueur 1
 * @param motsJoueur2   Tableau des mots joués par le joueur 2
 * @param scoresJoueur1 Tableau des scores obtenus par le joueur 1 pour chaque mot
 * @param scoresJoueur2 Tableau des scores obtenus par le joueur 2 pour chaque mot
 */
void sauvegarderPartie(const char *nomJoueur1, const char *nomJoueur2, int scoreJoueur1, int scoreJoueur2, int toursJoues, const char grille[9], const char motsJoueur1[][20], const char motsJoueur2[][20], const int scoresJoueur1[], const int scoresJoueur2[]);

/**
 * Charge une partie précédemment sauvegardée à partir du fichier sauvegarde.txt.
 * Le nombre total de tours est chargé dans la variable globale nbreTours.
 *
 * @param nomJoueur1   Pointeur pour stocker le nom du premier joueur
 * @param nomJoueur2   Pointeur pour stocker le nom du deuxième joueur
 * @param scoreJoueur1 Pointeur pour stocker le score du premier joueur
 * @param scoreJoueur2 Pointeur pour stocker le score du deuxième joueur
 * @param toursJoues   Pointeur pour stocker le nombre de tours déjà joués
 * @param grille       Tableau où stocker les lettres de la grille de jeu
 *
 * @return 1 si le chargement a réussi, 0 en cas d'échec
 */
int chargerPartie(char *nomJoueur1, char *nomJoueur2, int *scoreJoueur1, int *scoreJoueur2, int *toursJoues, char grille[9]);

/**
 * Affiche un résumé détaillé de la partie sauvegardée.
 * Montre les informations de base de la partie et l'historique des coups joués tour par tour.
 */
void reviewPartie();

#endif