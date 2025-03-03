#ifndef FONCTIONS_H
#define FONCTIONS_H

// D�claration des constantes
extern const int nbreJoueur;
extern const int nbreTotalLettresGrille;
extern const char voyelles[6];
extern const char consonnes[20];

// D�claration des variables
extern char nomJoueur1[10];
extern char nomJoueur2[10];
extern int numJoueurCommencerPartie;
extern int nbreTours;
extern char choixConsonneVoyelle;

//D�claration des structures

typedef struct Caractere Caractere;
typedef struct LCaractere LCaractere;

struct Caractere{
    char caractere;
    Caractere * suiv;
};

struct LCaractere{
    Caractere *head;
};

// D�claration des fonctions

//La fonction validationChar v�rifie si un mot respecte les crit�res de la grille (si tous ses caract�res sont conformes � ceux donn�s par la grille)
char * validationChar(char mot[], char grilleCaractere[]);

//Fonction d'insertion d'un caract�re en t�te dans la liste de caract�res
void insertCharUp(char data, LCaractere * liste);

//Fonction d'insertion d'un caract�re en queue dans la liste de caract�res
void insertCharEnd(char data, LCaractere * liste);

//Fonction pour d�terminer la taille du mot form� � partir de la liste de caract�res ordonn�s
int wordLength(LCaractere liste);

//Fonction pour former un mot � partir des caract�res de la liste de caract�res ordonn�s
char * motFormation(LCaractere liste, int tailleMot);

//Fonction pour d�terminer la taille de mot
int motLength(char mot[]);

//La fonction validationMots v�rifie si un mot se retrouve dans le dictionnaire. Si oui, il renvoie la taille du mot (correspondant au score du joueur) si non il renvoie 0 pour indiquer que le mot n'existe pas dans le dictionnaire
int validationMots(char mot[]);


#endif

