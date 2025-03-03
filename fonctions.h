#ifndef FONCTIONS_H
#define FONCTIONS_H

// D�claration des constantes
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

// Variables globales supplémentaires pour l'état du jeu
extern int scoreJoueur1;            // Score actuel du premier joueur
extern int scoreJoueur2;            // Score actuel du deuxième joueur
extern int toursJoues;              // Nombre de tours déjà joués
extern char grille[9];             // Tableau représentant les lettres dans la grille de jeu

//D�claration des structures

// D�claration des fonctions

//Fonction pour d�terminer la taille de mot
int motLength(char mot[]);

/**
 * Vérifie si le mot de l'utilisateur respecte les caractères de la grille
 * Si oui, elle renvoit la valeur 1 
 * Sinon, elle renvoit la valeur 0
 */
int validationChar(char mot[], char grilleCaractere[]);


//La fonction validationMots v�rifie si un mot se retrouve dans le dictionnaire. Si oui, il renvoie la taille du mot (correspondant au score du joueur) si non il renvoie 0 pour indiquer que le mot n'existe pas dans le dictionnaire
int validationMots(char mot[]);

/**
 * Sauvegarde l'état actuel de la partie dans un fichier texte (sauvegarde.txt).
 * Utilise les variables globales pour les informations de la partie (noms, scores, tours).
 * La grille n'est pas sauvegardée car elle sera régénérée à la reprise de la partie.
 * Inclut l'historique des mots joués et leurs scores pour chaque joueur.
 *
 * @param motsJoueur1   Tableau des mots joués par le joueur 1
 * @param motsJoueur2   Tableau des mots joués par le joueur 2
 * @param scoresJoueur1 Tableau des scores obtenus par le joueur 1 pour chaque mot
 * @param scoresJoueur2 Tableau des scores obtenus par le joueur 2 pour chaque mot
 */
void sauvegarderPartie(const char motsJoueur1[][20], const char motsJoueur2[][20], const int scoresJoueur1[], const int scoresJoueur2[]);

/**
 * Charge une partie précédemment sauvegardée à partir du fichier sauvegarde.txt.
 * Les données sont chargées directement dans les variables globales définies.
 * La grille n'est pas chargée car elle sera régénérée à la reprise de la partie.
 * 
 * @return 1 si le chargement a réussi, 0 en cas d'échec
 */
int chargerPartie(void);

/**
 * Affiche un résumé détaillé de la partie sauvegardée.
 * Montre les informations de base de la partie (noms, scores, progression) 
 * et l'historique des coups joués tour par tour.
 * La grille n'est pas affichée car elle n'est pas sauvegardée.
 */
void reviewPartie();

/**
 * Vérifie si une sauvegarde existe déjà dans le fichier sauvegarde.txt.
 * 
 * @return 1 si une sauvegarde existe et est valide, 0 sinon
 */
int verifSauvegarde(void);

/**
 * Efface le fichier de sauvegarde s'il existe.
 * Cette fonction permet de supprimer une sauvegarde existante
 * avant de commencer une nouvelle partie.
 * 
 * @return 1 si la sauvegarde a été effacée avec succès ou n'existait pas, 0 en cas d'échec
 */
int effacerSauvegarde(void);

#endif

