#include <stdio.h>
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


// Spécification: ici on cherche a supprimer une seule occurence d'une lettre, pas elles toutes
char *removeChar(char *str, char c) {
    int j=0;
    int taille=strlen(str);

//Dès qu'on rencontre la première occurence de la lettre en question on la remplace et on arrête le parcours de la chaine
    for(int i=0;i<taille;i++){
        if(str[i]==c ){
          str[i]='\n';
          j++;
          break;
        }
    }

//On supprime maintenant ce seul caractère remplacé
    j=0;
    char temp;
    for(int i=0;i<taille;i++){
        temp= str[i];
     if(temp=='\n'){
         continue;
     }
     str[j]=temp;
     j++;
    }
    str[taille-1]='\0';
    return str;
    }




    motPossible *Anagramme_(motPossible *Noeud, int taille, char tableau[]){
      //Allouer l'espace necessaire pour un tableau de mot possible qu'on associera au champ suivant du noeud à considérer  
      motPossible *tableau_mot=malloc(sizeof(motPossible)*(9-taille+1));

      //tableau des lettres restantes après suppression des caractères du parent
      char *tableauR = malloc(sizeof(char)*(strlen(tableau)-taille+2));

      //tableau intermédaire pour ne pas affecter le tableau des lettres générées par l'utilisateur
      char *tableau_inter=malloc(sizeof(char)*strlen(tableau));
      strcpy(tableau_inter,tableau);
      
        for (int i=0; i<taille-1; i++){
          tableau_inter=removeChar(tableau_inter, Noeud->mot[i]);
        }
          strcpy(tableauR,tableau_inter);
          free(tableau_inter);
  
          //créer les mots
      for(int i=0; i<(10-taille); i++){
          tableau_mot[i].mot=malloc(sizeof(char)*(taille+1));
          strcpy(tableau_mot[i].mot, Noeud->mot);
              tableau_mot[i].mot[taille-1]=tableauR[i];
              tableau_mot[i].mot[taille]='\0';
              tableau_mot[i].suivant=NULL;
      }
  
      //Allouer l'espace et lier au Noeud
      Noeud->suivant=malloc(sizeof(motPossible)*(9-taille+1));
      for (int i=0; i<(10-taille);i++){
              Noeud->suivant[i]=malloc(sizeof(motPossible));
              Noeud->suivant[i]->mot=malloc(sizeof(char)*(taille+1));
              Noeud->suivant[i]=(tableau_mot+i);
      }
      return Noeud->suivant;
    }


  
    void CreationArbre(motPossible *Noeud,int tailleGen, char* chaine){
        motPossible *pointeur=malloc(sizeof(motPossible));
        pointeur=Noeud;
        pointeur->suivant=Anagramme_(pointeur,tailleGen,chaine);

        //Pour chaque génération si le mot généré n'est pas de taille maximale (soit 9) on crée toute la génération suivante, l'itération ici permet de parcourir tous les noeuds d'une génération pour les créer et la récursivité passe d'une racine vers le fils jusqu'à la base
            for(int i=0; i<10-tailleGen; i++){
            if(strlen(pointeur->suivant[i]->mot)!=9){
                CreationArbre(pointeur->suivant[i],tailleGen+1,chaine);
               }
            }
    }
