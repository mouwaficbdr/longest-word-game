#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <string.h>
#include <ctype.h>

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

/**
 * @brief 
 * Ranger le dictionnaire suivant les lettres de l'alphabet 
 */
void RangerDico();

#endif