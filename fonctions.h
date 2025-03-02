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
extern int scorefieldX1, scorefieldY1, scorefieldLong, scorefieldHeight;
extern int scorefieldCursorX1, scorefieldCursorY1;
extern int mainframeX, mainframeY, mainframeLong, mainframeHeight;
extern int scorefieldX2, scorefieldY2;
extern int gameEntryFieldX, gameEntryFieldY, gameEntryFieldHeight, gameEntryFieldLong;
extern int EntryFieldX1, EntryFieldY1, EntryFieldLong, EntryFieldHeight;
extern int EntryFieldX2, EntryFieldY2;
extern int AIX, AIY;
extern int play1CursorX, play1CursorY;
extern int play2CursorX, play2CursorY;
extern int AImoveX, AImoveY;
extern int score1moveX, score1moveY;
extern int score2moveX, score2moveY;
extern int gambaseX, gamebaseY;

// Déclaration des fonctions
extern void hashWord(char*word, int size);
extern void gotoxy(int x, int y);
extern void rectangle(int x, int y, int lon, int haut);
extern void afficherInterface();
extern void initialiserVariables();
extern void player1();
extern void player2();
extern void AImove();
extern void player1Score();
extern void player2Score();
extern void EntryField();


#endif
