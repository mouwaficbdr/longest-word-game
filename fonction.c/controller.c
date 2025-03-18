#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <ctype.h>
#include "../fonction.h/controller.h"
#include "../fonction.h/utilitaire.h"
#include "../fonction.h/view.h"
#include <time.h>

#define MAX_TOURS 50

const int nbreJoueur = 2;
const int nbreTotalLettresGrille = 9;
const char voyelles[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
const char consonnes[20] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};

//Déclaration des structures
  
  // Définition des variables
Joueur Joueur1;
Joueur Joueur2;
PartieJ Partie;
ListeMot ListeDesMots;
int partieChargee = 0; // Indique si une partie vient d'être chargée

void InitialiserJoueur(){
    strcpy(Joueur1.nom,"\0");
    strcpy(Joueur2.nom,"\0");
    Joueur1.scoreTotal=0;
    Joueur2.scoreTotal=0;
    
    for(int i=0; i<MAX_TOURS; i++){
        Joueur1.score[i]=0;
        Joueur2.score[i]=0;
        strcpy(Joueur1.mot[i],"\0");
        strcpy(Joueur2.mot[i],"\0");
    }
}

 void InitialiserPartie(){
   strcpy(Partie.lettreGenerees,"\0");
   Partie.nbreTours=0;
   Partie.numJoueurCommencer=0;
   Partie.tourJoues=0;
   ListeDesMots.premier=NULL;
 }

/**
 * Sauvegarde l'état actuel de la partie dans un fichier texte (sauvegarde.txt).
 * Utilise les variables globales pour les informations de la partie.
 * Inclut l'historique des mots joués et leurs scores pour chaque joueur.
 */
void sauvegarderPartie() {
    FILE *fichier = fopen("sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    fprintf(fichier, "Nom Joueur 1: %s\n", Joueur1.nom);
    fprintf(fichier, "Nom Joueur 2: %s\n", Joueur2.nom);
    fprintf(fichier, "Score Joueur 1: %d\n", Joueur1.scoreTotal);
    fprintf(fichier, "Score Joueur 2: %d\n", Joueur2.scoreTotal);
    fprintf(fichier, "Tours joués: %d\n", Partie.tourJoues);
    fprintf(fichier, "Tours totaux: %d\n", Partie.nbreTours);
    
    //Pour s'assurer qu'aucune information n'est perdue ou erronée on réecrit a chaque fois 
    //les informations dans le fichier
    fprintf(fichier, "Review de la partie:\n");
    for (int i = 0; i < Partie.tourJoues; i++) {
        fprintf(fichier, "Tour %d:\n", i + 1);
        fprintf(fichier, "%s - Mot: %s, Score: %d\n", Joueur1.nom, Joueur1.mot[i], Joueur1.score[i]);
        fprintf(fichier, "%s - Mot: %s, Score: %d\n", Joueur2.nom, Joueur2.mot[i], Joueur2.score[i]);
    }

    fclose(fichier);
    printf("Partie sauvegardee avec succes.\n");
}


int enregistrerTour(const char motJoueur1[], const char motJoueur2[], int scoreMotJoueur1, int scoreMotJoueur2) {
    // Vérifier si le nombre maximum de tours n'est pas dépassé
    if (Partie.tourJoues >= MAX_TOURS) {
        printf("Erreur : Nombre maximum de tours atteint.\n");
        return 0;
    }
    
    // Vérifier que les tours joués ne dépassent pas le nombre de tours total défini pour la partie
    if (Partie.tourJoues >= Partie.nbreTours) {
        printf("Erreur : Tous les tours de la partie ont deja ete joues.\n");
        return 0;
    }

    // Enregistrer les mots (avec vérification de longueur pour éviter les débordements)
    strncpy(Joueur1.mot[Partie.tourJoues], motJoueur1, 19);
    Joueur1.mot[Partie.tourJoues][9] = '\0'; // Assurer la terminaison de la chaîne
    
    strncpy(Joueur2.mot[Partie.tourJoues], motJoueur2, 19);
    Joueur2.mot[Partie.tourJoues][9] = '\0'; // Assurer la terminaison de la chaîne
    
    // Enregistrer les scores du tour
    Joueur1.score[Partie.tourJoues] = scoreMotJoueur1;
    Joueur2.score[Partie.tourJoues] = scoreMotJoueur2;
    
    // Mettre à jour les scores totaux
    Joueur1.scoreTotal += scoreMotJoueur1;
    Joueur2.scoreTotal += scoreMotJoueur2;
    
    // Incrémenter le compteur de tours joués
    Partie.tourJoues++;
    
    return 1;
}


/**
 * Charge une partie précédemment sauvegardée à partir du fichier sauvegarde.txt.
 * Les données sont chargées directement dans les variables globales définies.
 * 
 * @return 1 si le chargement a réussi, 0 en cas d'échec
 */
int chargerPartie() {
    FILE *fichier = fopen("sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return 0;
    }

    // Lecture des noms des joueurs
    fscanf(fichier, "Nom Joueur 1: %s\n", Joueur1.nom);
    fscanf(fichier, "Nom Joueur 2: %s\n", Joueur2.nom);

    // Lecture des scores
    fscanf(fichier, "Score Joueur 1: %d\n", &Joueur1.scoreTotal);
    fscanf(fichier, "Score Joueur 2: %d\n", &Joueur2.scoreTotal);

    // Lecture du nombre de tours
    fscanf(fichier, "Tours joués: %d\n", &Partie.tourJoues);
    fscanf(fichier, "Tours totaux: %d\n", &Partie.nbreTours);

    // Réinitialiser les tableaux d'historique
    for (int i = 0; i < MAX_TOURS; i++) {
        Joueur1.mot[i][0] = '\0';
        Joueur2.mot[i][0] = '\0';
        Joueur1.score[i] = 0;
        Joueur2.score[i] = 0;
    }

    // Ignorer la ligne "Review de la partie:"
    char buffer[100];
    fgets(buffer, sizeof(buffer), fichier);

    // Lecture des historiques de mots et scores tour par tour
    for (int i = 0; i < Partie.tourJoues; i++) {
        // Lire la ligne "Tour X:"
        fgets(buffer, sizeof(buffer), fichier);
        
        // Lire les données du joueur 1
        fscanf(fichier, "%[^-]- Mot: %[^,], Score: %d\n", buffer, Joueur1.mot[i], &Joueur1.score[i]);
        
        // Lire les données du joueur 2
        fscanf(fichier, "%[^-]- Mot: %[^,], Score: %d\n", buffer, Joueur2.mot[i], &Joueur2.score[i]);
    }

    fclose(fichier);
    printf("Partie chargee avec succes, incluant l'historique des mots et scores.\n");
    partieChargee = 1; // Indique que la partie vient d'être chargée
    return 1;
}

/**
 * Affiche un résumé détaillé de la partie sauvegardée.
 * Utilise les variables globales pour afficher les informations de la partie.
 */
void reviewPartie() {
    // Vérifier si une partie a été chargée ou si on est en cours de partie
    if (Partie.tourJoues == 0) {
        printf("Aucune partie en cours ou chargee. Rien a afficher.\n");
        return;
    }

    // Affichage des informations générales
    printf("Informations de la partie:\n");
    printf("Joueur 1: %s (Score: %d)\n", Joueur1.nom, Joueur1.scoreTotal);
    printf("Joueur 2: %s (Score: %d)\n", Joueur2.nom, Joueur2.scoreTotal);
    printf("Progression: %d tours joués sur %d\n", Partie.tourJoues, Partie.nbreTours);
    
    // Affichage de l'historique des tours
    printf("Historique des tours:\n");
    for (int i = 0; i < Partie.tourJoues; i++) {
        printf("Tour %d:\n", i + 1);
        printf("%s - Mot: %s, Score: %d\n", Joueur1.nom, Joueur1.mot[i], Joueur1.score[i]);
        printf("%s - Mot: %s, Score: %d\n", Joueur2.nom, Joueur2.mot[i], Joueur2.score[i]);
    }
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
            printf("Sauvegarde precedente effacee avec succes.\n");
            return 1;
        } else {
            printf("Erreur lors de la suppression de la sauvegarde.\n");
            return 0;
        }
    } else {
        // Le fichier n'existe pas ou n'est pas valide, rien à faire
        printf("Aucune sauvegarde a effacer.\n");
        return 1;  // On considère que c'est un succès puisqu'il n'y a rien à effacer
    }
}


int notUsed(char tab[], char c){

    for(int j=0; j<strlen(tab); j++){
    if(c==tab[j]){
        return 1;
    }
    }
    return 0;
 }


//Fonction de vérification des caractères
int validationChar(char mot[], char grilleCaractere[]){
    char validChar[10];
    int isequal, i=0;

    strcpy(validChar, grilleCaractere);
    //On parcourt le tableau contenant le mot de l'utilisateur
    while(mot[i] != '\0'){

        //On initialise à 0 pour dire que le caractère à l'indice i n'est égale à aucun parmi ceux de la grille
        isequal = 0;

        //On parcourt la grille de caractères
        for(int j = 0; j < nbreTotalLettresGrille; j++){

            //Si le caractère à l'indice i correspond à un caractère parmi ceux de la grille, isequal passe à 1 pour dire vrai
            //on vide la case contenant le caractère dans la grille
            //on passe au caractère suivant
            if(mot[i] == validChar[j]){
                isequal = 1;
                validChar[j] = '\0';
                break;
            }
        }

        //Si la variable isequal est toujours à 0, alors le caractère dans le mot de l'utilisateur n'a pas de correspondant dans la grille
        //On retourne la valeur NULL pour stopper la validation
        //Le mot ne respecte pas les caractères de la grille 
        if(isequal == 0){
            return 0;
        }
        i++;
    }

    //si tout s'est bien passé, on renvoie le mot valide qui respecte les caractères de la grille
    return 1;
}



int validationMots(char mot[]) {
    FILE *fichier;
    char motDico[35], path[] = "./dico/ .txt";

    path[strcspn(path, " ")] = mot[0];
    int found = 0;

    fichier = fopen(path, "r");
    if (fichier == NULL) {
        printf("Louverture n'a pas marché");
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
        return strlen(mot);
    }

    return 0;

    fclose(fichier);
}


void motPossibles(char *mot){
    // Allouer correctement la taille de MotPossible (pas MotPossible*)
    MotPossible *ceMotValide = malloc(sizeof(MotPossible));
    if (ceMotValide == NULL) {
        // En cas d'échec d'allocation, sortir de la fonction
        return;
    }
    
    // Allouer de la mémoire pour le mot
    ceMotValide->mot = malloc((strlen(mot) + 1) * sizeof(char));
    if (ceMotValide->mot == NULL) {
        // Si l'allocation pour le mot échoue, libérer ceMotValide et sortir
        free(ceMotValide);
        return;
    }
    
    strcpy(ceMotValide->mot, mot);
    ceMotValide->suivant = NULL;

    // Pour éviter une limitation statique qui pourrait causer des problèmes
    static int nbrElement = 0;
    // Remettre à zéro si on atteint la limite (pour éviter de bloquer l'ajout)
    if (nbrElement >= 13) {
        nbrElement = 0;
    }
    
    int compteur = 0;
    
    if (ListeDesMots.premier == NULL) {
        // Liste vide, ajouter le premier élément
        ListeDesMots.premier = ceMotValide;
        nbrElement = 1;
    } else {
        // La liste n'est pas vide, parcourir pour compter les éléments
        MotPossible *pointeur = ListeDesMots.premier;
        while (pointeur != NULL) {
            // Compter les mots de même longueur
            if (strlen(mot) == strlen(pointeur->mot)) {
                    compteur++; 
                }
                nbrElement++;
            pointeur = pointeur->suivant;
        }
        
        // Si on a trop de mots de la même longueur, ne pas ajouter celui-ci
        if (compteur >= 3) {
            free(ceMotValide->mot);
            free(ceMotValide);
                return;
            }
        
        // Ajouter le nouveau mot en tête de liste
        ceMotValide->suivant = ListeDesMots.premier;
        ListeDesMots.premier = ceMotValide;
    }
 }


char *LongestWord(char grille[])
{
    //i pacours la grille
   int i=0;
 // le mot valide le plus long de taille 0 à l'initialisation
  char *valideMot=malloc(sizeof(char)+1);
  valideMot[0]='\0';
  char name[13]={'.','/','d','i','c','o','/',' ','.','t','x','t'};
 //On initialise des copies de la grille pour l'itération et pour les lettres non utilisés
  char *notUsedchar=malloc(sizeof(char)*(strlen(grille)+1));
  strcpy(notUsedchar,grille);

  //le mot courant du dictionnaire
 char mot[30];
 strcpy(mot,"\0");
while(grille[i]!='\0')
{
   if(notUsed(notUsedchar,grille[i]))
     {
      name[7]=grille[i];
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
          if(strchr(grille,'a')==NULL && strchr(mot,'a')!=NULL){
                strcpy(mot,"0");
          }
            if(validationChar(mot,grille))
              {
                motPossibles(mot);
           //On alloue et on récupère le mot valide seulement s'il est plus long que le précedent
              if(strlen(mot)>strlen(valideMot))
                  {
                    free(valideMot);
                  valideMot=malloc(sizeof(char)*(strlen(mot)+1));
                  strcpy(valideMot,mot);
           //Si le mot récupéré est aussi long que la grille des lettres il est le plus long
                  if(strlen(valideMot)==nbreTotalLettresGrille)
                      {return valideMot;}
                  }
              }
            fgets(mot,30,fichier);
            mot[strlen(mot)-1]='\0';
          }
      }
      fclose(fichier);
      strcpy(notUsedchar, removeSameChar(notUsedchar,grille[i]));
  }
  //le caractère courant est supprimé des caractères non utilisés
       i++;
  }
  free(notUsedchar);
      return valideMot;
}


int JouerEncore(){
    // Si une partie vient d'être chargée, passer automatiquement au tour suivant
    if (partieChargee) {
        partieChargee = 0; // Réinitialiser pour les prochains tours
        return 1;
    }

    char texte[100];
    int largeurTermi=0, hauteurTermi=0;

    //recuperer la taille du terminal
    getConsoleSize(&largeurTermi, &hauteurTermi);
    Effacer();
    
    //Centrer le 1er texte et l'écrire
    int xR=(largeurTermi)/2 - 20;
    int yR= (hauteurTermi)/2 - 4;
    rectangle(xR, yR, 40, 8);
    
    strcpy(texte, "On passe au tour suivant?");
    gotoxy(xR + (40-strlen(texte))/2, yR + 2);
    printf("%s", texte);
     
    //Centrer le 2ème texte et l'écrire
    strcpy(texte, "Oui [O] / Non [N]");
    gotoxy(xR + (40-strlen(texte))/2, yR + 4);
    printf("%s", texte);

    // Une approche plus simple pour la saisie
    fflush(stdin);
    char choix = ' ';
    
    // Attendre que l'utilisateur entre O ou N
    while(choix != 'O' && choix != 'N') {
        gotoxy(xR + 20, yR + 6);
        printf("Votre choix : ");
        choix = toupper(getchar());
        fflush(stdin);  // Vider le buffer après chaque entrée
    }
    
    if(choix == 'N') {
        return 0;
    }
    
    // Si l'utilisateur choisit Oui, demander qui commence
    Effacer();
    
    xR=(largeurTermi)/2 - 20;
    yR= (hauteurTermi)/2 - 4;
    rectangle(xR, yR, 40, 8);
    
    strcpy(texte, "Qui entamera le tour?");
    gotoxy(xR + (40-strlen(texte))/2, yR + 2);
    printf("%s", texte);
    
    strcpy(texte, "Joueur [1] / Joueur [2]");
    gotoxy(xR + (40-strlen(texte))/2, yR + 4);
    printf("%s", texte);
    
    // Attendre que l'utilisateur entre 1 ou 2
    int joueurChoice = 0;
    while(joueurChoice != 1 && joueurChoice != 2) {
        gotoxy(xR + 20, yR + 6);
        printf("Votre choix : ");
        char c = getchar();
        fflush(stdin);  // Vider le buffer après chaque entrée
        
        if(c == '1') joueurChoice = 1;
        else if(c == '2') joueurChoice = 2;
    }
    
    Partie.numJoueurCommencer = joueurChoice;
    return 1;
}



void nouvellePartie()
{
    Effacer();
char choixNouvellePartie='O';
char choix='\n';
char validation='\0';
int bon=0;
//Si une sauvegarde existe
    if(verifSauvegarde()){
        
            char texte[]="Attention: Une partie a ete sauvegardee. En poursuivant vous ecraserez les sauvegardes!\n";
            int largeur=0, hauteur=0;
            getConsoleSize(&largeur,&hauteur);
            largeur = (largeur-strlen(texte))/2;
            hauteur /= 2;
            EcritureDynamique(texte,largeur,hauteur-1,0);
            
            strcpy(texte,"Voulez-vous lancer la nouvelle partie? Oui[O] / Non[N]\n");
            getConsoleSize(&largeur,&hauteur);
            largeur = (largeur-strlen(texte))/2;
            hauteur /= 2;
            EcritureDynamique(texte,largeur,hauteur,0);
            getConsoleSize(&largeur,&hauteur);
            gotoxy((largeur/2),(hauteur/2)+1);

     while(!bon)
     {
        choixNouvellePartie=getche();
        if(choixNouvellePartie=='O' || choixNouvellePartie=='N')
        {
            while(1){
                validation=getche();
                if(validation=='\r')
                {
                    bon=1;
                    break;
                }else if(validation=='\b')
                {
                    gotoxy((largeur/2),(hauteur/2)+1);
                    gotoxy((largeur/2),(hauteur/2)+1);
                    choixNouvellePartie='\n';
                    break;
                }else
                {
                    printf("\b \b");
                    gotoxy((largeur/2)+1,(hauteur/2)+1);
                }
            }
        }else
        {
            printf("\b \b"); //Effacer les caractères qui ne répondent pas à ceux demandés
            gotoxy((largeur/2),(hauteur/2)+1);
        }
     }
        if(choixNouvellePartie=='O')
        {
            effacerSauvegarde();
        }
        Effacer();
    }

    //Recupérer les informations si une nouvelle partie est lancée
    if(choixNouvellePartie=='O')
    {   
        InitialiserJoueur();
        InitialiserPartie();
        char **lesinfos=malloc(sizeof(char *)*4);
       
        for(int i=0; i<4; i++){
            lesinfos[i]=malloc(sizeof(char)*70);
        }
        strcpy(lesinfos[0],"Nom du joueur 1: \n");
        strcpy(lesinfos[1],"Nom du joueur 2: \n");
        strcpy(lesinfos[2],"Combien de tours voulez-vous effectuer?\n");
        strcpy(lesinfos[3],"Qui desire entamer la partie: Joueur [1] / [2]\n");
        
        int largeurT=0;
        int hauteurT=0;
        int x=0, y=0;
        bon=0;
        choix='\n';
        validation='\0';

        for(int i=0; i<4; i++)
        {
            getConsoleSize(&largeurT,&hauteurT);
            x=(largeurT-strlen(lesinfos[i]))/2;
            y=(hauteurT/3)+(2*i);
            gotoxy(x,y);
            printf("%s",lesinfos[i]);
            getConsoleSize(&largeurT,&hauteurT);
            gotoxy((largeurT/2),y+1);   
            char test[10]="a";
            char *converti=NULL;
            switch(i){
                case 0:{
                scanf("%s",Joueur1.nom);
                gotoxy((largeurT/2),y+1);
                clearLine();
                EcritureDynamique(Joueur1.nom,((largeurT-strlen(Joueur1.nom))/2),(y+1),0);
                break;
                }
                case 1:{
                    scanf("%s",Joueur2.nom);
                    gotoxy((largeurT/2),y+1);
                    clearLine();
                    EcritureDynamique(Joueur2.nom,((largeurT-strlen(Joueur2.nom))/2),(y+1),0);
                    break;
                }
                case 2:{
                  do{
                      gotoxy((largeurT/2),y+1);
                      clearLine();
                      gotoxy((largeurT/2),y+1);
                      scanf("%s",test);    
                  }while(!isNumber(test) || test[0]=='\r');  
                  Partie.nbreTours=strtol(test,&converti,10);
                  gotoxy((largeurT/2),y+1);
                  clearLine();
                  EcritureDynamique(test,((largeurT-strlen(test))/2),(y+1),0);
                    break;
                }
                case 3:{
                    strcpy(test,"a");
                    do{
                        if(strcmp(test, "\r")){
                            gotoxy((largeurT/2),y+1);
                        }
                      gotoxy((largeurT/2),y+1);
                      clearLine();
                      gotoxy((largeurT/2),y+1);
                        scanf("%s", test);
                        Partie.numJoueurCommencer=strtol(test,&converti,10);
                    }while(!isNumber(test) || (Partie.numJoueurCommencer!=1 && Partie.numJoueurCommencer!=2));
                    Partie.numJoueurCommencer=strtol(test,&converti,10);
                    gotoxy((largeurT/2),y+1);
                    clearLine();
                    EcritureDynamique(test,((largeurT-strlen(test))/2),(y+1),0);
                    break;
                }                
            }    
        }
        for(int i=0; i<4; i++){
            free(lesinfos[i]);
        }
        free(lesinfos);

        DemarrerPartie(Joueur1.nom,Joueur2.nom,1,Partie.nbreTours,Partie.numJoueurCommencer);
    }else{
        afficherMenu();
    }
}


void lancerJeu(){
    
    Effacer();
    int largeurTermi=0, hauteurTermi=0;
    
    // Récupérer les dimensions du terminal pour les affichages
    getConsoleSize(&largeurTermi, &hauteurTermi);

    // Variable pour stocker si on vient de charger une partie
    int vientDeCharger = partieChargee;
    
    // Si on ne vient pas de charger une partie, afficher l'animation de début
    if (!vientDeCharger) {
        char TexteDebut[]="QUI AURA LE LONGEST WORD?";
        //Pause
        Sleep(1000);

        //Position du curseur
        int x=(largeurTermi-strlen(TexteDebut))/2;
        int y= hauteurTermi/2;

        //Afficher le message progressivement caractère par caractère
        EcritureDynamique(TexteDebut,x,y,100);

        //Pause et effacer pour lancer le Jeu
        Sleep(1000);
    }

    char *convert;
    char *texte=malloc(sizeof(char)*65);
    int x = 0; // Déclarer la variable x utilisée plus tard
    do{
        if(Partie.tourJoues<Partie.nbreTours){
            if(JouerEncore()){ 
                DemarrerPartie(Joueur1.nom, Joueur2.nom, Partie.tourJoues+1, Partie.nbreTours, Partie.numJoueurCommencer);
            }else{
                Effacer();
                strcpy(texte,"Point de sauvegarde!");
                EcritureDynamique(texte,(largeurTermi-strlen(texte))/2,(hauteurTermi/2)-2,0);            
                strcpy(texte,"Sauvegardez votre progression?");
                EcritureDynamique(texte,(largeurTermi-strlen(texte))/2,(hauteurTermi/2),0); 
                strcpy(texte,"Oui [1] / Non [0]");
                EcritureDynamique(texte,(largeurTermi-strlen(texte))/2,(hauteurTermi/2)+1,0);
                
                // Attendre que l'utilisateur entre 1 ou 0
                fflush(stdin);
                x = -1;
                while(x != 0 && x != 1) {
                    gotoxy((largeurTermi-10)/2,(hauteurTermi/2)+3);
                    printf("Choix : ");
                    char c = getchar();
                    fflush(stdin);
                    
                    if(c == '0') x = 0;
                    else if(c == '1') x = 1;
                }
                
                if(x) {
                    sauvegarderPartie();
                    Sleep(2000);
                    afficherMenu();
                }else{
                    afficherMenu();
                }
            }
        }else{
            // Si tous les tours ont été joués, supprimer la sauvegarde avant de revenir au menu
            if (verifSauvegarde()) {
                effacerSauvegarde();
            }
            afficherMenu();
        }
    }while(Partie.tourJoues<=Partie.nbreTours);
  
}


/**
 * Génère la grille de caractères aléatoires pour le mode Solo
 * Permet à l'IA de choisir intelligemment les voyelles/consonnes selon son niveau
 * @param numCommencer Le joueur qui commence (1 = humain, 2 = IA)
 * @param niveau Le niveau de difficulté de l'IA
 */
void genererCaractereAletoiresSolo(int numCommencer, NiveauDifficulteIA niveau) {
    char choixConsonneVoyelle[2];
    
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));
    
    // Compteurs pour la stratégie de l'IA
    int nbVoyelles = 0;
    int nbConsonnes = 0;

 for (int i = 0; i < nbreTotalLettresGrille; i++) { 
     prompt();
     clearLine();
     prompt();

        if (numCommencer == 1) {
            // Tour du joueur humain
            printf("Joueur, choisissez une lettre ('c' pour consonne, 'v' pour voyelle) : ");
     
     do {
         prompt();
         clearLine();
         prompt();
                printf("Joueur, choisissez une lettre ('c' pour consonne, 'v' pour voyelle) : ");
                scanf("%s", choixConsonneVoyelle);
                choixConsonneVoyelle[0] = tolower(choixConsonneVoyelle[0]);
            } while (strcmp(choixConsonneVoyelle, "c") != 0 && strcmp(choixConsonneVoyelle, "v") != 0);
            
        } else {
            // Tour de l'IA - Stratégie selon le niveau
            switch (niveau) {
                case FACILE:
                    // Choix aléatoire simple
                    strcpy(choixConsonneVoyelle, rand() % 2 == 0 ? "c" : "v");
                    break;
                    
                case MOYEN:
                    // Essaie d'équilibrer un peu plus (2/3 consonnes, 1/3 voyelles)
                    if (nbVoyelles > (i + 1) / 3) {
                        strcpy(choixConsonneVoyelle, "c");
                    } else if (nbConsonnes > 2 * (i + 1) / 3) {
                        strcpy(choixConsonneVoyelle, "v");
                    } else {
                        strcpy(choixConsonneVoyelle, rand() % 2 == 0 ? "c" : "v");
                    }
                    break;
                    
                case DIFFICILE:
                    // Stratégie optimisée pour trouver de longs mots
                    if (i < 2) {
                        // Commencer par des consonnes fréquentes
                        strcpy(choixConsonneVoyelle, "c");
                    } else if (nbVoyelles < 2 && i < 5) {
                        // S'assurer d'avoir des voyelles au milieu
                        strcpy(choixConsonneVoyelle, "v");
                    } else if (nbVoyelles >= (i + 1) / 3 + 1) {
                        // Maintenir un ratio optimal
                        strcpy(choixConsonneVoyelle, "c");
                    } else {
                        strcpy(choixConsonneVoyelle, "v");
                    }
                    break;
                    
                default:
                    // Par défaut, équilibrer
                    strcpy(choixConsonneVoyelle, rand() % 2 == 0 ? "c" : "v");
            }
            
            // Afficher le choix de l'IA
            prompt();
            printf("L'IA choisit: %s", strcmp(choixConsonneVoyelle, "c") == 0 ? "consonne" : "voyelle");
            Sleep(800); // Pause pour simuler la réflexion de l'IA
        }
        
        // Générer la lettre selon le choix
        if (strcmp(choixConsonneVoyelle, "c") == 0) {
         Partie.lettreGenerees[i] = consonnes[rand() % 20];
            nbConsonnes++;
     } else {
         Partie.lettreGenerees[i] = voyelles[rand() % 6];
            nbVoyelles++;
     }
     
        // Assurer que la chaîne est bien terminée
        Partie.lettreGenerees[i+1] = '\0';
        
        // Afficher la lettre générée
     EntryField();
        printf("%c", Partie.lettreGenerees[i]);
     fflush(stdin);
     gambaseX++;

        // Changer de joueur
        if (numCommencer == 1) {
            numCommencer = 2;
        } else {
            numCommencer = 1;
 }
    }
}

 void mettreAJourAffichageScores() {
    // Mise à jour des positions des scores en fonction de leurs valeurs actuelles
    score1moveX = scorefieldX1 + ((scorefieldLong-Intlen(Joueur1.scoreTotal))/2);
    score2moveX = scorefieldX2 + ((scorefieldLong-Intlen(Joueur2.scoreTotal))/2);
    
    // Effacement des anciens scores et affichage des nouveaux scores
    player1Score();
    printf("     ");
    player1Score();
    printf("%d", Joueur1.scoreTotal);

    player2Score();
    printf("     ");
    player2Score();
    printf("%d", Joueur2.scoreTotal);

}


void DemarrerPartie(char Joueur1name[], char Joueur2name[], int tourActuel, int totalTours, int numCommencer){
    
    // Réinitialiser la liste des mots possibles pour éviter les problèmes
    InitialiserListeDesMots();
    
    Effacer();
    gotoxy(0,4);
    printf(" Tour %d", tourActuel);
    
    // On initialise les variables de récupération des dimensions de la console
    initialiserVariables();

    // On affiche l'interface et on charge les noms des joueurs
    afficherInterface();
    namePlay1(); printf("%s", Joueur1name);
    namePlay2(); printf("%s", Joueur2name);
    
    // Afficher les scores existants au début du tour
    mettreAJourAffichageScores();

    // En fonction du joueur qui commence, on appelle la fonction genererCaracteresAleatoires
    genererCaractereAleatoires(numCommencer);

    // Effacer le texte de prompt après le remplissage de la grille
    prompt();
    clearLine();

    if(numCommencer == 1){
        // Afficher le texte pour le joueur 1
        gotoxy(EntryFieldX1, EntryFieldY1-1);
        printf("Joueur 1 entrez votre mot:");
        
        //Le joueur 1 entre son mot (le mot est biensur hashé)
        centeredhash1(Joueur1.mot[tourActuel-1], 10);

        // Effacer le texte du joueur 1 et afficher celui du joueur 2
        EffacerZone(EntryFieldX1,EntryFieldY1-1,strlen("Joueur 1 entrez votre mot:"),1);
        gotoxy(EntryFieldX2, EntryFieldY2-1);
        printf("Joueur 2 entrez votre mot:");

        //Puis le joueur 2 entre son mot
        centeredhash2(Joueur2.mot[tourActuel-1], 10);
        
        // Effacer le texte du joueur 2
        EffacerZone(EntryFieldX2,EntryFieldY2-1,strlen("Joueur 1 entrez votre mot:"),1);

        //On affiche les mots des deux joueurs après dans leur case respective
        centerword1(Joueur1.mot[tourActuel-1]);
        centerword2(Joueur2.mot[tourActuel-1]);

    }else{ //Dans le cas contraire on commence avec le joueur 2
        // Afficher le texte pour le joueur 2
        gotoxy(EntryFieldX2, EntryFieldY2-1);
        printf("Joueur 2 entrez votre mot:");

        //Le joueur 2 entre son mot 
        centeredhash2(Joueur2.mot[tourActuel-1], 10);

        // Effacer le texte du joueur 2 et afficher celui du joueur 1
        EffacerZone(EntryFieldX2,EntryFieldY2-1,strlen("Joueur 1 entrez votre mot:"),1);
        gotoxy(EntryFieldX1, EntryFieldY1-1);
        printf("Joueur 1 entrez votre mot:");

        //Le joueur 1 entre son mot ensuite
        centeredhash1(Joueur1.mot[tourActuel-1], 10);

        // Effacer le texte du joueur 1
        EffacerZone(EntryFieldX1,EntryFieldY1-1,strlen("Joueur 1 entrez votre mot:"),1);

        //Puis on affiche les deux mots
        centerword2(Joueur2.mot[tourActuel-1]);
        centerword1(Joueur1.mot[tourActuel-1]);
    }


    //Il y aura un texte pour dire qu'on procède maintenant à la validation des mots
    int positionLoading = (gameEntryFieldY + gameEntryFieldHeight -1) + ((EntryFieldY1 - (gameEntryFieldY + gameEntryFieldHeight -1))/2);
    
    EcritureDynamique("Un instant, nous procedons a la validation....", EntryFieldX1 + 2, positionLoading, 50);
    Sleep(3000);
        
    Joueur1.score[tourActuel-1]=validationChar(Joueur1.mot[tourActuel-1],Partie.lettreGenerees)?validationMots(Joueur1.mot[tourActuel-1]):0;
    Joueur1.scoreTotal+= Joueur1.score[tourActuel-1];

    Joueur2.score[tourActuel-1]=validationChar(Joueur2.mot[tourActuel-1],Partie.lettreGenerees)?validationMots(Joueur2.mot[tourActuel-1]):0;
    Joueur2.scoreTotal+= Joueur2.score[tourActuel-1];

    Partie.tourJoues=tourActuel;

    // Afficher "Vous auriez pu trouver:" au-dessus du rectangle de l'IA, centré
    char* messageTrouver = "Vous auriez pu trouver:";
    int messageX = AIX + ((EntryFieldLong - strlen(messageTrouver)) / 2);
    gotoxy(messageX, AIY-1);
    printf("%s", messageTrouver);
    
    // Récupérer et afficher le mot le plus long possible
    char *motLePlusLong = LongestWord(Partie.lettreGenerees);
    centerwordAI(motLePlusLong);
    free(motLePlusLong);

    // Mise à jour de l'affichage des scores
    mettreAJourAffichageScores();
    Sleep(1500);
    afficherListeMotsPossibles();

    Effacer();
    AfficherGagnantTour();
}


void AfficherGagnantTour(){

    //On récupère la taille de l'écran
    int consoleLargeur, consoleHauteur;

    //Initialisation des variables qui stockeront les dimensions de la console
    consoleLargeur = 0;
    consoleHauteur = 0;
    getConsoleSize(&consoleLargeur, &consoleHauteur);

    int largeurR = consoleLargeur/2;
    int hauteurR = consoleHauteur/2;
    //Mise en place du rectangle
    int xR = (largeurR) - ((largeurR)/2);
    int yR = (hauteurR) - ((hauteurR)/2);
    rectangle(xR, yR, largeurR, 15);

    //Positionnement des texte de joueur gagnant
    gotoxy(((largeurR)- strlen("GAGNANT DU PARTIE  "))/2 + xR, yR + 4);
    printf("GAGNANT DE LA PARTIE %d", Partie.tourJoues);
    
    //Si le score du joueur 1 pour le tour actuel est plus élevé par rapport à celui du joueur 2, il est le gagnant
    if(Joueur1.score[Partie.tourJoues - 1] > Joueur2.score[Partie.tourJoues - 1]){
        gotoxy(xR + 6, yR + 6);
        printf("Joueur %d :", 1);
        gotoxy(xR + 6, yR + 8);
        printf("%s vous etes le gagnant de cette partie", Joueur1.nom);
        gotoxy((((xR + largeurR) - 6) - strlen("Score : ")), yR + 8);
        printf("Score : %d", Joueur1.score[Partie.tourJoues - 1]);
    
    //Si le score du joueur 2 pour le tour actuel est plus élevé par rapport à celui du joueur 1, il est le gagnant
    }else if(Joueur1.score[Partie.tourJoues - 1] < Joueur2.score[Partie.tourJoues - 1]){
        gotoxy(xR + 6, yR + 6);
        printf("Joueur %d :", 2);
        gotoxy(xR + 6, yR + 8);
        if(strcmp(Joueur2.nom, "Ordinateur") == 0) {
            printf("L'IA est le gagnant de cette partie");
        } else {
            printf("%s vous etes le gagnant de cette partie", Joueur2.nom);
        }
        gotoxy((((xR + largeurR) - 6) - strlen("Score : ")), yR + 8);
        printf("Score : %d", Joueur2.score[Partie.tourJoues - 1]);
    
    //Si le score sont égaux, il s'agit d'un match nul
    }else{
        gotoxy(xR + 6, yR + 6);
        printf("Match nul !!!");
        gotoxy(xR + 6, yR + 8);
        printf("Vous avez obtenu le meme score pour ce tour.");
    }

    if(Partie.tourJoues == Partie.nbreTours){
        gotoxy((largeurR - strlen("Appuyez sur une touche pour terminer la partie"))/2 + xR, yR + 12);
        printf("Appuyez sur une touche pour terminer la partie");
    } else {
        gotoxy((largeurR - strlen("Appuyez sur une touche pour continuer"))/2 + xR, yR + 12);
        printf("Appuyez sur une touche pour continuer");
    }
    
    // Solution Windows simple : utiliser system("pause")
    system("pause > nul");  // Rediriger la sortie vers nul pour éviter l'affichage du message par défaut
    
    if(Partie.tourJoues == Partie.nbreTours){
        Effacer();
        AfficherGagnantPartie();
    }
}

void AfficherGagnantPartie(){
    //On récupère la taille de l'écran
    int consoleLargeur, consoleHauteur;

    //Initialisation des variables qui stockeront les dimensions de la console
    consoleLargeur = 0;
    consoleHauteur = 0;
    getConsoleSize(&consoleLargeur, &consoleHauteur);

    int largeurR = consoleLargeur/2;
    int hauteurR = consoleHauteur/2;
    //Mise en place du rectangle
    int xR = (largeurR) - ((largeurR)/2);
    int yR = (hauteurR) - ((hauteurR)/2);
    rectangle(xR, yR, largeurR, 20);

    gotoxy(((largeurR)- strlen("GAGNANT DE LA PARTIE"))/2 + xR, yR + 4);printf("GAGNANT DE LA PARTIE");

    //Si le score total du joueur 1 pour la partie actuel est plus élevé par rapport à celui du joueur 2, il est le gagnant
    if(Joueur1.scoreTotal > Joueur2.scoreTotal){
        gotoxy(xR + 6, yR + 6);printf("Joueur %d :", 1);
        gotoxy(xR + 6, yR + 8);printf("%s vous etes le gagnant de cette partie", Joueur1.nom);
        gotoxy((((xR + largeurR) - 6) - strlen("Score total:  ")) - 1, yR + 8);printf("Score : %d", Joueur1.scoreTotal);
    
    //Si le score total du joueur 2 pour la partie actuel est plus élevé par rapport à celui du joueur 1, il est le gagnant
    }else if(Joueur1.score[Partie.tourJoues - 1] < Joueur2.score[Partie.tourJoues - 1]){
        gotoxy(xR + 6, yR + 6);printf("Joueur %d :", 2);
        gotoxy(xR + 6, yR + 8);printf("%s vous etes le gagnant de cette partie", Joueur2.nom);
        gotoxy((((xR + largeurR) - 6) - strlen("Score :  ")) - 1, yR + 8);printf("Score : %d", Joueur2.scoreTotal);
    
    //Si le score sont égaux, il s'agit d'un match nul
    }else{
        gotoxy(xR + 6, yR + 6);printf("Match nul !!!");
        gotoxy(xR + 6, yR + 8);printf("Vous avez obtenu le meme score total pour cette partie.");
        gotoxy(xR + 6, yR + 11);printf("Joueur 1 : %s", Joueur1.nom);
        gotoxy((((xR + largeurR) - 6) - (strlen("Joueur 2 : ") + strlen(Joueur2.nom))), yR + 11);printf("Joueur 2 : %s", Joueur2.nom);
        gotoxy(xR + 6, yR + 13);printf("Score : %d", Joueur1.scoreTotal);
        gotoxy((((xR + largeurR) - 6) - strlen("Score :  ")), yR + 13);printf("Score : %d", Joueur2.scoreTotal);
        gotoxy((largeurR- strlen("Ne baisse pas les bras, tu l'auras a la prochaine partie !!"))/2 + xR, yR + 15);printf("Ne baisse pas les bras, tu l'auras a la prochaine partie !!");
    }

    gotoxy(xR + 6, yR + 17);printf("Saisissez la touche ENTRER pour terminer la partie");
    char validation = '\n';

    do{
        printf(" \b ");
        validation = getche();
    }while(validation != '\r');
    
}

/**
 * Trouve le mot le plus court possible parmi les mots valides pour le niveau facile
 * Version modifiée de LongestWord qui cherche le mot le plus court au lieu du plus long
 */
char *trouverMotCourt(char grille[]) {
    int i = 0;
    // Initialisation avec une longueur maximale pour trouver le plus court
    char *valideMot = malloc(sizeof(char) + 1);
    valideMot[0] = '\0';
    int longueurMax = 9; // Longueur maximale d'un mot dans la grille
    
    char name[13] = {'.', '/', 'd', 'i', 'c', 'o', '/', ' ', '.', 't', 'x', 't'};
    char *notUsedchar = malloc(sizeof(char) * (strlen(grille) + 1));
    strcpy(notUsedchar, grille);

    char mot[30];
    strcpy(mot, "\0");
    
    // Variable pour indiquer si on a trouvé au moins un mot valide
    int motValideFound = 0;
    
    while (grille[i] != '\0') {
        if (notUsed(notUsedchar, grille[i])) {
            name[7] = grille[i];
            FILE *fichier = NULL;
            fichier = fopen(name, "r");

            if (fichier == NULL) {
                perror("Erreur d'ouverture de fichier");
            } else {
                fgets(mot, 30, fichier);
                mot[strlen(mot) - 1] = '\0';

                while (!feof(fichier)) {
                    // Si le mot du dictionnaire respecte les lettres de la grille
                    if (strchr(grille, 'a') == NULL && strchr(mot, 'a') != NULL) {
                        strcpy(mot, "0");
                    }
                    
                    if (validationChar(mot, grille)) {
                        // On garde le mot seulement s'il est non vide et si sa longueur est entre 2 et longueurMax
                        if (strlen(mot) >= 2 && (strlen(mot) < strlen(valideMot) || !motValideFound)) {
                            free(valideMot);
                            valideMot = malloc(sizeof(char) * (strlen(mot) + 1));
                            strcpy(valideMot, mot);
                            motValideFound = 1;
                        }
                    }
                    
                    fgets(mot, 30, fichier);
                    mot[strlen(mot) - 1] = '\0';
                }
            }
            fclose(fichier);
            strcpy(notUsedchar, removeSameChar(notUsedchar, grille[i]));
        }
        i++;
    }
    
    free(notUsedchar);
    
    // Si aucun mot valide n'a été trouvé, on utilise LongestWord mais on en prend un segment
    if (!motValideFound) {
        free(valideMot);
        char *longMot = LongestWord(grille);
        // Prendre juste les 2-3 premières lettres si le mot est assez long
        int longueurUtilisee = (strlen(longMot) > 3) ? 3 : strlen(longMot);
        valideMot = malloc(sizeof(char) * (longueurUtilisee + 1));
        strncpy(valideMot, longMot, longueurUtilisee);
        valideMot[longueurUtilisee] = '\0';
        free(longMot);
    }
    
    return valideMot;
}

/**
 * Structure utilisée pour collecter tous les mots valides
 */
typedef struct {
    char **mots;      // Tableau de mots
    int *longueurs;   // Tableau des longueurs correspondantes
    int count;        // Nombre de mots trouvés
    int capacity;     // Capacité du tableau
} CollectionMots;

/**
 * Fonction utilitaire pour collecter tous les mots valides dans la grille
 */
CollectionMots *collecterMotsValides(char grille[]) {
    int i = 0;
    
    // Initialiser la collection de mots
    CollectionMots *collection = malloc(sizeof(CollectionMots));
    collection->capacity = 50;  // Capacité initiale
    collection->count = 0;
    collection->mots = malloc(sizeof(char*) * collection->capacity);
    collection->longueurs = malloc(sizeof(int) * collection->capacity);
    
    char name[13] = {'.', '/', 'd', 'i', 'c', 'o', '/', ' ', '.', 't', 'x', 't'};
    char *notUsedchar = malloc(sizeof(char) * (strlen(grille) + 1));
    strcpy(notUsedchar, grille);

    char mot[30];
    strcpy(mot, "\0");
    
    while (grille[i] != '\0') {
        if (notUsed(notUsedchar, grille[i])) {
            name[7] = grille[i];
            FILE *fichier = NULL;
            fichier = fopen(name, "r");

            if (fichier == NULL) {
                perror("Erreur d'ouverture de fichier");
            } else {
                fgets(mot, 30, fichier);
                mot[strlen(mot) - 1] = '\0';

                while (!feof(fichier)) {
                    // Si le mot du dictionnaire respecte les lettres de la grille
                    if (strchr(grille, 'a') == NULL && strchr(mot, 'a') != NULL) {
                        strcpy(mot, "0");
                    }
                    
                    if (validationChar(mot, grille) && strlen(mot) >= 2) {
                        // Vérifier si on a besoin d'augmenter la capacité
                        if (collection->count >= collection->capacity) {
                            collection->capacity *= 2;
                            collection->mots = realloc(collection->mots, sizeof(char*) * collection->capacity);
                            collection->longueurs = realloc(collection->longueurs, sizeof(int) * collection->capacity);
                        }
                        
                        // Ajouter le mot à la collection
                        collection->mots[collection->count] = malloc(sizeof(char) * (strlen(mot) + 1));
                        strcpy(collection->mots[collection->count], mot);
                        collection->longueurs[collection->count] = strlen(mot);
                        collection->count++;
                    }
                    
                    fgets(mot, 30, fichier);
                    mot[strlen(mot) - 1] = '\0';
                }
            }
            fclose(fichier);
            strcpy(notUsedchar, removeSameChar(notUsedchar, grille[i]));
        }
        i++;
    }
    
    free(notUsedchar);
    return collection;
}

/**
 * Libère la mémoire utilisée par une collection de mots
 */
void libererCollectionMots(CollectionMots *collection) {
    if (collection == NULL) return;
    
    for (int i = 0; i < collection->count; i++) {
        free(collection->mots[i]);
    }
    
    free(collection->mots);
    free(collection->longueurs);
    free(collection);
}

/**
 * Trouve un mot de longueur moyenne pour le niveau moyen
 */
char *trouverMotMoyen(char grille[]) {
    // Collecter tous les mots valides
    CollectionMots *collection = collecterMotsValides(grille);
    
    // Si aucun mot n'a été trouvé, utiliser LongestWord mais réduire sa longueur
    if (collection->count == 0) {
        char *longMot = LongestWord(grille);
        // Prendre la moitié du mot si possible
        int longueurUtilisee = (strlen(longMot) > 1) ? strlen(longMot) / 2 : 1;
        char *resultat = malloc(sizeof(char) * (longueurUtilisee + 1));
        strncpy(resultat, longMot, longueurUtilisee);
        resultat[longueurUtilisee] = '\0';
        free(longMot);
        libererCollectionMots(collection);
        return resultat;
    }
    
    // Calculer la longueur moyenne
    float longueurMoyenne = 0;
    for (int i = 0; i < collection->count; i++) {
        longueurMoyenne += collection->longueurs[i];
    }
    longueurMoyenne /= collection->count;
    
    // Trouver les mots proches de la moyenne
    int *ecarts = malloc(sizeof(int) * collection->count);
    for (int i = 0; i < collection->count; i++) {
        ecarts[i] = abs(collection->longueurs[i] - (int)longueurMoyenne);
    }
    
    // Trouver l'écart minimal
    int ecartMin = ecarts[0];
    for (int i = 1; i < collection->count; i++) {
        if (ecarts[i] < ecartMin) {
            ecartMin = ecarts[i];
        }
    }
    
    // Compter combien de mots ont cet écart minimal
    int nbMotsProches = 0;
    for (int i = 0; i < collection->count; i++) {
        if (ecarts[i] == ecartMin) {
            nbMotsProches++;
        }
    }
    
    // Choisir aléatoirement un mot parmi ceux qui ont l'écart minimal
    int indiceChoisi = rand() % nbMotsProches;
    int compteur = 0;
    int indice = 0;
    
    for (int i = 0; i < collection->count; i++) {
        if (ecarts[i] == ecartMin) {
            if (compteur == indiceChoisi) {
                indice = i;
                break;
            }
            compteur++;
        }
    }
    
    // Créer une copie du mot choisi
    char *resultat = malloc(sizeof(char) * (strlen(collection->mots[indice]) + 1));
    strcpy(resultat, collection->mots[indice]);
    
    // Libérer la mémoire
    free(ecarts);
    libererCollectionMots(collection);
    
    return resultat;
}

/**
 * Trouve le mot le plus long possible avec une variation aléatoire pour le niveau difficile
 */
char *trouverMotDifficile(char grille[]) {
    // Utiliser directement la fonction existante dans 90% des cas
    if ((float)rand() / RAND_MAX >= 0.1) {
        return LongestWord(grille);
    }
    
    // Dans 10% des cas, trouver le deuxième meilleur mot
    CollectionMots *collection = collecterMotsValides(grille);
    
    // Si on a moins de 2 mots, utiliser simplement le plus long
    if (collection->count <= 1) {
        libererCollectionMots(collection);
        return LongestWord(grille);
    }
    
    // Trier les mots par longueur décroissante (tri à bulles simple)
    for (int i = 0; i < collection->count - 1; i++) {
        for (int j = 0; j < collection->count - i - 1; j++) {
            if (collection->longueurs[j] < collection->longueurs[j + 1]) {
                // Échanger les longueurs
                int tempLongueur = collection->longueurs[j];
                collection->longueurs[j] = collection->longueurs[j + 1];
                collection->longueurs[j + 1] = tempLongueur;
                
                // Échanger les mots
                char *tempMot = collection->mots[j];
                collection->mots[j] = collection->mots[j + 1];
                collection->mots[j + 1] = tempMot;
            }
        }
    }
    
    // Sélectionner le deuxième mot le plus long s'il existe
    char *resultat = NULL;
    if (collection->count >= 2) {
        resultat = malloc(sizeof(char) * (strlen(collection->mots[1]) + 1));
        strcpy(resultat, collection->mots[1]);
    } else {
        // Fallback au cas où
        resultat = malloc(sizeof(char) * (strlen(collection->mots[0]) + 1));
        strcpy(resultat, collection->mots[0]);
    }
    
    libererCollectionMots(collection);
    return resultat;
}

/**
 * Fonction principale qui choisit un mot en fonction du niveau de difficulté
 */
char *choisirMotIA(char grille[], NiveauDifficulteIA niveau) {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));
    
    switch (niveau) {
        case FACILE:
            return trouverMotCourt(grille);
        case MOYEN:
            return trouverMotMoyen(grille);
        case DIFFICILE:
            return trouverMotDifficile(grille);
        default:
            // Par défaut, utiliser le niveau moyen
            return trouverMotMoyen(grille);
    }
}

/**
 * Exemple d'utilisation du système de difficulté d'IA
 * Cette fonction peut être appelée pour tester les niveaux d'IA
 */
void demonstrationIA(char grille[]) {
    printf("\n===== Démonstration des niveaux d'IA =====\n");
    
    // Afficher la grille
    printf("Grille de lettres: %s\n\n", grille);
    
    // Tester chaque niveau de difficulté
    printf("Niveau FACILE: L'IA choisit le mot le plus court possible\n");
    char *motFacile = trouverMotCourt(grille);
    printf("Mot choisi: %s (longueur: %lu)\n\n", motFacile, strlen(motFacile));
    free(motFacile);
    
    printf("Niveau MOYEN: L'IA choisit un mot de longueur moyenne\n");
    char *motMoyen = trouverMotMoyen(grille);
    printf("Mot choisi: %s (longueur: %lu)\n\n", motMoyen, strlen(motMoyen));
    free(motMoyen);
    
    printf("Niveau DIFFICILE: L'IA choisit le mot le plus long (avec variation)\n");
    char *motDifficile = trouverMotDifficile(grille);
    printf("Mot choisi: %s (longueur: %lu)\n\n", motDifficile, strlen(motDifficile));
    free(motDifficile);
    
    // Utiliser la fonction générique avec différents niveaux
    printf("Utilisation de la fonction générique choisirMotIA:\n");
    
    char *motIA1 = choisirMotIA(grille, FACILE);
    printf("Niveau FACILE: %s (longueur: %lu)\n", motIA1, strlen(motIA1));
    free(motIA1);
    
    char *motIA2 = choisirMotIA(grille, MOYEN);
    printf("Niveau MOYEN: %s (longueur: %lu)\n", motIA2, strlen(motIA2));
    free(motIA2);
    
    char *motIA3 = choisirMotIA(grille, DIFFICILE);
    printf("Niveau DIFFICILE: %s (longueur: %lu)\n", motIA3, strlen(motIA3));
    free(motIA3);
    
    printf("====================================\n");
}

void genererCaractereAleatoires(int numCommencer) {
    char *choixConsonneVoyelle=malloc(sizeof(char)*2);
 // int joueurActuel = demanderJoueurCommence(); // On appelle la fonction ici

 for (int i = 0; i < nbreTotalLettresGrille; i++) { 
     prompt();
     clearLine();
     prompt();

     printf("Joueur %d, choisissez une lettre ('c' pour consonne, 'v' pour voyelle) : ",numCommencer); 
        
     
     do {
         srand(time(NULL));  
         prompt();
         clearLine();
         prompt();
         printf("Joueur %d, choisissez une lettre ('c' pour consonne, 'v' pour voyelle) : ",numCommencer); 
         scanf("%s",choixConsonneVoyelle);
         choixConsonneVoyelle[0]=tolower(choixConsonneVoyelle[0]);
     } while (strcmp(choixConsonneVoyelle,"c")!=0 && strcmp(choixConsonneVoyelle,"v")!=0);

     if (!strcmp(choixConsonneVoyelle,"c")) {
         Partie.lettreGenerees[i] = consonnes[rand() % 20];
     } else {
         Partie.lettreGenerees[i] = voyelles[rand() % 6];
     }
     if(numCommencer==1) numCommencer=2;
     else numCommencer=1;
     
     EntryField();
      printf("%c",Partie.lettreGenerees[i]);
     fflush(stdin);
     gambaseX++;
     // Changer de joueur sans ternaire

 }
 free(choixConsonneVoyelle);
}

// Fonction utilitaire pour réinitialiser la liste des mots possibles
void InitialiserListeDesMots() {
    // Si la liste n'est pas vide, on la vide
    MotPossible *courant = ListeDesMots.premier;
    MotPossible *suivant;
    
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant->mot);
        free(courant);
        courant = suivant;
    }
    
    // Initialiser la liste vide
    ListeDesMots.premier = NULL;
}

/**
 * Démarre une partie en mode solo contre l'IA
 * @param Joueur1name Nom du joueur humain
 * @param niveauIA Niveau de difficulté de l'IA (FACILE, MOYEN, DIFFICILE)
 * @param tourActuel Tour actuel à jouer
 * @param totalTours Nombre total de tours pour la partie
 * @param numCommencer Joueur qui commence (1 = humain, 2 = IA)
 */
void DemarrerPartieSolo(char Joueur1name[], NiveauDifficulteIA niveauIA, int tourActuel, int totalTours, int numCommencer) {
    // Réinitialiser la liste des mots possibles pour éviter des problèmes
    InitialiserListeDesMots();
    
    Effacer();
    gotoxy(0, 4);
    printf(" Tour %d", tourActuel);
    
    // On initialise les variables de récupération des dimensions de la console
    initialiserVariables();
    
    // On affiche l'interface et on charge les noms des joueurs
    afficherInterface();
    namePlay1(); printf("%s", Joueur1name);
    namePlay2(); printf("Ordinateur"); // Afficher "Ordinateur" pour le joueur 2
    
    // Afficher les scores existants au début du tour
    mettreAJourAffichageScores();
    
    // En fonction du joueur qui commence, on appelle la fonction de génération pour mode solo
    genererCaractereAletoiresSolo(numCommencer, niveauIA);
    
    // Effacer le texte de prompt après le remplissage de la grille
    prompt();
    clearLine();
    
    // Initialisation des variables pour stocker les mots
    char motJoueur[10] = "";
    char motIA[10] = "";
    
    if (numCommencer == 1) {
        // Tour du joueur humain d'abord
        gotoxy(EntryFieldX1, EntryFieldY1 - 1);
        printf("Joueur, entrez votre mot:");
        
        // Le joueur entre son mot (le mot est bien sûr hashé)
        centeredhash1(motJoueur, 10);
        strcpy(Joueur1.mot[tourActuel - 1], motJoueur);
        
        // Effacer le texte du joueur
        EffacerZone(EntryFieldX1, EntryFieldY1 - 1, strlen("Joueur, entrez votre mot:"), 1);
        
        // Tour de l'IA ensuite
        gotoxy(EntryFieldX2, EntryFieldY2 - 1);
        printf("L'IA réfléchit...");
        
        // Simuler la réflexion de l'IA
        Sleep(1000 + rand() % 1000); // Entre 1 et 2 secondes
        
        // L'IA choisit son mot selon le niveau de difficulté
        char *motChoisiIA = choisirMotIA(Partie.lettreGenerees, niveauIA);
        strncpy(motIA, motChoisiIA, 9);
        motIA[9] = '\0'; // Assurer la terminaison de la chaîne
        free(motChoisiIA); // Libérer la mémoire allouée par choisirMotIA
        
        strcpy(Joueur2.mot[tourActuel - 1], motIA);
        
        // Effacer le texte de l'IA
        EffacerZone(EntryFieldX2, EntryFieldY2 - 1, strlen("L'IA réfléchit..."), 1);
        
        // Afficher les mots des deux joueurs
        centerword1(Joueur1.mot[tourActuel - 1]);
        centerword2(Joueur2.mot[tourActuel - 1]);
    } else {
        // Tour de l'IA d'abord
        gotoxy(EntryFieldX2, EntryFieldY2 - 1);
        printf("L'IA réfléchit...");
        
        // Simuler la réflexion de l'IA
        Sleep(1000 + rand() % 1000); // Entre 1 et 2 secondes
        
        // L'IA choisit son mot selon le niveau de difficulté
        char *motChoisiIA = choisirMotIA(Partie.lettreGenerees, niveauIA);
        strncpy(motIA, motChoisiIA, 9);
        motIA[9] = '\0'; // Assurer la terminaison de la chaîne
        free(motChoisiIA); // Libérer la mémoire allouée par choisirMotIA
        
        strcpy(Joueur2.mot[tourActuel - 1], motIA);
        
        // Effacer le texte de l'IA
        EffacerZone(EntryFieldX2, EntryFieldY2 - 1, strlen("L'IA réfléchit..."), 1);
        
        // Tour du joueur humain ensuite
        gotoxy(EntryFieldX1, EntryFieldY1 - 1);
        printf("Joueur, entrez votre mot:");
        
        // Le joueur entre son mot
        centeredhash1(motJoueur, 10);
        strcpy(Joueur1.mot[tourActuel - 1], motJoueur);
        
        // Effacer le texte du joueur
        EffacerZone(EntryFieldX1, EntryFieldY1 - 1, strlen("Joueur, entrez votre mot:"), 1);
        
        // Afficher les mots des deux joueurs
        centerword2(Joueur2.mot[tourActuel - 1]);
        centerword1(Joueur1.mot[tourActuel - 1]);
    }
    
    // Message de validation
    int positionLoading = (gameEntryFieldY + gameEntryFieldHeight - 1) + ((EntryFieldY1 - (gameEntryFieldY + gameEntryFieldHeight - 1)) / 2);
    EcritureDynamique("Un instant, nous procedons a la validation....", EntryFieldX1 + 2, positionLoading, 50);
    Sleep(2000);
    
    // Vérification et calcul des scores
    Joueur1.score[tourActuel - 1] = validationChar(Joueur1.mot[tourActuel - 1], Partie.lettreGenerees) ? validationMots(Joueur1.mot[tourActuel - 1]) : 0;
    Joueur1.scoreTotal += Joueur1.score[tourActuel - 1];
    
    // Pour l'IA, on s'assure que le mot est valide (cela devrait toujours être le cas si choisirMotIA est bien implémenté)
    Joueur2.score[tourActuel - 1] = validationChar(Joueur2.mot[tourActuel - 1], Partie.lettreGenerees) ? validationMots(Joueur2.mot[tourActuel - 1]) : 0;
    Joueur2.scoreTotal += Joueur2.score[tourActuel - 1];
    
    Partie.tourJoues = tourActuel;
    
    // Afficher "Vous auriez pu trouver:" au-dessus du rectangle de l'IA
    char* messageTrouver = "Vous auriez pu trouver:";
    int messageX = AIX + ((EntryFieldLong - strlen(messageTrouver)) / 2);
    gotoxy(messageX, AIY - 1);
    printf("%s", messageTrouver);
    
    // Afficher le mot le plus long possible
    char *motLePlusLong = LongestWord(Partie.lettreGenerees);
    centerwordAI(motLePlusLong);
    free(motLePlusLong);
    
    // Mise à jour de l'affichage des scores
    mettreAJourAffichageScores();
    Sleep(1500);

    // Ajouter un message de débug pour vérifier si cette partie est exécutée
    gotoxy(0, 0);
    printf("Affichage de la liste des mots possibles...");
    Sleep(500);
    
    // Afficher la liste des mots possibles - assurons-nous qu'elle n'est pas vide
    MotPossible *temp = ListeDesMots.premier;
    int compteur = 0;
    while (temp != NULL) {
        compteur++;
        temp = temp->suivant;
    }
    
    // Si ListeDesMots est vide, ajoutons un mot fictif pour tester
    if (compteur == 0) {
        // Créer un mot fictif pour le test
        MotPossible *nouveauMot = (MotPossible*)malloc(sizeof(MotPossible));
        nouveauMot->mot = (char*)malloc(5 * sizeof(char));
        strcpy(nouveauMot->mot, "test");
        nouveauMot->suivant = NULL;
        ListeDesMots.premier = nouveauMot;
    }
    
    // Affichage de la liste des mots possibles
    afficherListeMotsPossibles();
    
    // Nettoyer l'écran et afficher le gagnant du tour
    gotoxy(0, 0);
    printf("Affichage du gagnant du tour...");
    Sleep(500);
    
    Effacer();
    AfficherGagnantTour();
    
    // Ne pas revenir au menu après la fin du tour
    // La fonction lancerJeuSolo gérera le passage au tour suivant
}

/**
 * Lance une partie en mode solo contre l'IA
 * Permet de choisir le niveau de difficulté
 */
void lancerJeuSolo() {
    Effacer();
    int largeurTermi = 0, hauteurTermi = 0;
    
    // Récupérer les dimensions du terminal pour les affichages
    getConsoleSize(&largeurTermi, &hauteurTermi);
    
    // Variable pour stocker si on vient de charger une partie
    int vientDeCharger = partieChargee;
    
    // Si on ne vient pas de charger une partie, afficher l'animation de début
    if (!vientDeCharger) {
        char TexteDebut[] = "MODE SOLO - JOUEZ CONTRE L'IA !";
        // Pause
        Sleep(1000);
        
        // Position du curseur
        int x = (largeurTermi - strlen(TexteDebut)) / 2;
        int y = hauteurTermi / 2;
        
        // Afficher le message progressivement caractère par caractère
        EcritureDynamique(TexteDebut, x, y, 100);
        
        // Pause et effacer pour lancer le Jeu
        Sleep(1000);
    }
    
    // Choisir le niveau de difficulté de l'IA si on commence une nouvelle partie
    NiveauDifficulteIA niveauIA = MOYEN; // Niveau par défaut
    
    if (!vientDeCharger) {
        Effacer();
        char TexteNiveau[] = "Choisissez le niveau de difficulté de l'IA:";
        int x = (largeurTermi - strlen(TexteNiveau)) / 2;
        int y = hauteurTermi / 3;
        
        EcritureDynamique(TexteNiveau, x, y, 50);
        
        char TexteOptions[] = "1. Facile  2. Moyen  3. Difficile";
        x = (largeurTermi - strlen(TexteOptions)) / 2;
        y += 2;
        
        EcritureDynamique(TexteOptions, x, y, 50);
        
        int choixNiveau = 0;
        char buffer[10];
        do {
            gotoxy(largeurTermi / 2, y + 2);
            clearLine();
            gotoxy(largeurTermi / 2, y + 2);
            scanf("%s", buffer);
            
            if (isNumber(buffer)) {
                choixNiveau = atoi(buffer);
            }
        } while (choixNiveau < 1 || choixNiveau > 3);
        
        switch (choixNiveau) {
            case 1:
                niveauIA = FACILE;
                break;
            case 2:
                niveauIA = MOYEN;
                break;
            case 3:
                niveauIA = DIFFICILE;
                break;
            default:
                niveauIA = MOYEN; // Par sécurité
        }
    } else {
        // Si on vient de charger une partie, on peut demander le niveau de difficulté
        // car cette information n'est pas sauvegardée
        Effacer();
        char TexteNiveau[] = "Partie chargée! Choisissez le niveau de difficulté de l'IA:";
        int x = (largeurTermi - strlen(TexteNiveau)) / 2;
        int y = hauteurTermi / 3;
        
        EcritureDynamique(TexteNiveau, x, y, 50);
        
        char TexteOptions[] = "1. Facile  2. Moyen  3. Difficile";
        x = (largeurTermi - strlen(TexteOptions)) / 2;
        y += 2;
        
        EcritureDynamique(TexteOptions, x, y, 50);
        
        int choixNiveau = 0;
        char buffer[10];
        do {
            gotoxy(largeurTermi / 2, y + 2);
            clearLine();
            gotoxy(largeurTermi / 2, y + 2);
            scanf("%s", buffer);
            
            if (isNumber(buffer)) {
                choixNiveau = atoi(buffer);
            }
        } while (choixNiveau < 1 || choixNiveau > 3);
        
        switch (choixNiveau) {
            case 1:
                niveauIA = FACILE;
                break;
            case 2:
                niveauIA = MOYEN;
                break;
            case 3:
                niveauIA = DIFFICILE;
                break;
            default:
                niveauIA = MOYEN; // Par sécurité
        }
        
        // Réinitialiser partieChargee pour ne pas répéter l'écran de bienvenue
        partieChargee = 0;
    }
    
    // Variable pour savoir si on continue à jouer
    int continuerJeu = 1;
    // Déclaration de convert ici pour qu'il soit disponible dans toute la fonction
    char *convert = NULL;
    
    while (continuerJeu && Partie.tourJoues < Partie.nbreTours) {
        // Démarrer le tour actuel
        DemarrerPartieSolo(Joueur1.nom, niveauIA, Partie.tourJoues + 1, Partie.nbreTours, Partie.numJoueurCommencer);
        
        // Si c'est le dernier tour, sortir de la boucle
        if (Partie.tourJoues >= Partie.nbreTours) {
            break;
        }
        
        // Demander si on veut continuer (pas besoin de JouerEncore car AfficherGagnantTour demande déjà de continuer)
        Effacer();
        char texte[100];
        strcpy(texte, "Voulez-vous continuer au tour suivant ?");
        EcritureDynamique(texte, (largeurTermi - strlen(texte)) / 2, hauteurTermi / 3, 50);
        
        strcpy(texte, "Oui [O] / Non [N]");
        EcritureDynamique(texte, (largeurTermi - strlen(texte)) / 2, hauteurTermi / 3 + 2, 50);
        
        gotoxy(largeurTermi / 2, hauteurTermi / 3 + 4);
        char choix = '\0';
        char validation = '\0';
        int choixValide = 0;
        
        // Obtenir le choix de l'utilisateur
        while (!choixValide) {
            choix = toupper(getche());
            if (choix == 'O' || choix == 'N') {
                while (1) {
                    validation = getche();
                    if (validation == '\r') {
                        choixValide = 1;
                        break;
                    } else if (validation == '\b') {
                        printf("\b \b");
                        break;
                    } else {
                        printf("\b \b");
                    }
                }
            } else {
                printf("\b \b");
            }
        }
        
        if (choix == 'N') {
            continuerJeu = 0;
            
            // Proposer de sauvegarder
            Effacer();
            strcpy(texte, "Point de sauvegarde!");
            EcritureDynamique(texte, (largeurTermi - strlen(texte)) / 2, (hauteurTermi / 2) - 1, 0);
            strcpy(texte, "Sauvegardez votre progression (1). Si (0) elle sera perdue.[1/0]");
            EcritureDynamique(texte, (largeurTermi - strlen(texte)) / 2, (hauteurTermi / 2), 0);
            
            int sauvegarder = 0;
            
            do {
                gotoxy(largeurTermi / 2, (hauteurTermi / 2) + 1);
                clearLine();
                gotoxy(largeurTermi / 2, (hauteurTermi / 2) + 1);
                scanf("%s", texte);
                sauvegarder = strtol(texte, &convert, 10);
            } while ((sauvegarder != 1 && sauvegarder != 0) || !isNumber(texte));
            
            if (sauvegarder) {
                // S'assurer que Joueur2 est bien "Ordinateur"
                strcpy(Joueur2.nom, "Ordinateur");
                sauvegarderPartie();
                Sleep(2000);
            }
            
            afficherMenu();
            return; // Sortir de la fonction pour éviter de retourner au menu deux fois
        } else {
            // Si on a choisi de continuer, demander qui commence le tour suivant
            strcpy(texte, "Qui entamera le tour suivant: Joueur [1] / IA [2] ?");
            Effacer();
            EcritureDynamique(texte, (largeurTermi - strlen(texte)) / 2, hauteurTermi / 3, 0);
            
            do {
                gotoxy(largeurTermi / 2, hauteurTermi / 3 + 2);
                clearLine();
                gotoxy(largeurTermi / 2, hauteurTermi / 3 + 2);
                scanf("%s", texte);
                Partie.numJoueurCommencer = strtol(texte, &convert, 10);
            } while ((Partie.numJoueurCommencer != 1 && Partie.numJoueurCommencer != 2) || !isNumber(texte));
        }
    }
    
    // Si tous les tours ont été joués, supprimer la sauvegarde avant de revenir au menu
    if (Partie.tourJoues >= Partie.nbreTours && verifSauvegarde()) {
        effacerSauvegarde();
    }
    
    // Retourner au menu principal
    afficherMenu();
}

/**
 * Initialise une nouvelle partie en mode solo contre l'IA
 * Permet de configurer le nom du joueur, le nombre de tours, et qui commence
 */
void nouvellePartieSolo() {
    Effacer();
    char choixNouvellePartie = 'O';
    char choix = '\n';
    char validation = '\0';
    int bon = 0;
    
    // Si une sauvegarde existe
    if (verifSauvegarde()) {
        char texte[] = "Attention: Une partie a ete sauvegardee. En poursuivant vous ecraserez les sauvegardes!\n";
        int largeur = 0, hauteur = 0;
        getConsoleSize(&largeur, &hauteur);
        largeur = (largeur - strlen(texte)) / 2;
        hauteur /= 2;
        EcritureDynamique(texte, largeur, hauteur - 1, 0);
        
        strcpy(texte, "Voulez-vous lancer la nouvelle partie? Oui[O] / Non[N]\n");
        getConsoleSize(&largeur, &hauteur);
        largeur = (largeur - strlen(texte)) / 2;
        hauteur /= 2;
        EcritureDynamique(texte, largeur, hauteur, 0);
        getConsoleSize(&largeur, &hauteur);
        gotoxy((largeur / 2), (hauteur / 2) + 1);
        
        while (!bon) {
            choixNouvellePartie = getche();
            if (choixNouvellePartie == 'O' || choixNouvellePartie == 'N') {
                while (1) {
                    validation = getche();
                    if (validation == '\r') {
                        bon = 1;
                        break;
                    } else if (validation == '\b') {
                        gotoxy((largeur / 2), (hauteur / 2) + 1);
                        gotoxy((largeur / 2), (hauteur / 2) + 1);
                        choixNouvellePartie = '\n';
                        break;
                    } else {
                        printf("\b \b");
                        gotoxy((largeur / 2) + 1, (hauteur / 2) + 1);
                    }
                }
            } else {
                printf("\b \b"); // Effacer les caractères qui ne répondent pas à ceux demandés
                gotoxy((largeur / 2), (hauteur / 2) + 1);
            }
        }
        
        if (choixNouvellePartie == 'O') {
            effacerSauvegarde();
        }
        Effacer();
    }
    
    // Récupérer les informations si une nouvelle partie est lancée
    if (choixNouvellePartie == 'O') {
        InitialiserJoueur();
        InitialiserPartie();
        
        char **lesinfos = malloc(sizeof(char *) * 3);
        for (int i = 0; i < 3; i++) {
            lesinfos[i] = malloc(sizeof(char) * 70);
        }
        
        strcpy(lesinfos[0], "Nom du joueur: \n");
        strcpy(lesinfos[1], "Combien de tours voulez-vous effectuer?\n");
        strcpy(lesinfos[2], "Qui desire entamer la partie: Joueur [1] / IA [2]\n");
        
        int largeurT = 0;
        int hauteurT = 0;
        int x = 0, y = 0;
        bon = 0;
        choix = '\n';
        validation = '\0';
        
        for (int i = 0; i < 3; i++) {
            getConsoleSize(&largeurT, &hauteurT);
            x = (largeurT - strlen(lesinfos[i])) / 2;
            y = (hauteurT / 3) + (2 * i);
            gotoxy(x, y);
            printf("%s", lesinfos[i]);
            getConsoleSize(&largeurT, &hauteurT);
            gotoxy((largeurT / 2), y + 1);
            char test[10] = "a";
            char *converti = NULL;
            
            switch (i) {
                case 0: {
                    scanf("%s", Joueur1.nom);
                    gotoxy((largeurT / 2), y + 1);
                    clearLine();
                    EcritureDynamique(Joueur1.nom, ((largeurT - strlen(Joueur1.nom)) / 2), (y + 1), 0);
                    // Pour le mode solo, Joueur2 est toujours "Ordinateur"
                    strcpy(Joueur2.nom, "Ordinateur");
                    break;
                }
                case 1: {
                    do {
                        gotoxy((largeurT / 2), y + 1);
                        clearLine();
                        gotoxy((largeurT / 2), y + 1);
                        scanf("%s", test);
                    } while (!isNumber(test) || test[0] == '\r');
                    Partie.nbreTours = strtol(test, &converti, 10);
                    gotoxy((largeurT / 2), y + 1);
                    clearLine();
                    EcritureDynamique(test, ((largeurT - strlen(test)) / 2), (y + 1), 0);
                    break;
                }
                case 2: {
                    strcpy(test, "a");
                    do {
                        if (strcmp(test, "\r")) {
                            gotoxy((largeurT / 2), y + 1);
                        }
                        gotoxy((largeurT / 2), y + 1);
                        clearLine();
                        gotoxy((largeurT / 2), y + 1);
                        scanf("%s", test);
                        Partie.numJoueurCommencer = strtol(test, &converti, 10);
                    } while (!isNumber(test) || (Partie.numJoueurCommencer != 1 && Partie.numJoueurCommencer != 2));
                    Partie.numJoueurCommencer = strtol(test, &converti, 10);
                    gotoxy((largeurT / 2), y + 1);
                    clearLine();
                    EcritureDynamique(test, ((largeurT - strlen(test)) / 2), (y + 1), 0);
                    break;
                }
            }
        }
        
        for (int i = 0; i < 3; i++) {
            free(lesinfos[i]);
        }
        free(lesinfos);
        
        // Lancer le jeu en mode solo
        lancerJeuSolo();
    } else {
        afficherMenu();
    }
}

