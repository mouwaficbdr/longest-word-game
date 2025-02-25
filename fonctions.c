#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

// Définition des constantes
const int nbreJoueur = 2;
const int nbreTotalLettresGrille = 9;
const char voyelles[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
const char consonnes[20] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};


//Définition des variables
char nomJoueur1[10];
char nomJoueur2[10];
int numJoueurCommencerPartie;
int nbreTours;
char choixConsonneVoyelle;

// Définition des fonctions

//Fonction de vérification des caractères
char * validationChar(char mot[], char grilleCaractere[]){
    char validCarac[10];
    int isequal, i;

    //On parcourt le tableau contenant le mot de l'utilisateur
    while(mot[i] != "\0"){

        //On initialise à 0 pour dire que le caractère à l'indice i n'est égale à aucun parmi ceux de la grille
        isequal = 0;

        //On parcourt la grille de caractères
        for(int j = 0; j < nbreTotalLettresGrille; j++){

            //Si le caractère à l'indice i correspond à un caractère parmi ceux de la grille, isequal passe à 1 pour dire vrai
            //on vide la case contenant le caractère dans la grille
            //on passe au caractère suivant
            if(mot[i] == grilleCaractere[j]){
                isequal = 1;
                grilleCaractere[j] = "\0";
                break;
            }
        }

        //Si la variable isequal est toujours à 0, alors le caractère dans le mot de l'utilisateur n'a pas de correspondant dans la grille
        //On retourne la valeur 0 pour stopper la validation
        //Le mot ne respecte pas les caractères de la grille 
        if(isequal == 0){
            return 0;
        }
        i++;
    }

    //si tout s'est bien passé, on renvoie le mot valide qui respecte les caractères de la grille
    return mot;
}


void validationMots(char mot[]){
    int *position, i = 0;
    //Pointeur sur le fichier du dictionnaire
    FILE * dico = NULL; 

    //Ouverture du dictionnaire
    dico = fopen("dico.txt", "r");
    int notFound = 0;
    char motDico[10] = "";
    if(dico != NULL){
        fseek(dico, 0, SEEK_END);
        *position = ftell(dico);
        fseek(dico, *position/2, SEEK_SET);
        do{
            fgets(motDico, 9, dico);
            if(strcmp(mot, motDico) == 0){
                notFound = 1;
            }else{
                if(strcmp(mot, motDico) < 0){
                    *position = ftell(dico);
                    fseek(dico, -(*position/2), SEEK_CUR);
                }else{
                    *position = ftell(dico);
                    fseek(dico, (*position/2), SEEK_CUR);
                }
            }
        }while(!notFound);

        if(notFound){
            while(mot[i] != "\0"){
                i++;
                return i;
            }
        }else{
            return 0;
        }

        fclose(dico);
    }
}