#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h> On en aura besoin au niveau du main
#include "fonctions.h"


// Définition des constantes
const int MAX_TOURS = 10;
//Declaration sous forme de constante usage de define eu lieu de const 
#define NBRE_JOUEUR 2
#define NBRE_TOTAL_LETTRES_GRILLE 9
//const int nbreTotalLettresGrille = 9;
const char voyelles[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
const char consonnes[20] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};

// Définition des variables
char nomJoueur1[10];
char nomJoueur2[10];
int numJoueurCommencerPartie;
int nbreTours;
int taille_consonne;
int taille_voyelle;
int index_consonne;
int index_voyelle;
char choixConsonneVoyelle;
char lettresGenerees[NBRE_JOUEUR][NBRE_TOTAL_LETTRES_GRILLE]; 

// Fonction pour générer les caractères aléatoires et donc le mot de la grille 
void genererCaractereAleatoires() {
    taille_consonne = sizeof(consonnes) / sizeof(consonnes[0]); // Taille de la consonne
    taille_voyelle = sizeof(voyelles) / sizeof(voyelles[0]); // Taille de la voyelle

    for (int i = 0; i < NBRE_JOUEUR; i++) {  // Correction ici
        printf("\nJoueur %d, choisissez vos lettres :\n", i + 1);
        
        for (int j = 0; j < NBRE_TOTAL_LETTRES_GRILLE; j++) {
            // Demander à l'utilisateur de choisir une consonne ou une voyelle
            do {
                printf("Tour %d - Choisissez une lettre ('c' pour consonne, 'v' pour voyelle) : ", j + 1);
                scanf(" %c", &choixConsonneVoyelle);
                choixConsonneVoyelle = tolower(choixConsonneVoyelle); // Convertir en minuscule pour éviter les erreurs de casse
            } while (choixConsonneVoyelle != 'c' && choixConsonneVoyelle != 'v');

            // Générer une lettre en fonction du choix
            if (choixConsonneVoyelle == 'c') {
                lettresGenerees[i][j] = consonnes[rand() % taille_consonne];
            } else {
                lettresGenerees[i][j] = voyelles[rand() % taille_voyelle];
            }
        }
    }

    // Affichage des lettres générées pour chaque joueur
    for (int i = 0; i < NBRE_JOUEUR; i++) {
        printf("\nLettres générées pour le Joueur %d : ", i + 1);
        for (int j = 0; j < NBRE_TOTAL_LETTRES_GRILLE; j++) {
            printf("%c ", lettresGenerees[i][j]);
        }
        printf("\n");
    }
}

int main() {
    //srand(time(NULL)); // Initialisation de l'aléatoire et on en aura besoin au niveau du main
    genererCaractereAleatoires(); // Appel de la fonction
    return 0;
}
