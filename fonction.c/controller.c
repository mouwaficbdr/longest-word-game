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
    MotPossible *ceMotValide=malloc(sizeof(MotPossible*));
    ceMotValide->mot=malloc(1+strlen(mot)*sizeof(char));
    strcpy(ceMotValide->mot,mot);
    ceMotValide->suivant=NULL;

    MotPossible *pointeur=malloc(sizeof(MotPossible*));
    int compteur=0;
    static int nbrElement=0;
    if(nbrElement==13){
        return;
    }
    
    if(ListeDesMots.premier==NULL){
        ListeDesMots.premier=ceMotValide;
    }else{
        pointeur=ListeDesMots.premier;
            while(pointeur!=NULL){
                if(strlen(mot)==strlen(pointeur->mot)){
                    compteur++; 
                }
                nbrElement++;
                pointeur=pointeur->suivant;
            }
            if(nbrElement<13) nbrElement=0;
            if(compteur>=3){
                return;
            }
            ceMotValide->suivant=ListeDesMots.premier;
            ListeDesMots.premier=ceMotValide;
        
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
    int xR=(3*largeurTermi)/4;
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
                    do{
                        gotoxy(1+(3*largeurTermi)/4,(7*hauteurTermi/8)+1);
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
             DemarrerPartie(Joueur1.nom,  Joueur2.nom, Partie.tourJoues+1,Partie.nbreTours,Partie.numJoueurCommencer);
            }else{
                Effacer();
                strcpy(texte,"Point de sauvegarde!");
                EcritureDynamique(texte,(largeurTermi-strlen(texte))/2,(hauteurTermi/2)-1,0);            
                strcpy(texte,"Sauvegardez votre progression (1).Si (0) elle sera perdue.[1/0]");
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
    centerwordAI(LongestWord(Partie.lettreGenerees));

    // Mise à jour de l'affichage des scores
    mettreAJourAffichageScores();
    Sleep(1500);
    afficherListeMotsPossibles();

    Effacer();
    AfficherGagnantPartie();

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
    rectangle(xR, yR, largeurR, 15);

    //Positionnement des texte de joueur gagnant

    gotoxy(((largeurR)- strlen("GAGNANT DE LA PARTIE"))/2 + xR, yR + 4);printf("GAGNANT DE LA PARTIE %d", Partie.tourJoues);
    
    //Si le score du joueur 1 pour le tour actuel est plus élevé par rapport à celui du joueur 2, il est le gagnant
    if(Joueur1.score[Partie.tourJoues - 1] > Joueur2.score[Partie.tourJoues - 1]){
        gotoxy(xR + 6, yR + 6);printf("Joueur %d :", 1);
        gotoxy(xR + 6, yR + 8);printf("%s vous etes le gagnant de cette partie", Joueur1.nom);
        gotoxy((((xR + largeurR) - 6) - strlen("Score : ")), yR + 8);printf("Score : %d", Joueur1.score[Partie.tourJoues - 1]);
    
    //Si le score du joueur 2 pour le tour actuel est plus élevé par rapport à celui du joueur 1, il est le gagnant
    }else if(Joueur1.score[Partie.tourJoues - 1] < Joueur2.score[Partie.tourJoues - 1]){
        gotoxy(xR + 6, yR + 6);printf("Joueur %d :", 2);
        gotoxy(xR + 6, yR + 8);printf("%s vous etes le gagnant de cette partie", Joueur2.nom);
        gotoxy((((xR + largeurR) - 6) - strlen("Score : ")), yR + 8);printf("Score : %d", Joueur2.score[Partie.tourJoues - 1]);
    
    //Si le score sont égaux, il s'agit d'un match nul
    }else{
        gotoxy(xR + 6, yR + 6);printf("Match nul !!!");
        gotoxy(xR + 6, yR + 8);printf("Vous avez obtenu le meme score pour ce tour.");
    }


    if(Partie.tourJoues == Partie.nbreTours){
        gotoxy((largeurR- strlen("Ne baisse pas les bras, tu l'auras a la prochaine partie !!"))/2 + xR, yR + 10);printf("Ne baisse pas les bras, tu l'auras a la prochaine partie !!");
        gotoxy((largeurR - strlen("Appuyez sur la touche ENTRER pour terminer la partie"))/2 + xR-1, yR + 12);printf("Appuyez sur la touche ENTRER pour terminer la partie");

        gotoxy((2*xR+largeurR)/2,yR + 13);
        char validation = '\n';

        do{
            printf("\b \b");
            validation = getche();
        }while(validation != '\r');
    }
    
}


