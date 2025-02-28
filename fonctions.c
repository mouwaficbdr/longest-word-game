#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"

// Définition des constantes
const int nbreJoueur = 2;
const int nbreTotalLettresGrille = 12;
const char voyelles[6] = {'A', 'E', 'I', 'O', 'U', 'Y'};
const char consonnes[20] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};


//Définition des variables
char nomJoueur1[10];
char nomJoueur2[10];
int numJoueurCommencerPartie;
int nbreTours;
char choixConsonneVoyelle;

// Définition des fonctions

void RangerDico(){
    char grille[]="abcdefghijklmnopqrstuvwxyz";
     char chaine[30];
      int i=0;
      int once=1;
      int nbr=0;
      char accent[]="àáâäæçèéêëìíîïòóôöœùú";

    //Le laisser passer permet de d'insérer dans le même fichier les caractères les mot 
    //commencant par un caractère accentué dérivant de la même lettre
      int laisserPasser=0;
      char *inserer=NULL;
      FILE *dico=fopen("dico.txt","r");

   while(!feof(dico)){
   //On parcourt la grille des lettres de l'alphabet
      while(grille[i]!='\0'){

         chaine[0]=grille[i];
          char name[6]={grille[i],'.','t','x','t'};
          FILE *fichier=fopen(name,"a");
   
   //Tant que pour un mot sa premiere lettre est la lettre courante de la grille ou un accentué dérivé (laisserPasser)
   //On l'insère dans le fichier 
        while(chaine[0]==grille[i] || laisserPasser){
   
          if(once){
            fgets(chaine,30,dico);
             chaine[0]=tolower(chaine[0]);
             once=0;
           }
          inserer=malloc(sizeof(char)*(strlen(chaine)+1));
           strcpy (inserer,chaine);
            fputs(inserer,fichier);
            nbr++;
           fgets(chaine,30,dico);
           chaine[0]=tolower(chaine[0]);
            printf("%s",inserer);
           laisserPasser=0;
           for(int j=0; j<strlen(accent); j++){
           if(chaine[0]==accent[j]){
             laisserPasser=1;
               break;
          }
                   }
               }
                   fputs(inserer,fichier);
                   nbr++;
                   free(inserer);
                   fclose(fichier);
                   i++;
               }
           }
               fclose(dico);
   
    }

   
    int validationChar(char mot[], char grilleCaractere[]){
        int isequal, i=0;
        if(strlen(mot)>nbreTotalLettresGrille){
            return 0;
        }
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
            //On retourne la valeur 0 pour stopper la validation
            //Le mot ne respecte pas les caractères de la grille
            if(isequal == 0){
                return 0;
            }
            i++;
        }
    
        //si tout s'est bien passé, on renvoie 1
        return 1;
    }
    
    
    void removeSameChar(char *chaine, char c) {
       int i=0;
       int j=0;
       //On compte le nombre d'occurence de la lettre dans le mot et on alloue de la memoire pour une chaine en conséquence
      while(chaine[i]!='\0'){
       if(chaine[i]==c){
           j++;
       }
       i++;
      }
      i=0;
       char *str=malloc(sizeof(char)*(strlen(chaine)-j+1));
       // On insère dans str les caratères différents de celui à supprimer
       j=0;
       while(chaine[i]!='\0'){
           if(chaine[i]!= c){
           str[j]=chaine[i];
           j++;
           }
           i++;
      }
      str[j]='\0';
    }
    
    
     int notUsed(char tab[], char c){
    
           for(int j=0; j<strlen(tab); j++){
           if(c==tab[j]){
               return 1;
           }
         }
        return 0;
       }
    
    
     
