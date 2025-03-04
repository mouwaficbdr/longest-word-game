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
extern void getConsoleSize(int *width, int *height) ;
extern void gotoxy(int x, int y) ;
extern void rectangle();
// Déclaration des fonctions
//Fonction pour generer les caracteres aleatoire et donc le mot a 9 lettres
void genererCaracteresAleatoires();
//Fonction pour afficher le menu du jeux 
void afficherMenu();
#endif