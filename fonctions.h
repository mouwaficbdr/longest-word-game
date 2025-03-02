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

//Déclaration des structures

typedef struct Caractere Caractere;
typedef struct LCaractere LCaractere;

struct Caractere{
    char caractere;
    Caractere * suiv;
};

struct LCaractere{
    Caractere *head;
};

// Déclaration des fonctions

//La fonction validationChar vérifie si un mot respecte les critères de la grille (si tous ses caractères sont conformes à ceux donnés par la grille)
char * validationChar(char mot[], char grilleCaractere[]);

//Fonction d'insertion d'un caractère en tête dans la liste de caractères
void insertCharUp(char data, LCaractere * liste);

//Fonction d'insertion d'un caractère en queue dans la liste de caractères
void insertCharEnd(char data, LCaractere * liste);

//Fonction pour déterminer la taille du mot formé à partir de la liste de caractères ordonnés
int wordLength(LCaractere liste);

//Fonction pour former un mot à partir des caractères de la liste de caractères ordonnés
char * motFormation(LCaractere liste, int tailleMot);

//Fonction pour déterminer la taille de mot
int motLength(char mot[]);

//La fonction validationMots vérifie si un mot se retrouve dans le dictionnaire. Si oui, il renvoie la taille du mot (correspondant au score du joueur) si non il renvoie 0 pour indiquer que le mot n'existe pas dans le dictionnaire
int validationMots(char mot[]);


#endif