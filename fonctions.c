#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

// Définition des variables globales supplémentaires
int scoreJoueur1 = 0;           // Score du joueur 1, initialisé à 0
int scoreJoueur2 = 0;           // Score du joueur 2, initialisé à 0
int toursJoues = 0;             // Nombre de tours joués, initialisé à 0
char grille[9] = {0};          // Grille de jeu avec taille exacte pour stocker nbreTotalLettresGrille caractères

// Définition des fonctions

/**
 * Sauvegarde l'état actuel de la partie dans un fichier texte (sauvegarde.txt).
 * Utilise les variables globales pour les informations de la partie.
 * Inclut l'historique des mots joués et leurs scores pour chaque joueur.
 */
void sauvegarderPartie(const char motsJoueur1[][20], const char motsJoueur2[][20], const int scoresJoueur1[], const int scoresJoueur2[]) {
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    fprintf(fichier, "Nom Joueur 1: %s\n", nomJoueur1);
    fprintf(fichier, "Nom Joueur 2: %s\n", nomJoueur2);
    fprintf(fichier, "Score Joueur 1: %d\n", scoreJoueur1);
    fprintf(fichier, "Score Joueur 2: %d\n", scoreJoueur2);
    fprintf(fichier, "Tours joués: %d\n", toursJoues);
    fprintf(fichier, "Tours totaux: %d\n", nbreTours);
    
    fprintf(fichier, "Review de la partie:\n");
    for (int i = 0; i < toursJoues; i++) {
        fprintf(fichier, "Tour %d:\n", i + 1);
        fprintf(fichier, "%s - Mot: %s, Score: %d\n", nomJoueur1, motsJoueur1[i], scoresJoueur1[i]);
        fprintf(fichier, "%s - Mot: %s, Score: %d\n", nomJoueur2, motsJoueur2[i], scoresJoueur2[i]);
    }

    fclose(fichier);
    printf("Partie sauvegardée avec succès.\n");
}

/**
 * Charge une partie précédemment sauvegardée à partir du fichier sauvegarde.txt.
 * Les données sont chargées directement dans les variables globales définies dans le module.
 * 
 * @return 1 si le chargement a réussi, 0 en cas d'échec
 */
int chargerPartie(void) {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return 0;
    }

    // Lecture des noms des joueurs
    fscanf(fichier, "Nom Joueur 1: %s\n", nomJoueur1);
    fscanf(fichier, "Nom Joueur 2: %s\n", nomJoueur2);

    // Lecture des scores
    fscanf(fichier, "Score Joueur 1: %d\n", &scoreJoueur1);
    fscanf(fichier, "Score Joueur 2: %d\n", &scoreJoueur2);

    // Lecture du nombre de tours
    fscanf(fichier, "Tours joués: %d\n", &toursJoues);
    fscanf(fichier, "Tours totaux: %d\n", &nbreTours);

    fclose(fichier);
    printf("Partie chargée avec succès.\n");
    return 1;
}

/**
 * Affiche un résumé détaillé de la partie sauvegardée.
 * Montre les informations de base de la partie et l'historique des coups joués tour par tour.
 */
void reviewPartie() {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    char nomJoueurSauvegarde1[10], nomJoueurSauvegarde2[10];
    int scoreJoueurSauvegarde1, scoreJoueurSauvegarde2, toursJouesSauvegarde;
    char ligne[100];
    int toursTotauxTemp; // Variable temporaire pour lire la valeur

    // Lecture des informations de base
    fscanf(fichier, "Nom Joueur 1: %s\n", nomJoueurSauvegarde1);
    fscanf(fichier, "Nom Joueur 2: %s\n", nomJoueurSauvegarde2);
    fscanf(fichier, "Score Joueur 1: %d\n", &scoreJoueurSauvegarde1);
    fscanf(fichier, "Score Joueur 2: %d\n", &scoreJoueurSauvegarde2);
    fscanf(fichier, "Tours joués: %d\n", &toursJouesSauvegarde);
    fscanf(fichier, "Tours totaux: %d\n", &toursTotauxTemp);
    

    // Affichage des informations générales
    printf("Informations de la partie:\n");
    printf("Joueur 1: %s (Score: %d)\n", nomJoueurSauvegarde1, scoreJoueurSauvegarde1);
    printf("Joueur 2: %s (Score: %d)\n", nomJoueurSauvegarde2, scoreJoueurSauvegarde2);
    printf("Progression: %d tours joués sur %d\n", toursJouesSauvegarde, toursTotauxTemp);
    
    // Lecture de la ligne "Review de la partie:"
    fgets(ligne, sizeof(ligne), fichier);

    // Lecture de la review de la partie
    printf("Historique des tours:\n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    fclose(fichier);
}

/**
 * Vérifie si une sauvegarde existe déjà dans le fichier sauvegarde.txt.
 * 
 * @return 1 si une sauvegarde existe et est valide, 0 sinon
 */
int verifSauvegarde(void) {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        // Le fichier n'existe pas ou n'est pas accessible
        return 0;
    }

    // Vérifier que le fichier contient au moins les informations essentielles
    char ligne[100];
    int compteurLignes = 0;
    
    // On vérifie que le fichier contient au moins les 6 premières lignes
    // qui correspondent aux informations d'une sauvegarde
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && compteurLignes < 6) {
        compteurLignes++;
    }
    
    fclose(fichier);
    
    // Si on a trouvé au moins 6 lignes, on considère que c'est une sauvegarde valide
    return (compteurLignes >= 6) ? 1 : 0;
}

/**
 * Efface le fichier de sauvegarde s'il existe.
 * Cette fonction permet de supprimer une sauvegarde existante
 * avant de commencer une nouvelle partie.
 * 
 * @return 1 si la sauvegarde a été effacée avec succès ou n'existait pas, 0 en cas d'échec
 */
int effacerSauvegarde(void) {
    // Vérifier d'abord si le fichier existe
    if (verifSauvegarde()) {
        // Le fichier existe, on tente de le supprimer
        int resultat = remove("sauvegarde.txt");
        
        if (resultat == 0) {
            printf("Sauvegarde précédente effacée avec succès.\n");
            return 1;
        } else {
            printf("Erreur lors de la suppression de la sauvegarde.\n");
            return 0;
        }
    } else {
        // Le fichier n'existe pas ou n'est pas valide, rien à faire
        printf("Aucune sauvegarde à effacer.\n");
        return 1;  // On considère que c'est un succès puisqu'il n'y a rien à effacer
    }
}

// D�finition des fonctions

//Fonction pour compter le nombre de caract�res dans un mot

int motLength(char mot[]){
    int i = 0;
    while(mot[i] != '\0'){
        i++;
    }
    return i;
}


//Fonction de v�rification des caract�res
int validationChar(char mot[], char grilleCaractere[]){
    char validChar[10];
    int isequal, i=0;

    strcpy(validChar, grilleCaractere);
    //On parcourt le tableau contenant le mot de l'utilisateur
    while(mot[i] != '\0'){

        //On initialise � 0 pour dire que le caract�re � l'indice i n'est �gale � aucun parmi ceux de la grille
        isequal = 0;

        //On parcourt la grille de caract�res
        for(int j = 0; j < nbreTotalLettresGrille; j++){

            //Si le caract�re � l'indice i correspond � un caract�re parmi ceux de la grille, isequal passe � 1 pour dire vrai
            //on vide la case contenant le caract�re dans la grille
            //on passe au caract�re suivant
            if(mot[i] == validChar[j]){
                isequal = 1;
                validChar[j] = '\0';
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
    

  char *LongestWord(char grille[])
       {
           //i pacours la grille
          int i=0;
       // le mot valide le plus long de taille 0 à l'initialisation
         char *valideMot=malloc(sizeof(char)+1);
         valideMot[0]='\0';
       
         char name[15]={'.','.','/','d','i','c','o','/','a','.','t','x','t'};
       //On initialise des copies de la grille pour l'itération et pour les lettres non utilisés
         char *notUsedchar=malloc(sizeof(char)*(strlen(grille)+1));
         strcpy(notUsedchar,grille);
       
         //le mot courant du dictionnaire
        char mot[30]={'\0'};
       while(grille[i]!='\0')
       {
          if(notUsed(notUsedchar,grille[i]))
            {
             name[8]=grille[i];
             FILE *fichier=NULL;
             fichier=fopen(name,"r");
       
             if(fichier==NULL)
             {
                perror("Erreur d'ouverture de fichier");
             }else
             {
          //Si le fichier est bien ouvert on récupère le mot de chaque ligne en remplacant le contenu de la case de \n par \0
               fgets(mot,30,fichier);
              mot[strlen(mot)-1]='\0';
       
             while(!feof(fichier))
                {
                 //Si le mot du dictionnaire respecte les lettres de la grille
                   if(validationChar(mot,grille))
                     {
                  //On alloue et on récupère le mot valide seulement s'il est plus long que le précedent
                     if(strlen(mot)>strlen(valideMot))
                         {
                         valideMot=malloc(sizeof(char)*(strlen(mot)+1));
                         strcpy(valideMot,mot);
                  //Si le mot récupéré est aussi long que la grille des lettres il est le plus long
                         if(strlen(valideMot)==nbreTotalLettresGrille)
                             {
                           return valideMot;
                             }
                         }else
                         {
                         fgets(mot,30,fichier);
                         mot[strlen(mot)-1]='\0';
       
                         }
       
                     }else
                         {
                         fgets(mot,30,fichier);
                         mot[strlen(mot)-1]='\0';
                         }
                 }
             }
             fclose(fichier);
         }
         //le caractère courant est supprimé des caractères non utilisés
         removeSameChar(notUsedchar,grille[i]);
              i++;
         }
         free(notUsedchar);
             return valideMot;
    }
       
