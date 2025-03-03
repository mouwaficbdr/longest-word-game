#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"

// D�finition des constantes
const int nbreJoueur = 2;
const int nbreTotalLettresGrille = 9;
const char voyelles[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
const char consonnes[20] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};


//D�finition des variables
char nomJoueur1[10];
char nomJoueur2[10];
int numJoueurCommencerPartie;
int nbreTours;
char choixConsonneVoyelle;


// D�finition des fonctions

//Fonction d'insertion en tete d'un caract�re
void insertCharUp(char data, LCaractere * liste){
    Caractere *newCarac;

    newCarac = (Caractere*) malloc(sizeof(Caractere));
    newCarac->caractere = data;
    newCarac->suiv = liste->head;
    liste->head = newCarac;
}

//Fonction d'insertion en queue d'un caract�re
void insertCharEnd(char data, LCaractere * liste){
    Caractere *p;
    Caractere *newCarac;

    p = liste->head;
    newCarac = (Caractere*) malloc(sizeof(Caractere));
    newCarac->suiv = NULL;

    if(liste->head == NULL){
        liste->head = newCarac;
    }else{
        while(p->suiv != NULL){
            p = p->suiv;
        }
        p->suiv = newCarac;
    }
}

//Fonction de comptage du nombre de noeuds (caract�res) pr�sents dans le liste

int wordLength(LCaractere liste){
    Caractere *p;
    int compte=0;
    p = liste.head;
    while(p != NULL){
        compte++;
        p = p->suiv;
    }

    return compte;
}

//Fonction pour copier le mot form� dans la chaine de caract�res correspondante

char * motFormation(LCaractere liste, int tailleMot){
    char *motFormed;
    Caractere *p;
    int i = 0;

    motFormed = (char*) malloc(tailleMot * sizeof(char));
    p = liste.head;
    while(p != NULL){
        motFormed[i] = p->caractere;
        i++;
        p = p->suiv;
    }
    motFormed[i] = '\0';

    return motFormed;
}

//Fonction pour compter le nombre de caract�res dans un mot

int motLength(char mot[]){
    int i = 0;
    while(mot[i] != '\0'){
        i++;
    }
    return i;
}


//Fonction de v�rification des caract�res
char * validationChar(char mot[], char grilleCaractere[]){
    char validCarac[10];
    int isequal, i=0;

    //On parcourt le tableau contenant le mot de l'utilisateur
    while(mot[i] != '\0'){

        //On initialise � 0 pour dire que le caract�re � l'indice i n'est �gale � aucun parmi ceux de la grille
        isequal = 0;

        //On parcourt la grille de caract�res
        for(int j = 0; j < nbreTotalLettresGrille; j++){

            //Si le caract�re � l'indice i correspond � un caract�re parmi ceux de la grille, isequal passe � 1 pour dire vrai
            //on vide la case contenant le caract�re dans la grille
            //on passe au caract�re suivant
            if(mot[i] == grilleCaractere[j]){
                isequal = 1;
                grilleCaractere[j] = '\0';
                break;
            }
        }

        //Si la variable isequal est toujours � 0, alors le caract�re dans le mot de l'utilisateur n'a pas de correspondant dans la grille
        //On retourne la valeur NULL pour stopper la validation
        //Le mot ne respecte pas les caract�res de la grille 
        if(isequal == 0){
            return NULL;
        }
        i++;
    }

    //si tout s'est bien pass�, on renvoie le mot valide qui respecte les caract�res de la grille
    return mot;
}


int validationMots(char mot[]) {
    FILE *fichier;
    char motDico[35], path[] = "../ .txt";

    path[strcspn(path, " ")] = mot[0];
    int found = 0;

    fichier = fopen(path, "r");
    if (fichier == NULL) {
        return -1;  
    }

    
    while (fgets(motDico, sizeof(motDico), fichier) != NULL) {
        
        motDico[strcspn(motDico, "\n")] = '\0';
        if (strcmp(mot, motDico) == 0) {
            found = 1;
            break;  
        }
    }

    if(found == 1){
        return motLength(mot);
    }

    return 0;

    fclose(fichier);
}
