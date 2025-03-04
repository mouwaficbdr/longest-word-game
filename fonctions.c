#include <stdio.h>
#include <stdlib.h>
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

//Fonction pour generer les caracteres aleatoires et donc le mot de la grille 
void genererCaractereAleatoires(int nbreTotalLettresGrille) {
    taille_consonne = sizeof(consonnes) / sizeof(consonnes[0]);//taille de la consonne
    taille_voyelle = sizeof(voyelles) / sizeof(voyelles[0]);//taille de la voyelle

    for (int i = 0; i < nbreTotalLettresGrille; i++ ) {
        // Demander à l'utilisateur de choisir une consonne ou une voyelle
        do {
            printf("Tour %d - Choisissez une lettre ('c' pour consonne, 'v' pour voyelle) : ", i + 1);
            scanf(" %c", &choixConsonneVoyelle);
            choixConsonneVoyelle = tolower(choixConsonneVoyelle); // Convertir en minuscule pour éviter les erreurs de casse
        } while (choixConsonneVoyelle != 'c' && choixConsonneVoyelle != 'v');

        // Générer une lettre en fonction du choix
        if (choixConsonneVoyelle == 'c') {
            lettresGenerees[i] = consonnes[rand() % taille_consonne];
        } else {
            lettresGenerees[i] = voyelles[rand() % taille_voyelle];
        }
    }

    // Affichage des lettres générées
    printf("\nLettres générées : ");
    for (int i = 0; i < nbreTotalLettresGrille; i++) {
        printf("%c ", lettresGenerees[i]);
    }
    printf("\n");
}
