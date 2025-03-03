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



// int validationMots(char mot[]){
//     //D�claration des variables pour la validation dans le disctionnaire
//     FILE *fichier;

//     //Variable qui contient la liste de caract�res de la ligne � laquelle on se retrouve
//     LCaractere *currentMot = malloc(sizeof(LCaractere));

//     //On consid�re 3 variables qui contiendront les positions de fin d�but et milieu lors du d�placement
//     //dans le fichier du dictionnaire
//     long start = 0, middle, end;

//     //Variable qui r�cup�re le nombre de caract�res dans la liste
//     //Ce qui correspond � la taille du mot de la ligne
//     int listLength;

//     //Variable qui r�cup�re chaque caract�re courant lors de notre d�placement caract�re par caract�re
//     //dans le fichier du dictionnaire 
//     char carac;

//     fichier = fopen("dico.txt", "r");

//     if(fichier != NULL){

//         //On se positionne � la fin du fichier
//         fseek(fichier, 0, SEEK_END);

//         //On stocke la position � laquelle on se retrouve � la fin du fichier
//         end = ftell(fichier) - 1;

//         do{
//             //Calcul du milieu du fichier et positionnement � ce niveau
//             middle = start + (end - start)/2;
//             fseek(fichier, middle, SEEK_SET);

//             //On initialise notre liste de caract�res � NULL et on r�cup�re le premier caract�re qu'on 
//             //rencontre
//             currentMot->head = NULL;
//             carac = fgetc(fichier);

//             //Si le premier caract�re rencontr� est \n
//             if(carac == '\n'){

//                 //On fait un bond en arri�re d'un caract�re
//                 fseek(fichier, -2, SEEK_CUR);

//                 //On r�cup�re les valeurs caract�re par caract�re vers l'arri�re
//                 while((carac = fgetc(fichier)) != '\n'){

//                     //On fait une insertion en t�te pour respecter l'ordre des caract�res
//                     //dans le vocabulaire du mot
//                     insertCharUp(carac, currentMot);
//                     fseek(fichier, -2, SEEK_CUR);

//                     //On reprend le processus jusqu'� ce qu'on rencontre un \n
//                     //dans notre marche invers�e
//                 }

//                 //Si le premier caract�re n'est pas un \n
//             }else{

//                 //On fait des bonds en avant (�tant donn� que nous pouvons �tre au beau milieu d'un mot)
//                 //On r�cup�re les caract�res de notre position jusqu'� le fin du mot (jusqu'� le \n)
//                 //Et on les stocke en queue dans notre liste de caract�res
//                 while(carac != '\n'){
//                     insertCharEnd(carac, currentMot);
//                     carac = fgetc(fichier);
//                 }

//                 //On se repositionne ensuite au caract�re
//                 //juste avant celui auquel on �tait avant de commencer le stockage
//                 //Et on fait une r�cup�ration mais en marche invers�e
//                 //Cette fois ci, une insertion en t�te
//                 fseek(fichier, middle - 1, SEEK_SET);
//                 while((carac = fgetc(fichier)) != '\n'){
//                     insertCharUp(carac, currentMot);
//                     fseek(fichier, -2, SEEK_CUR);
//                 }
//             }

//             //Lorsque chaque caract�re du mot est r�cup�r� et bien positionn�

//             //Le nouveau milieur devient celui du d�but du mot stock� caract�re par caract�re
//             middle = ftell(fichier);

//             //Calcul de la taille du mot
//             listLength = wordLength(*currentMot);


//             //Cr�ation dynamique d'une chaine de caract�res
//             //de taille �gale � celle du mot stock� dans la liste
//             char *motFormed = motFormation(*currentMot, listLength + 1);

//             //Si le mot stock� est �gale au mot de l'utilisateur on retourne la taille du mot de l'utilisateur
//             if(strcmp(mot, motFormed) == 0){
//                 //On d�salloue l'espace en m�moire pour la liste de caract�res et le mot form�
//                 free(currentMot);
//                 free(motFormed);

//                 //On ferme le fichier
//                 fclose(fichier);

//                 return motLength(mot);

//                 //sinon si le mot form� est plus grand que le mot de l'utilisateur
//                 //on ignore tous les mots qui viennent apr�s le mot form�
//                 //la nouvelle fin commence � partir du mot form�
//             }else{
//                 if(strcmp(mot, motFormed) < 0){
//                     end = middle;

//                 //si le mot form� est plus petit que le mot de l'utilisateur
//                 //on ignore tous les mots qui viennent avant le mot form� 
//                 //le nouveau d�but commence � partir du mot form�
//                 }else if(strcmp(mot, motFormed) > 0){
//                     start = middle;
//                 }
//             }

//             free(motFormed);

//         //et on reprend le processus jusqu'� ce qu'on ne trouve le mot de l'utilisateur dans le dictionnaire
//         //ou jusqu'� ce que le d�but et la fin ne soit confondu
//         }while(start < end);
        
//         free(currentMot);
//         //Fermuture du fichier
//         fclose(fichier);

//         //La fonction renvoie la valeur 0 si le mot de l'utilisateur n'est pas dans le disctionnaire
//         return 0;
//     }



// }

int validationMots(char mot[]){
    FILE * fichier;


    char /*link[] = "../dico/ .txt",*/ *motDico, *result;
    // link[8] = mot[0];

    int found;

    fichier = fopen("dico.txt", "r");

    if(fichier != NULL){
        do{
            found = 0;
            result = fgets(motDico, 35 * sizeof(char), fichier);
            if(strcmp(mot, motDico) == 0){
                found = 1;
            }
        }while(found == 0 || result != NULL);
        
        if(found == 1){
            return motLength(mot);
        }
        
        return 0;
    }

}