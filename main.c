#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "fonctions.h"

int main()
{
    initialiserVariables();
    char mot_joueur1[10]="";
    char mot_joueur2[10]="";
    
    // Affichage de l'interface initiale avec tous les éléments visibles
    afficherInterface();
    
    // Afficher les scores et noms des joueurs dès le début
    namePlay1();printf("Joueur 1");
    namePlay2();printf("Joueur 2");
    player1Score();printf("0");
    player2Score();printf("0");
    EntryField();printf("WASOPEDNLQ"); // Affichage de la grille de lettres
    
    // Pause pour permettre au joueur de voir l'interface
    Sleep(1000);
    
    // Afficher l'instruction pour le joueur 1 au-dessus de sa zone de saisie
    gotoxy(EntryFieldX1, EntryFieldY1-1);
    printf("Joueur 1, entrez votre mot:");
    
    // Positionnement du curseur au centre du 2ème rectangle (rectangle du joueur 1)
    player1();
    // Saisie du mot du joueur 1 (fonction qui masque l'entrée)
    centeredhash1(mot_joueur1, 10);
    
    // Afficher l'instruction pour le joueur 2 au-dessus de sa zone de saisie
    gotoxy(EntryFieldX2, EntryFieldY2-1);
    printf("Joueur 2, entrez votre mot:");
    
    // Positionnement du curseur au centre du 3ème rectangle (rectangle du joueur 2)
    player2();
    // Saisie du mot du joueur 2 (fonction qui masque l'entrée)
    centeredhash2(mot_joueur2, 10);
    
    // Affichage des mots dans leurs rectangles respectifs après validation
    centerword1(mot_joueur1);
    centerword2(mot_joueur2);
    
    // Message de fin et attente
    gotoxy(0, height-1);
    printf("Appuyez sur une touche pour quitter...");
    getch();
    
    return 0;
}