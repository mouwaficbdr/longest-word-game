#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <ctype.h>
#include <math.h>    // Pour fabs()
#include <time.h>    // Pour time() et rand()
#include "../fonction.h/controller.h"
#include "../fonction.h/utilitaire.h"
#include "../fonction.h/view.h"

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
ConfigIA ConfigurationIA; // Configuration du mode IA


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
    // Réinitialiser les structures de données avant de charger
    InitialiserJoueur();
    InitialiserPartie();
    
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
        char tempNom[20];
        if (fscanf(fichier, "%[^ ] - Mot: %[^,], Score: %d\n", tempNom, Joueur1.mot[i], &Joueur1.score[i]) != 3) {
            printf("Erreur lors de la lecture des données du joueur 1 au tour %d\n", i+1);
            fclose(fichier);
            return 0;
        }
        
        // Lire les données du joueur 2
        if (fscanf(fichier, "%[^ ] - Mot: %[^,], Score: %d\n", tempNom, Joueur2.mot[i], &Joueur2.score[i]) != 3) {
            printf("Erreur lors de la lecture des données du joueur 2 au tour %d\n", i+1);
            fclose(fichier);
            return 0;
        }
    }

    fclose(fichier);
    
    // Vérification que les données chargées sont cohérentes
    if (Partie.nbreTours <= 0 || Partie.tourJoues < 0 || Partie.tourJoues > Partie.nbreTours) {
        printf("Données de partie incohérentes dans le fichier de sauvegarde.\n");
        return 0;
    }
    
    // Afficher un message de succès
    printf("Partie chargee avec succes!\n");
    Sleep(1000);
    
    // Déterminer qui a le droit de commencer le tour actuel
    // Alternance entre les joueurs - Si le dernier joueur à commencer était le joueur 1, alors c'est au tour du joueur 2
    if (Partie.tourJoues % 2 == 0) {
        Partie.numJoueurCommencer = 1; // Joueur 1 commence
    } else {
        Partie.numJoueurCommencer = 2; // Joueur 2 commence
    }
    
    return 1; // Retourner simplement 1 pour indiquer le succès du chargement
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
    if (!verifSauvegarde()) {
        // Aucun message
        return 1;  // On considère que c'est un succès puisqu'il n'y a rien à effacer
    }

    int resultat = remove("sauvegarde.txt");
    if (resultat == 0) {
        // Suppression silencieuse - pas de message
        return 1;
    } else {
        // En cas d'erreur, pas de message non plus
        return 0;
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
    char motDico[35], path[] = "../dico/ .txt";

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
        return strlen(mot);
    }

    return 0;

    fclose(fichier);
}


char *LongestWord(char grille[])
{
    //i pacours la grille
   int i=0;
 // le mot valide le plus long de taille 0 à l'initialisation
  char *valideMot=malloc(sizeof(char)+1);
  valideMot[0]='\0';
  char name[15]={'.','.','/','d','i','c','o','/',' ','.','t','x','t'};
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
          if(strchr(grille,'a')==NULL && strchr(mot,'a')!=NULL){
                strcpy(mot,"0");
          }
            if(validationChar(mot,grille))
              {
           //On alloue et on récupère le mot valide seulement s'il est plus long que le précedent
              if(strlen(mot)>strlen(valideMot))
                  {
                    free(valideMot);
                  valideMot=malloc(sizeof(char)*(strlen(mot)+1));
                  strcpy(valideMot,mot);
           //Si le mot récupéré est aussi long que la grille des lettres il est le plus long
                  if(strlen(valideMot)==nbreTotalLettresGrille)
                      {return valideMot;}
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


int JouerEncore(){
    char texte[]="On passe au tour suivant?";
    int largeurTermi=0, hauteurTermi=0;

    //recuperer la taille du terminal
    getConsoleSize(&largeurTermi, &hauteurTermi);
    char c='R';
    while(hauteurTermi<30 || c!='R'){
        gotoxy(0,1);
        clearLine();
        EcritureDynamique("Veuillez agrandir votre terminal et appuyer sur [R]\n",0,0,0);
        scanf("%c", &c);
        getConsoleSize(&largeurTermi, &hauteurTermi);
    }
    //Centrer le 1er texte et l'écrire
    int xR=(3*largeurTermi-4)/4;
    int yR= (3*hauteurTermi)/4;
    rectangle(xR,yR,(largeurTermi/4),7);
    
    xR=1+((largeurTermi/4)-strlen(texte))/2+(3*largeurTermi)/4;
    yR= (7*hauteurTermi/8)-1;
    EcritureDynamique(texte,xR,yR,50);
     
    //Centrer le 2ème texte et l'écrire
    strcpy(texte,"Oui[O] / Non [N]");
    xR=1+((largeurTermi/4)-strlen(texte))/2+(3*largeurTermi)/4;
    EcritureDynamique(texte,xR,yR+1,50);

    //Recupérer la récuperer la réponse
    gotoxy((7*largeurTermi/8),(7*hauteurTermi/8)+1);
    char choix='\n';
    char validation='\0';
     int bon=0;
     char *convert;
     while(!bon){
        choix=getche();
        if(choix=='O' || choix=='N')
        {
            while(1)
            {
                validation=getche();
                if(validation=='\r'){
                    if(choix=='O'){
                    strcpy(texte,"Qui entamera le tour: ");
                    gotoxy(1+(3*largeurTermi)/4,(7*hauteurTermi/8)-1);
                    printf("                                ");
                    EcritureDynamique(texte,1+((largeurTermi/4)-strlen(texte))/2+(3*largeurTermi)/4,(7*hauteurTermi/8)-1,0);
                    strcpy(texte," Joueur [1]/[2]?");
                    EcritureDynamique(texte,1+((largeurTermi/4)-strlen(texte))/2+(3*largeurTermi)/4,(7*hauteurTermi/8),0);
                    
                    // Effacer le caractère 'O' qui reste à l'écran
                    gotoxy((7*largeurTermi/8),(7*hauteurTermi/8)+1);
                    printf(" ");
                    
                    do{
                        gotoxy(1+(3*largeurTermi)/4,(7*hauteurTermi/8)+2);
                        printf("                                ");
                        gotoxy((7*largeurTermi/8),(7*hauteurTermi/8)+1);
                        scanf("%s",texte);
                        Partie.numJoueurCommencer=strtol(texte,&convert,10);
                    }while((Partie.numJoueurCommencer!=1 && Partie.numJoueurCommencer!=2) || !isNumber(texte)); 
                    Partie.numJoueurCommencer=strtol(texte,&convert,10);
                  
                  free(convert);
                        return 1;
                    }
                        
                    else return 0;
                }else if(validation=='\b'){
                    gotoxy((7*largeurTermi/8),(7*hauteurTermi/8)+1);
                    printf(" "); 
                    gotoxy((7*largeurTermi/8),(7*hauteurTermi/8)+1);
                    choix='\n';
                    break;
                }else{
                    printf("\b \b");
                    gotoxy((7*largeurTermi/8)+1,(7*hauteurTermi/8)+1);

                }
            }
        }else
        {
            printf("\b \b"); //Effacer les caractères qui ne répondent pas à ceux demandés
            gotoxy((7*largeurTermi/8),(7*hauteurTermi/8)+1);

        }
     }
   
     return 0;
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
        
    //Definir les dimensions du terminal pour les affichages
    getConsoleSize(&largeurTermi, &hauteurTermi);

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
    
    // Menu principal avec rectangles pour chaque option
    Effacer();
    char titre[] = "MENU PRINCIPAL";
    int titreX = (largeurTermi - strlen(titre)) / 2;
    EcritureDynamique(titre, titreX, hauteurTermi/4, 50);
    
    // Options du menu
    char option1[] = "NOUVELLE PARTIE (2 JOUEURS)";
    char option2[] = "MODE SOLO VS IA";
    char option3[] = "CHARGER PARTIE";
    char option4[] = "QUITTER";
    
    // Dimensions des rectangles
    int rectLargeur = largeurTermi / 2;
    int rectHauteur = 3;
    int rectX = largeurTermi / 4;
    
    // Position y des options
    int optionY1 = hauteurTermi/2 - 8;
    int optionY2 = hauteurTermi/2 - 3;
    int optionY3 = hauteurTermi/2 + 2;
    int optionY4 = hauteurTermi/2 + 7;
    
    // Dessiner les rectangles et afficher les options
    rectangle(rectX, optionY1, rectLargeur, rectHauteur);
    gotoxy(rectX + (rectLargeur - strlen(option1)) / 2, optionY1 + 1);
    printf("%s", option1);
    
    rectangle(rectX, optionY2, rectLargeur, rectHauteur);
    gotoxy(rectX + (rectLargeur - strlen(option2)) / 2, optionY2 + 1);
    printf("%s", option2);
    
    rectangle(rectX, optionY3, rectLargeur, rectHauteur);
    gotoxy(rectX + (rectLargeur - strlen(option3)) / 2, optionY3 + 1);
    printf("%s", option3);
    
    rectangle(rectX, optionY4, rectLargeur, rectHauteur);
    gotoxy(rectX + (rectLargeur - strlen(option4)) / 2, optionY4 + 1);
    printf("%s", option4);
    
    // Instructions pour la sélection
    char instructions[] = "Utilisez les touches 1-4 pour selectionner une option: ";
    int instrX = (largeurTermi - strlen(instructions)) / 2;
    gotoxy(instrX, hauteurTermi/2 + 12);
    printf("%s", instructions);
    
    int choixMenu = 0;
    char input[10];
    scanf("%s", input);
    
    if (isNumber(input)) {
        choixMenu = atoi(input);
    }
    
    switch(choixMenu) {
        case 1:
            // Mode 2 joueurs existant
            initialiserModeIA(0, 1); // Désactiver le mode IA
            nouvellePartie();
            break;
        case 2:
            // Mode solo contre l'IA
            {
                Effacer();
                
                // Demander les informations de la partie
                char nomJoueur[15];
                int nbreTours;
                
                gotoxy((largeurTermi - strlen("Entrez votre nom (max 14 caracteres): ")) / 2, hauteurTermi/3);
                printf("Entrez votre nom (max 14 caracteres): ");
                scanf("%14s", nomJoueur);
                
                gotoxy((largeurTermi - strlen("Entrez le nombre de tours (max 50): ")) / 2, hauteurTermi/3 + 2);
                printf("Entrez le nombre de tours (max %d): ", MAX_TOURS);
                
                char tourInput[10];
                do {
                    scanf("%9s", tourInput);
                    if (isNumber(tourInput)) {
                        nbreTours = atoi(tourInput);
                    } else {
                        nbreTours = 0;
                    }
                    
                    if (nbreTours <= 0 || nbreTours > MAX_TOURS) {
                        gotoxy((largeurTermi - strlen("Nombre invalide. Entrez une valeur entre 1 et 50: ")) / 2, hauteurTermi/3 + 3);
                        printf("Nombre invalide. Entrez une valeur entre 1 et %d: ", MAX_TOURS);
                    }
                } while (nbreTours <= 0 || nbreTours > MAX_TOURS);
                
                // Sélectionner la difficulté
                int difficulte = selectionnerDifficulteIA();
                
                // Lancer la partie solo
                demarrerPartieSolo(nomJoueur, nbreTours, difficulte);
            }
            break;
        case 3:
            // Charger partie (code existant)
            if(verifSauvegarde()) {
                if(chargerPartie()) {
                    gotoxy(10, 20);
                    printf("Partie chargée avec succès!");
                    Sleep(1000);
                    // Démarrer la partie correctement en commençant par le prochain tour à jouer
                    DemarrerPartie(Joueur1.nom, Joueur2.nom, Partie.tourJoues + 1, Partie.nbreTours, Partie.numJoueurCommencer);
                }
            } else {
                Effacer();
                char message[] = "Aucune sauvegarde disponible.";
                gotoxy((largeurTermi - strlen(message)) / 2, hauteurTermi/2);
                printf("%s", message);
                Sleep(2000);
                lancerJeu(); // Retour au menu
            }
            break;
        case 4:
            // Quitter
            Effacer();
            exit(0);
            break;
        default:
            // Option invalide
            Effacer();
            char message[] = "Option invalide. Veuillez réessayer.";
            gotoxy((largeurTermi - strlen(message)) / 2, hauteurTermi/2);
            printf("%s", message);
            Sleep(2000);
            lancerJeu(); // Retour au menu
            break;
    }

    char *convert;
    char *texte=malloc(sizeof(char)*65);
    do{
          if(Partie.tourJoues<Partie.nbreTours){
              if(JouerEncore()){ 
                  DemarrerPartie(Joueur1.nom, Joueur2.nom, Partie.tourJoues+1, Partie.nbreTours, Partie.numJoueurCommencer);
              }else{
                  Effacer();
                  strcpy(texte,"Point de sauvegarde!");
                  EcritureDynamique(texte,(largeurTermi-strlen(texte))/2,(hauteurTermi/2)-1,0);            
                  strcpy(texte,"Sauvegardez votre progression (1). Si (0) elle sera perdue.[1/0]");
                  EcritureDynamique(texte,(largeurTermi-strlen(texte))/2,(hauteurTermi/2),0); 
                  do{
                      gotoxy(largeurTermi/2,(hauteurTermi/2)+1);
                      clearLine();
                      gotoxy(largeurTermi/2,(hauteurTermi/2)+1);
                      scanf("%s",texte);
                      x=strtol(texte,&convert,10);
                  }while((x!=1 && x!=0) || !isNumber(texte)); 
                  x=strtol(texte,&convert,10);    
                  if(x) {
                      sauvegarderPartie();
                      Sleep(2000);
                  }
                  
                  // Désactiver le mode IA après la sauvegarde
                  initialiserModeIA(0, 1);
                  
                  // Retour au menu principal
                  lancerJeu();
                  return;
              }
          }else{
              // Suppression automatique de la sauvegarde à la fin d'une partie complète
              // (quand tous les tours ont été joués)
              if(Partie.tourJoues >= Partie.nbreTours && Partie.nbreTours > 0 && verifSauvegarde()) {
                  effacerSauvegarde(); // Suppression silencieuse, sans message
              }
              
              // Désactiver le mode IA
              initialiserModeIA(0, 1);
              
              // Afficher le résultat final
              Effacer();
              char resultat[100];
              
              if (Joueur1.scoreTotal > Joueur2.scoreTotal) {
                  sprintf(resultat, "FIN DE LA PARTIE! %s gagne avec %d points contre %d points!", 
                          Joueur1.nom, Joueur1.scoreTotal, Joueur2.scoreTotal);
              } else if (Joueur2.scoreTotal > Joueur1.scoreTotal) {
                  sprintf(resultat, "FIN DE LA PARTIE! %s gagne avec %d points contre %d points!", 
                          Joueur2.nom, Joueur2.scoreTotal, Joueur1.scoreTotal);
              } else {
                  sprintf(resultat, "FIN DE LA PARTIE! Match nul avec %d points partout!", 
                          Joueur1.scoreTotal);
              }
              
              EcritureDynamique(resultat, (largeurTermi-strlen(resultat))/2, hauteurTermi/2, 30);
              
              // Attendre quelques secondes pour que le joueur puisse voir le résultat
              Sleep(3000);
              
              // Restauration de l'affichage du menu
              lancerJeu();
              return;
          }
      }while(Partie.tourJoues < Partie.nbreTours);
      
      free(texte);
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
    Effacer();
    gotoxy(0,4);
    printf(" Tour %d", tourActuel);
    //On lance les fonctions interfaces et autres 
    
    //On initialise les variables de récupération des dimensions de la console
    initialiserVariables();

    //On affiche l'interface et on charge le nom des joueurs
    afficherInterface();
    namePlay1();printf("%s", Joueur1name);
    namePlay2();printf("%s", Joueur2name);
    
    // Afficher les scores existants au début du tour
    mettreAJourAffichageScores();

    //En fonction du joueur qui commence, on appelle la fonction genererCaracteresAleatoires
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

        // Effacer le texte du joueur 1
        EffacerZone(EntryFieldX1,EntryFieldY1-1,strlen("Joueur 1 entrez votre mot:"),1);
        
        // Vérifier si on est en mode solo (IA)
        if (ConfigurationIA.estActif && strcmp(Joueur2.nom, "Ordinateur") == 0) {
            // Tour de l'IA
            char* motIA = jouerTourIA(Partie.lettreGenerees);
            
            if (motIA != NULL) {
                // Copier le mot de l'IA dans l'historique
                strncpy(Joueur2.mot[tourActuel-1], motIA, 9);
                Joueur2.mot[tourActuel-1][9] = '\0'; // Garantir la terminaison
                
                // Afficher le mot trouvé par l'IA
                centerword2(Joueur2.mot[tourActuel-1]);
                
                // Libérer la mémoire allouée
                free(motIA);
            }
        } else {
            // Tour normal du joueur 2
        gotoxy(EntryFieldX2, EntryFieldY2-1);
        printf("Joueur 2 entrez votre mot:");

        //Puis le joueur 2 entre son mot
        centeredhash2(Joueur2.mot[tourActuel-1], 10);
        
        // Effacer le texte du joueur 2
            EffacerZone(EntryFieldX2,EntryFieldY2-1,strlen("Joueur 2 entrez votre mot:"),1);
        }

        //On affiche le mot du joueur 1 s'il n'est pas déjà affiché
        centerword1(Joueur1.mot[tourActuel-1]);
        
        // Si on n'est pas en mode IA ou si le mot du joueur 2 n'est pas déjà affiché
        if (!ConfigurationIA.estActif || strcmp(Joueur2.nom, "Ordinateur") != 0) {
        centerword2(Joueur2.mot[tourActuel-1]);
        }

    } else { //Dans le cas contraire on commence avec le joueur 2
        // Vérifier si on est en mode solo (IA)
        if (ConfigurationIA.estActif && strcmp(Joueur2.nom, "Ordinateur") == 0) {
            // Tour de l'IA en premier
            char* motIA = jouerTourIA(Partie.lettreGenerees);
            
            if (motIA != NULL) {
                // Copier le mot de l'IA dans l'historique
                strncpy(Joueur2.mot[tourActuel-1], motIA, 9);
                Joueur2.mot[tourActuel-1][9] = '\0'; // Garantir la terminaison
                
                // Afficher le mot trouvé par l'IA
                centerword2(Joueur2.mot[tourActuel-1]);
                
                // Libérer la mémoire allouée
                free(motIA);
            }
        } else {
            // Tour normal du joueur 2
        gotoxy(EntryFieldX2, EntryFieldY2-1);
        printf("Joueur 2 entrez votre mot:");

        //Le joueur 2 entre son mot 
        centeredhash2(Joueur2.mot[tourActuel-1], 10);

            // Effacer le texte du joueur 2
            EffacerZone(EntryFieldX2,EntryFieldY2-1,strlen("Joueur 2 entrez votre mot:"),1);
        }

        // Tour du joueur 1 toujours humain
        gotoxy(EntryFieldX1, EntryFieldY1-1);
        printf("Joueur 1 entrez votre mot:");

        //Le joueur 1 entre son mot ensuite
        centeredhash1(Joueur1.mot[tourActuel-1], 10);

        // Effacer le texte du joueur 1
        EffacerZone(EntryFieldX1,EntryFieldY1-1,strlen("Joueur 1 entrez votre mot:"),1);

        //Puis on affiche les mots s'ils ne sont pas déjà affichés
        centerword1(Joueur1.mot[tourActuel-1]);
        
        if (!ConfigurationIA.estActif || strcmp(Joueur2.nom, "Ordinateur") != 0) {
            centerword2(Joueur2.mot[tourActuel-1]);
        }
    }

    //Il y aura peut être un texte pour dire qu'on procède mainteanant à la validation des mots
    Sleep(2000);
        
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

    centerwordAI(LongestWord(Partie.lettreGenerees));

    // Mise à jour de l'affichage des scores
    mettreAJourAffichageScores();
    
    // Vérifier si nous avons terminé tous les tours
    if (tourActuel >= totalTours) {
        Sleep(5000);
        return; // Retourner au lancerJeu() qui gèrera l'affichage des résultats
    }
    
    Sleep(5000);
}

/**
 * @brief
 * Initialise la configuration du mode IA
 * @param estActif 0 pour désactiver, 1 pour activer le mode IA
 * @param difficulte Niveau de difficulté (1=facile, 2=moyen, 3=difficile) 
 */
void initialiserModeIA(int estActif, int difficulte) {
    ConfigurationIA.estActif = estActif;
    ConfigurationIA.difficulte = difficulte;
    
    // Temps de réflexion selon la difficulté
    switch(difficulte) {
        case 1: // Facile
            ConfigurationIA.tempsReflexion = 800;
            break;
        case 2: // Moyen
            ConfigurationIA.tempsReflexion = 1200;
            break;
        case 3: // Difficile
            ConfigurationIA.tempsReflexion = 1800;
            break;
        default:
            ConfigurationIA.tempsReflexion = 1000;
    }
}

/**
 * @brief
 * Gère le tour de l'IA, génère un mot et l'affiche
 * @param grille La grille de lettres disponibles
 * @return char* Le mot choisi par l'IA (alloué dynamiquement, doit être libéré après usage)
 */
char* jouerTourIA(char grille[]) {
    // Vérifier si le mode IA est actif
    if (!ConfigurationIA.estActif) {
        return NULL;
    }
    
    // Afficher un message indiquant que l'IA réfléchit
    int messageX = EntryFieldX2 + ((EntryFieldLong - strlen("L'ordinateur reflechit...")) / 2);
    gotoxy(messageX, EntryFieldY2-1);
    printf("L'ordinateur reflechit...");
    
    // Simuler un temps de réflexion pour plus de réalisme
    Sleep(ConfigurationIA.tempsReflexion);
    
    // Générer un mot selon le niveau de difficulté
    char* motIA = AIChooseWord(grille, ConfigurationIA.difficulte);
    
    // Effacer le message de réflexion
    EffacerZone(EntryFieldX2, EntryFieldY2-1, EntryFieldLong, 1);
    
    // Vérifier si un mot a été trouvé
    if (motIA == NULL || strlen(motIA) == 0) {
        // Si aucun mot n'a été trouvé, générer un message d'erreur
        motIA = malloc(sizeof(char) * 5);
        strcpy(motIA, "???");
        return motIA;
    }
    
    return motIA;
}

/**
 * @brief
 * Lance une partie en mode solo contre l'IA
 * @param nomJoueur Nom du joueur humain
 * @param nbreTours Nombre de tours pour la partie
 * @param difficulte Niveau de difficulté de l'IA (1=facile, 2=moyen, 3=difficile)
 */
void demarrerPartieSolo(char nomJoueur[], int nbreTours, int difficulte) {
    // Initialiser les variables
    InitialiserJoueur();
    InitialiserPartie();
    
    // Configurer le mode IA
    initialiserModeIA(1, difficulte);
    
    // Configurer les noms des joueurs
    strcpy(Joueur1.nom, nomJoueur);
    strcpy(Joueur2.nom, "Ordinateur");
    
    // Configurer les paramètres de la partie
    Partie.nbreTours = nbreTours;
    Partie.numJoueurCommencer = 1; // Le joueur humain commence toujours
    Partie.tourJoues = 0;
    
    // Démarrer la partie
    DemarrerPartie(Joueur1.nom, Joueur2.nom, 1, nbreTours, 1);
}

/**
 * @brief
 * Affiche le menu de sélection de difficulté pour l'IA et retourne le choix
 * @return int Niveau de difficulté choisi (1=facile, 2=moyen, 3=difficile)
 */
int selectionnerDifficulteIA() {
    Effacer();
    int largeurTermi = 0, hauteurTermi = 0;
    getConsoleSize(&largeurTermi, &hauteurTermi);
    
    // Titre du menu
    char titreDifficulte[] = "CHOISISSEZ LE NIVEAU DE DIFFICULTE DE L'IA";
    int titreX = (largeurTermi - strlen(titreDifficulte)) / 2;
    EcritureDynamique(titreDifficulte, titreX, hauteurTermi/4, 50);
    
    // Options de difficulté simplifiées
    char optionFacile[] = "FACILE";
    char optionMoyen[] = "MOYEN";
    char optionDifficile[] = "DIFFICILE";
    
    // Dimensions des rectangles
    int rectLargeur = largeurTermi / 2;
    int rectHauteur = 3;
    int rectX = largeurTermi / 4;
    
    // Position y des options
    int optionY1 = hauteurTermi/2 - 6;
    int optionY2 = hauteurTermi/2;
    int optionY3 = hauteurTermi/2 + 6;
    
    // Dessiner les rectangles et afficher les options
    rectangle(rectX, optionY1, rectLargeur, rectHauteur);
    gotoxy(rectX + (rectLargeur - strlen(optionFacile)) / 2, optionY1 + 1);
    printf("1. %s", optionFacile);
    
    rectangle(rectX, optionY2, rectLargeur, rectHauteur);
    gotoxy(rectX + (rectLargeur - strlen(optionMoyen)) / 2, optionY2 + 1);
    printf("2. %s", optionMoyen);
    
    rectangle(rectX, optionY3, rectLargeur, rectHauteur);
    gotoxy(rectX + (rectLargeur - strlen(optionDifficile)) / 2, optionY3 + 1);
    printf("3. %s", optionDifficile);
    
    // Instructions pour la sélection
    char instructions[] = "Entrez votre choix (1-3): ";
    int instrX = (largeurTermi - strlen(instructions)) / 2;
    gotoxy(instrX, hauteurTermi/2 + 12);
    printf("%s", instructions);
    
    // Récupérer le choix de l'utilisateur
    int choix = 0;
    char input[10];
    int valide = 0;
    
    while (!valide) {
        gotoxy(instrX + strlen(instructions), hauteurTermi/2 + 12);
        printf("   \b\b\b"); // Effacer l'entrée précédente
        scanf("%s", input);
        
        if (isNumber(input)) {
            choix = atoi(input);
            if (choix >= 1 && choix <= 3) {
                valide = 1;
            }
        }
        
        if (!valide) {
            // Message d'erreur
            char erreur[] = "Veuillez entrer un nombre entre 1 et 3";
            int erreurX = (largeurTermi - strlen(erreur)) / 2;
            gotoxy(erreurX, hauteurTermi/2 + 13);
            printf("%s", erreur);
            Sleep(1000);
            EffacerZone(erreurX, hauteurTermi/2 + 13, strlen(erreur), 1);
        }
    }
    
    return choix;
}

/**
 * @brief Trouve le mot le plus court possible parmi les mots valides dans la grille
 * 
 * Cette fonction cherche le mot le plus court valide qui peut être formé avec les lettres
 * de la grille. Elle utilise une approche similaire à LongestWord mais inverse la logique
 * de sélection pour privilégier les mots courts.
 * 
 * @param grille La grille de lettres disponibles
 * @return char* Le mot le plus court valide (alloué dynamiquement)
 */
char *ShortestWord(char grille[])
{
    int i = 0;
    // Initialiser avec une grande taille pour garantir le remplacement
    char *valideMot = malloc(10 * sizeof(char));
    strcpy(valideMot, "abcdefghi"); // Mot fictif de taille maximale
    char name[15] = {'.','.','/','d','i','c','o','/',' ','.','t','x','t'};
    
    // Initialiser des copies de la grille
    char *notUsedchar = malloc(sizeof(char) * (strlen(grille) + 1));
    strcpy(notUsedchar, grille);

    // Le mot courant du dictionnaire
    char mot[30];
    strcpy(mot, "\0");
    
    while(grille[i] != '\0')
    {
        if(notUsed(notUsedchar, grille[i]))
        {
            name[8] = grille[i];
            FILE *fichier = NULL;
            fichier = fopen(name, "r");

            if(fichier == NULL)
            {
                perror("Erreur d'ouverture de fichier");
            }
            else
            {
                // Si le fichier est bien ouvert, on récupère chaque mot
                fgets(mot, 30, fichier);
                mot[strlen(mot) - 1] = '\0';

                while(!feof(fichier))
                {
                    // Si le mot est vide ou d'une seule lettre, on passe au suivant
                    if(strlen(mot) <= 1) {
                        fgets(mot, 30, fichier);
                        if(!feof(fichier)) {
                            mot[strlen(mot) - 1] = '\0';
                        }
                        continue;
                    }
                    
                    // Si le mot du dictionnaire respecte les lettres de la grille
                    if(validationChar(mot, grille))
                    {
                        // On récupère le mot valide seulement s'il est plus court que le précédent
                        if(strlen(mot) < strlen(valideMot))
                        {
                            free(valideMot);
                            valideMot = malloc(sizeof(char) * (strlen(mot) + 1));
                            strcpy(valideMot, mot);
                        }
                    }
                    
                    fgets(mot, 30, fichier);
                    if(!feof(fichier)) {
                        mot[strlen(mot) - 1] = '\0';
                    }
                }
            }
            fclose(fichier);
        }
        // Le caractère courant est supprimé des caractères non utilisés
        removeSameChar(notUsedchar, grille[i]);
        i++;
    }
    
    free(notUsedchar);
    return valideMot;
}

/**
 * @brief Trouve tous les mots valides dans la grille et choisit un mot de longueur médiane
 * 
 * Cette fonction collecte tous les mots valides pour la grille donnée,
 * calcule la longueur moyenne et sélectionne un mot proche de cette moyenne.
 * 
 * @param grille La grille de lettres disponibles
 * @return char* Un mot de longueur moyenne (alloué dynamiquement)
 */
char *MediumWord(char grille[])
{
    int i = 0;
    // Tableau pour stocker jusqu'à 100 mots valides
    char **motsValides = malloc(100 * sizeof(char*));
    int nbMotsValides = 0;
    int longueurTotale = 0;
    
    char name[15] = {'.','.','/','d','i','c','o','/',' ','.','t','x','t'};
    
    // Initialiser des copies de la grille
    char *notUsedchar = malloc(sizeof(char) * (strlen(grille) + 1));
    strcpy(notUsedchar, grille);

    // Le mot courant du dictionnaire
    char mot[30];
    strcpy(mot, "\0");
    
    // Parcourir toutes les lettres de la grille
    while(grille[i] != '\0' && nbMotsValides < 100)
    {
        if(notUsed(notUsedchar, grille[i]))
        {
            name[8] = grille[i];
            FILE *fichier = NULL;
            fichier = fopen(name, "r");

            if(fichier == NULL)
            {
                perror("Erreur d'ouverture de fichier");
            }
            else
            {
                // Si le fichier est bien ouvert, on récupère chaque mot
                fgets(mot, 30, fichier);
                mot[strlen(mot) - 1] = '\0';

                while(!feof(fichier) && nbMotsValides < 100)
                {
                    // Si le mot est vide ou d'une seule lettre, on passe au suivant
                    if(strlen(mot) <= 1) {
                        fgets(mot, 30, fichier);
                        if(!feof(fichier)) {
                            mot[strlen(mot) - 1] = '\0';
                        }
                        continue;
                    }
                    
                    // Si le mot du dictionnaire respecte les lettres de la grille
                    if(validationChar(mot, grille))
                    {
                        // Ajouter le mot valide à notre tableau
                        motsValides[nbMotsValides] = malloc((strlen(mot) + 1) * sizeof(char));
                        strcpy(motsValides[nbMotsValides], mot);
                        longueurTotale += strlen(mot);
                        nbMotsValides++;
                    }
                    
                    fgets(mot, 30, fichier);
                    if(!feof(fichier)) {
                        mot[strlen(mot) - 1] = '\0';
                    }
                }
            }
            fclose(fichier);
        }
        // Le caractère courant est supprimé des caractères non utilisés
        removeSameChar(notUsedchar, grille[i]);
        i++;
    }
    
    free(notUsedchar);
    
    // Si aucun mot valide n'a été trouvé
    if(nbMotsValides == 0) {
        free(motsValides);
        return ShortestWord(grille); // Retourner le mot le plus court comme fallback
    }
    
    // Calculer la longueur moyenne
    float longueurMoyenne = (float)longueurTotale / nbMotsValides;
    
    // Trouver un mot proche de la longueur moyenne
    int indiceChoisi = 0;
    float diff = 10.0; // Grande valeur initiale pour la différence
    
    for(i = 0; i < nbMotsValides; i++) {
        float diffActuelle = fabs(strlen(motsValides[i]) - longueurMoyenne);
        if(diffActuelle < diff) {
            diff = diffActuelle;
            indiceChoisi = i;
        }
    }
    
    // Sélectionner un mot aléatoirement parmi ceux proches de la moyenne (±1 caractère)
    int nbProches = 0;
    int indicesProches[100];
    
    for(i = 0; i < nbMotsValides; i++) {
        if(fabs(strlen(motsValides[i]) - longueurMoyenne) <= 1.0) {
            indicesProches[nbProches] = i;
            nbProches++;
        }
    }
    
    // S'il y a des mots proches, en choisir un au hasard
    if(nbProches > 0) {
        indiceChoisi = indicesProches[rand() % nbProches];
    }
    
    // Récupérer le mot choisi
    char *motChoisi = malloc((strlen(motsValides[indiceChoisi]) + 1) * sizeof(char));
    strcpy(motChoisi, motsValides[indiceChoisi]);
    
    // Libérer la mémoire
    for(i = 0; i < nbMotsValides; i++) {
        free(motsValides[i]);
    }
    free(motsValides);
    
    return motChoisi;
}

/**
 * @brief Version améliorée de LongestWord avec une variation aléatoire
 * 
 * Cette fonction utilise LongestWord mais ajoute 10% de chances de choisir
 * un mot légèrement plus court pour simuler une erreur occasionnelle.
 * 
 * @param grille La grille de lettres disponibles
 * @return char* Le mot choisi (alloué dynamiquement)
 */
char *DifficultWord(char grille[])
{
    // Obtenir le mot le plus long
    char *motLePlusLong = LongestWord(grille);
    
    // 10% de chances de ne pas choisir le mot optimal
    if(rand() % 100 < 10) {
        // Stocker le mot le plus long
        char *motSecondaire = malloc((strlen(motLePlusLong) + 1) * sizeof(char));
        strcpy(motSecondaire, motLePlusLong);
        
        // Chercher un mot légèrement plus court (2ème meilleur)
        int i = 0;
        char *motPlusCourtValide = NULL;
        int longueurCible = strlen(motLePlusLong) - 1;
        
        char name[15] = {'.','.','/','d','i','c','o','/',' ','.','t','x','t'};
        char *notUsedchar = malloc(sizeof(char) * (strlen(grille) + 1));
        strcpy(notUsedchar, grille);
        char mot[30];
        
        while(grille[i] != '\0')
        {
            if(notUsed(notUsedchar, grille[i]))
            {
                name[8] = grille[i];
                FILE *fichier = NULL;
                fichier = fopen(name, "r");

                if(fichier != NULL)
                {
                    fgets(mot, 30, fichier);
                    mot[strlen(mot) - 1] = '\0';

                    while(!feof(fichier))
                    {
                        if(validationChar(mot, grille) && strlen(mot) == longueurCible)
                        {
                            // Si on trouve un mot de longueur cible
                            motPlusCourtValide = malloc((strlen(mot) + 1) * sizeof(char));
                            strcpy(motPlusCourtValide, mot);
                            fclose(fichier);
                            free(notUsedchar);
                            free(motLePlusLong);
                            return motPlusCourtValide;
                        }
                        
                        fgets(mot, 30, fichier);
                        if(!feof(fichier)) {
                            mot[strlen(mot) - 1] = '\0';
                        }
                    }
                    fclose(fichier);
                }
            }
            removeSameChar(notUsedchar, grille[i]);
            i++;
        }
        
        free(notUsedchar);
        
        // Si on n'a pas trouvé de mot plus court, on retourne le mot original
        if(motPlusCourtValide == NULL) {
            return motSecondaire;
        } else {
            free(motSecondaire);
            return motPlusCourtValide;
        }
    }
    
    // 90% du temps, on retourne le mot optimal
    return motLePlusLong;
}

/**
 * @brief Fonction principale pour choisir un mot selon le niveau de difficulté
 * 
 * Cette fonction sélectionne l'algorithme approprié en fonction du niveau de difficulté choisi.
 * 
 * @param grille La grille de lettres disponibles
 * @param niveau Le niveau de difficulté (1=Facile, 2=Moyen, 3=Difficile)
 * @return char* Le mot choisi selon le niveau (alloué dynamiquement)
 */
char *AIChooseWord(char grille[], int niveau)
{
    // Initialiser le générateur de nombres aléatoires si ce n'est pas déjà fait
    static int initialized = 0;
    if (!initialized) {
        srand(time(NULL));
        initialized = 1;
    }
    
    switch(niveau) {
        case 1: // Facile
            return ShortestWord(grille);
        case 2: // Moyen
            return MediumWord(grille);
        case 3: // Difficile
        default:
            return DifficultWord(grille);
    }
}

