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
extern void hashWord(char*word, int size);
extern void gotoxy(int x, int y);
extern void rectangle(int x, int y, int lon, int haut);
extern void interface(); 
#endif