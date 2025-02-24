#ifndef FONCTIONS_H
#define FONCTIONS_H

// Déclaration des constantes
extern const int nbreJoueur;
extern const int nbreTotalLettresGrille;
extern const char voyelles[6];
extern const char consonnes[20];

// Déclaration des variables
extern char nomJoueur1[10];
extern char nomJoueur2[10];
extern int numJoueurCommencerPartie;
extern int nbreTours;
extern char choixConsonneVoyelle;

// Déclaration des fonctions
void sauvegarderPartie(const char *nomJoueur1, const char *nomJoueur2, int scoreJoueur1, int scoreJoueur2, int toursJoues, int toursTotaux, const char grille[9]);
int chargerPartie(char *nomJoueur1, char *nomJoueur2, int *scoreJoueur1, int *scoreJoueur2, int *toursJoues, int *toursTotaux, char grille[9]);

#endif