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

// Définition des fonctions
    //Fonction pour generer les lettres aleatoire
    void genererVariablesAleatoires()
        {
                // Demander à l'utilisateur de choisir entre 'c' (consonne) ou 'v' (voyelle)
    do {
        printf("Choisissez une lettre ('c' pour consonne, 'v' pour voyelle) : ");
        getch(" %c", &choixConsonneVoyelle); // Pour cacher la saisi de l'utilisateur
        // Convertir la lettre en minuscule pour ignorer la casse
        choixConsonneVoyelle = tolower(choixConsonneVoyelle);

    } while (choixConsonneVoyelle != 'c' && choixConsonneVoyelle != 'v'); // Tant que l'entrée n'est ni 'c' ni 'v', on redemande

    // Si l'utilisateur a choisi 'c' (consonne)
    if (choixConsonneVoyelle == 'c') {
        taille_consonne = sizeof(consonnes) / sizeof(consonnes[0]); // Calculer la taille du tableau consonnes
        index_consonne = rand() % taille_consonne; // Générer un index aléatoire dans ce tableau
        return consonnes[index_consonne]; // Retourner la consonne choisie aléatoirement
    }
    // Si l'utilisateur a choisi 'v' (voyelle)
    else if (choixConsonneVoyelle == 'v') {
        taille_voyelle = sizeof(voyelles) / sizeof(voyelles[0]); // Calculer la taille du tableau voyelles
        index_voyelle = rand() % taille_voyelle; // Générer un index aléatoire dans ce tableau
        return voyelles[index_voyelle]; // Retourner la voyelle choisie aléatoirement
    }

        }

    //Fonction pour demander a l'utilisateur d'entrer une lettre entre consonne et voyelle (susceptible d'etre supprimer)
