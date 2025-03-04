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
    initialiserInterface();
    
    // Pause pour permettre au joueur de voir l'interface
    Sleep(1000);
    
    // Demander le mot au joueur 1
    demanderMotJoueur1(mot_joueur1);
    
    // Demander le mot au joueur 2
    demanderMotJoueur2(mot_joueur2);
    
    // Affichage des mots dans leurs rectangles respectifs après validation
    centerword1(mot_joueur1);
    centerword2(mot_joueur2);
    
    // Message de fin et attente
    gotoxy(0, height-1);
    printf("Appuyez sur une touche pour quitter...");
    getch();
    
    return 0;
}