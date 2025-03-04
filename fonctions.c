#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "fonctions.h"

// Définition des constantes
const int MAX_TOURS = 10;
const int nbreJoueur = 2;
const int nbreTotalLettresGrille = 9;
const char voyelles[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
const char consonnes[20] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};

//Définition des variables
char nomJoueur1[10];
char nomJoueur2[10];
int numJoueurCommencerPartie;
int nbreTours;
int taille_consonne;
int taille_voyelle;
int index_consonne;
int index_voyelle;
char choixConsonneVoyelle;
char lettresGenerees[9]; 
char choixmenu;
int width,height;

//Fonction pour afficher le menu 
void chargerPartie() {
    printf("Chargement de la partie...\n");
    // Ajoute ici le code pour charger une partie
}

void nouvellePartie() {
    printf("Nouvelle partie en cours...\n");
    // Ajoute ici le code pour démarrer une nouvelle partie
}
void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        *width = 0;
        *height = 0;
    }
}
void gotoxy(int x, int y) 
{ 
    HANDLE hConsoleOutput; 
    COORD dwCursorPosition; 
    fflush(stdout); 
    dwCursorPosition.X = x; 
    dwCursorPosition.Y = y; 
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition); 
} 

void rectangle(int x, int y, int lon, int haut)
{
    int i;
    gotoxy(x,y); printf("%c",218);
    gotoxy(x+lon,y); printf("%c",191);
    gotoxy(x, y+haut); printf("%c",192);
    gotoxy(x+lon, y+haut); printf("%c",217);     
    for (i=1; i<lon;i++)
    {
        gotoxy(x+i,y); printf("%c",196); 
        gotoxy(x+i,y+haut); printf("%c",196);
    }
    for (i=1; i<haut;i++)
    {
        gotoxy(x,y+i); printf("%c",179); 
        gotoxy(x+lon,y+i); printf("%c",179);
    }
}
void afficherMenu() {
    char choixmenu;
    getConsoleSize(&width,&height);
    int menuWidth = (int)(width * 0.4);
    int menuHeight = (int)(height * 0.4);
    int menuX = (width - menuWidth) / 2;
    int menuY = (height - menuHeight) / 2;
    int upper=menuHeight/3;
    int optionZone=2*menuHeight/3;
    while (1) {
        system("clear || cls");  // Efface l'écran (compatible Linux/Windows)
        rectangle(menuX,menuY,menuWidth,upper);
        rectangle(menuX,menuY+upper+1,menuWidth,optionZone);
       
       gotoxy(menuX+(menuWidth-4)/2,menuY+(upper/2)); printf("MENU");
       
       gotoxy(menuX+3,menuY+upper+optionZone*0.3);printf("X - Charger Partie");
       gotoxy(menuX+3,menuY+upper+optionZone*0.5);printf("Y - Nouvelle Partie");
       gotoxy(menuX+3,menuY+upper+optionZone*0.9);printf("Q - Quitter");
       rectangle(menuX,menuY+menuHeight+1,menuWidth,menuHeight*0.3);
       gotoxy(menuX+3,menuY+menuHeight+(upper)/2);printf("Votre choix : ");


        choixmenu = getchar(); // Récupère l'entrée utilisateur
        while (getchar() != '\n'); // Vide le buffer pour éviter les erreurs

        choixmenu = tolower(choixmenu); // Convertit en minuscule

        switch (choixmenu) {
            case 'x':
                chargerPartie();
                break;
            case 'y':
                nouvellePartie();
                break;
            case 'q':
                printf("Fermeture du programme...\n");
                exit(0);
            default:
                // L'entrée invalide est ignorée, pas d'affichage d'erreur
                break;
        }
    }
}
