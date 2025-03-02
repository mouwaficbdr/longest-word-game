#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

//Fonction d'insertion en tete d'un caractère
void insertCharUp(char data, LCaractere * liste){
    Caractere *newCarac;

    newCarac = (Caractere*) malloc(sizeof(Caractere));
    newCarac->caractere = data;
    newCarac->suiv = liste->head;
    liste->head = newCarac;
}

//Fonction d'insertion en queue d'un caractère
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

//Fonction de comptage du nombre de noeuds (caractères) présents dans le liste

int wordLength(LCaractere liste){
    Caractere *p;
    int compte;
    p = liste.head;
    while(p != NULL){
        compte++;
        p = p->suiv;
    }

    return compte;
}

//Fonction pour copier le mot formé dans la chaine de caractères correspondante

char * motFormation(LCaractere liste, int tailleMot){
    char *motFormed;
    Caractere *p;
    int i = 0;

    motFormed = (char*) malloc(tailleMot * sizeof(char));
    p = liste.head;
    while(p != NULL){
        motFormed[i] = p->caractere;
        i++;
    }

    return motFormed;
}

//Fonction pour compter le nombre de caractères dans un mot

int motLength(char mot[]){
    int i = 0;
    while(mot[i] != '\0'){
        i++;
    }
    return i;
}

//Fonction de vérification des caractères
char * validationChar(char mot[], char grilleCaractere[]){
    char validCarac[10];
    int isequal, i=0;

    //On parcourt le tableau contenant le mot de l'utilisateur
    while(mot[i] != '\0'){

        //On initialise à 0 pour dire que le caractère à l'indice i n'est égale à aucun parmi ceux de la grille
        isequal = 0;

        //On parcourt la grille de caractères
        for(int j = 0; j < nbreTotalLettresGrille; j++){

            //Si le caractère à l'indice i correspond à un caractère parmi ceux de la grille, isequal passe à 1 pour dire vrai
            //on vide la case contenant le caractère dans la grille
            //on passe au caractère suivant
            if(mot[i] == grilleCaractere[j]){
                isequal = 1;
                grilleCaractere[j] = '\0';
                break;
            }
        }

        //Si la variable isequal est toujours à 0, alors le caractère dans le mot de l'utilisateur n'a pas de correspondant dans la grille
        //On retourne la valeur NULL pour stopper la validation
        //Le mot ne respecte pas les caractères de la grille 
        if(isequal == 0){
            return NULL;
        }
        i++;
    }

    //si tout s'est bien passé, on renvoie le mot valide qui respecte les caractères de la grille
    return mot;
}



int validationMots(char mot[]){
    //Déclaration des variables pour la validation dans le disctionnaire
    FILE *fichier;

    //Variable qui contient la liste de caractères de la ligne à laquelle on se retrouve
    LCaractere *currentMot = malloc(sizeof(LCaractere));

    //On considère 3 variables qui contiendront les positions de fin début et milieu lors du déplacement
    //dans le fichier du dictionnaire
    long start = 0, middle, end;

    //Variable qui récupère le nombre de caractères dans la liste
    //Ce qui correspond à la taille du mot de la ligne
    int listLength;

    //Variable qui récupère chaque caractère courant lors de notre déplacement caractère par caractère
    //dans le fichier du dictionnaire 
    char carac;

    fichier = fopen("dico.txt", "r");

    if(fichier != NULL){

        //On se positionne à la fin du fichier
        fseek(fichier, 0, SEEK_END);

        //On stocke la position à laquelle on se retrouve à la fin du fichier
        end = ftell(fichier) - 1;

        do{
            //Calcul du milieu du fichier et positionnement à ce niveau
            middle = start + (end - start)/2;
            fseek(fichier, middle, SEEK_SET);

            //On initialise notre liste de caractères à NULL et on récupère le premier caractère qu'on 
            //rencontre
            currentMot->head = NULL;
            carac = fgetc(fichier);

            //Si le premier caractère rencontré est \n
            if(carac == '\n'){

                //On fait un bond en arrière d'un caractère
                fseek(fichier, -2, SEEK_CUR);

                //On récupère les valeurs caractère par caractère vers l'arrière
                while((carac = fgetc(fichier)) != '\n'){

                    //On fait une insertion en tête pour respecter l'ordre des caractères
                    //dans le vocabulaire du mot
                    insertCharUp(carac, currentMot);
                    fseek(fichier, -2, SEEK_CUR);

                    //On reprend le processus jusqu'à ce qu'on rencontre un \n
                    //dans notre marche inversée
                }

                //Si le premier caractère n'est pas un \n
            }else{

                //On fait des bonds en avant (étant donné que nous pouvons être au beau milieu d'un mot)
                //On récupère les caractères de notre position jusqu'à le fin du mot (jusqu'à le \n)
                //Et on les stocke en queue dans notre liste de caractères
                while(carac != '\n'){
                    insertCharEnd(carac, currentMot);
                    carac = fgetc(fichier);
                }

                //On se repositionne ensuite au caractère
                //juste avant celui auquel on était avant de commencer le stockage
                //Et on fait une récupération mais en marche inversée
                //Cette fois ci, une insertion en tête
                fseek(fichier, middle - 1, SEEK_SET);
                while((carac = fgetc(fichier)) != '\n'){
                    insertCharUp(carac, currentMot);
                    fseek(fichier, -2, SEEK_CUR);
                }
            }

            //Lorsque chaque caractère du mot est récupéré et bien positionné

            //Le nouveau milieur devient celui du début du mot stocké caractère par caractère
            middle = ftell(fichier);

            //Calcul de la taille du mot
            listLength = wordLength(*currentMot);


            //Création dynamique d'une chaine de caractères
            //de taille égale à celle du mot stocké dans la liste
            char *motFormed = motFormation(*currentMot, listLength + 1);

            //Si le mot stocké est égale au mot de l'utilisateur on retourne la taille du mot de l'utilisateur
            if(strcmp(mot, motFormed) == 0){
                //On désalloue l'espace en mémoire pour la liste de caractères et le mot formé
                free(currentMot);
                free(motFormed);

                //On ferme le fichier
                fclose(fichier);

                return motLength(mot);

                //sinon si le mot formé est plus grand que le mot de l'utilisateur
                //on ignore tous les mots qui viennent après le mot formé
                //la nouvelle fin commence à partir du mot formé
            }else{
                if(strcmp(mot, motFormed) < 0){
                    end = middle;

                //si le mot formé est plus petit que le mot de l'utilisateur
                //on ignore tous les mots qui viennent avant le mot formé 
                //le nouveau début commence à partir du mot formé
                }else if(strcmp(mot, motFormed) > 0){
                    start = middle;
                }
            }

            free(motFormed);

        //et on reprend le processus jusqu'à ce qu'on ne trouve le mot de l'utilisateur dans le dictionnaire
        //ou jusqu'à ce que le début et la fin ne soit confondu
        }while(start < end);
        
        free(currentMot);
        //Fermuture du fichier
        fclose(fichier);

        //La fonction renvoie la valeur 0 si le mot de l'utilisateur n'est pas dans le disctionnaire
        return 0;
    }



}