#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

//Fonction pour afficher le menu 
void chargerPartie() {
    printf("Chargement de la partie...\n");
    // Ajoute ici le code pour charger une partie
}

void nouvellePartie() {
    printf("Nouvelle partie en cours...\n");
    // Ajoute ici le code pour démarrer une nouvelle partie
}

void afficherMenu() {
    char choixmenu;

    while (1) {
        system("clear || cls");  // Efface l'écran (compatible Linux/Windows)

        // Affichage du menu dans un rectangle
        printf("\n");
        printf("*            MENU                *\n");
        printf("\n");
        printf("* X - Charger Partie             *\n");
        printf("* Y - Nouvelle Partie            *\n");
        printf("* Q - Quitter                    *\n");
        printf("\n");
        printf("  Votre choix : ");

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
