#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <ctype.h>
#include <windows.h>
#include "fonctions.h"
// Définition des constantes
const int nbreJoueur = 2;
const int nbreTotalLettresGrille = 9;
const char voyelles[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
const char consonnes[20] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z'};

//Définition des variables
char nomJoueur1[10];
char nomJoueur2[10];
int numJoueurCommencerPartie;
int nbreTours;
int taille_consonne;
int taille_voyelle;
int index_consonne;
int index_voyelle;
char choixConsonneVoyelle;
char lettresGenerees[9]; 
char choixmenu;
int width,height;

// Définition des variables globales supplémentaires
int scoreJoueur1 = 0;           // Score du joueur 1, initialisé à 0
int scoreJoueur2 = 0;           // Score du joueur 2, initialisé à 0
int toursJoues = 0;             // Nombre de tours joués, initialisé à 0
char grille[9] = {0};          // Grille de jeu avec taille exacte pour stocker nbreTotalLettresGrille caractères

int scorefieldX1, scorefieldY1, scorefieldLong, scorefieldHeight;
int scorefieldCursorX1, scorefieldCursorY1;
int mainframeX, mainframeY, mainframeLong, mainframeHeight;
int scorefieldX2, scorefieldY2;
int gameEntryFieldX, gameEntryFieldY, gameEntryFieldHeight, gameEntryFieldLong;
int EntryFieldX1, EntryFieldY1, EntryFieldLong, EntryFieldHeight;
int EntryFieldX2, EntryFieldY2;
int AIX, AIY;
int play1CursorX, play1CursorY;
int play2CursorX, play2CursorY;
int AImoveX, AImoveY;
int score1moveX, score1moveY;
int score2moveX, score2moveY;
int gambaseX, gamebaseY;
int height,width;
int frameX,frameY,frameLong,frameHeight;

// Définition des tableaux pour l'historique des mots et scores
char motsJoueur1[MAX_TOURS][20] = {{0}};  // Initialisé avec des chaînes vides
char motsJoueur2[MAX_TOURS][20] = {{0}};  // Initialisé avec des chaînes vides
int scoresJoueur1[MAX_TOURS] = {0};       // Initialisé avec des zéros
int scoresJoueur2[MAX_TOURS] = {0};       // Initialisé avec des zéros

// Définition des fonctions

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
 * Enregistre les mots et scores d'un tour dans l'historique.
 * Met à jour les tableaux globaux et les scores totaux.
 * 
 * @return 1 si l'enregistrement a réussi, 0 si le nombre maximum de tours est atteint
 */
int enregistrerTour(const char motJoueur1[], const char motJoueur2[], int scoreMotJoueur1, int scoreMotJoueur2) {
    // Vérifier si le nombre maximum de tours n'est pas dépassé
    if (toursJoues >= MAX_TOURS) {
        printf("Erreur : Nombre maximum de tours atteint.\n");
        return 0;
    }
    
    // Vérifier que les tours joués ne dépassent pas le nombre de tours total défini pour la partie
    if (toursJoues >= nbreTours) {
        printf("Erreur : Tous les tours de la partie ont déjà été joués.\n");
        return 0;
    }

    // Enregistrer les mots (avec vérification de longueur pour éviter les débordements)
    strncpy(motsJoueur1[toursJoues], motJoueur1, 19);
    motsJoueur1[toursJoues][19] = '\0'; // Assurer la terminaison de la chaîne
    
    strncpy(motsJoueur2[toursJoues], motJoueur2, 19);
    motsJoueur2[toursJoues][19] = '\0'; // Assurer la terminaison de la chaîne
    
    // Enregistrer les scores du tour
    scoresJoueur1[toursJoues] = scoreMotJoueur1;
    scoresJoueur2[toursJoues] = scoreMotJoueur2;
    
    // Mettre à jour les scores totaux
    scoreJoueur1 += scoreMotJoueur1;
    scoreJoueur2 += scoreMotJoueur2;
    
    // Incrémenter le compteur de tours joués
    toursJoues++;
    
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
    fscanf(fichier, "Nom Joueur 1: %s\n", nomJoueur1);
    fscanf(fichier, "Nom Joueur 2: %s\n", nomJoueur2);

    // Lecture des scores
    fscanf(fichier, "Score Joueur 1: %d\n", &scoreJoueur1);
    fscanf(fichier, "Score Joueur 2: %d\n", &scoreJoueur2);

    // Lecture du nombre de tours
    fscanf(fichier, "Tours joués: %d\n", &toursJoues);
    fscanf(fichier, "Tours totaux: %d\n", &nbreTours);

    // Réinitialiser les tableaux d'historique
    for (int i = 0; i < MAX_TOURS; i++) {
        motsJoueur1[i][0] = '\0';
        motsJoueur2[i][0] = '\0';
        scoresJoueur1[i] = 0;
        scoresJoueur2[i] = 0;
    }

    // Ignorer la ligne "Review de la partie:"
    char buffer[100];
    fgets(buffer, sizeof(buffer), fichier);

    // Lecture des historiques de mots et scores tour par tour
    for (int i = 0; i < toursJoues; i++) {
        // Lire la ligne "Tour X:"
        fgets(buffer, sizeof(buffer), fichier);
        
        // Lire les données du joueur 1
        fscanf(fichier, "%*[^:]: Mot: %19[^,], Score: %d\n", motsJoueur1[i], &scoresJoueur1[i]);
        
        // Lire les données du joueur 2
        fscanf(fichier, "%*[^:]: Mot: %19[^,], Score: %d\n", motsJoueur2[i], &scoresJoueur2[i]);
    }

    fclose(fichier);
    printf("Partie chargée avec succès, incluant l'historique des mots et scores.\n");
    return 1;
}

/**
 * Affiche un résumé détaillé de la partie sauvegardée.
 * Utilise les variables globales pour afficher les informations de la partie.
 */
void reviewPartie() {
    // Vérifier si une partie a été chargée ou si on est en cours de partie
    if (toursJoues == 0) {
        printf("Aucune partie en cours ou chargée. Rien à afficher.\n");
        return;
    }

    // Affichage des informations générales
    printf("Informations de la partie:\n");
    printf("Joueur 1: %s (Score: %d)\n", nomJoueur1, scoreJoueur1);
    printf("Joueur 2: %s (Score: %d)\n", nomJoueur2, scoreJoueur2);
    printf("Progression: %d tours joués sur %d\n", toursJoues, nbreTours);
    
    // Affichage de l'historique des tours
    printf("Historique des tours:\n");
    for (int i = 0; i < toursJoues; i++) {
        printf("Tour %d:\n", i + 1);
        printf("%s - Mot: %s, Score: %d\n", nomJoueur1, motsJoueur1[i], scoresJoueur1[i]);
        printf("%s - Mot: %s, Score: %d\n", nomJoueur2, motsJoueur2[i], scoresJoueur2[i]);
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

// Définition des fonctions

//Fonction pour compter le nombre de caractères dans un mot


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
        return strlen(mot);
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
       
// Définition des fonctions

void tailleTerminal(int *largeur, int *hauteur){
    CONSOLE_SCREEN_BUFFER_INFO terminal;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminal);
    *largeur= terminal.srWindow.Right - terminal.srWindow.Left +1;
    *hauteur= terminal.srWindow.Bottom - terminal.srWindow.Top +1;
}


void getConsoleSize(int *width, int *height) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        *width = 0;
        *height = 0;
    }
}
void gotoxy(int x, int y) 
{ 
    HANDLE hConsoleOutput; 
    COORD dwCursorPosition; 
    fflush(stdout); 
    dwCursorPosition.X = x; 
    dwCursorPosition.Y = y; 
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition); 
} 

void Effacer()
{
    #ifdef WIN32
    system("cls");
    system("prompt $G");
    #elif
    system("clear");
    system("export PS1='> '");
    #endif
}


int isNumber(char *string){
    for(int i=0; i<strlen(string); i++){
        if(!isdigit(string[i])){
            return 0;
        }
    }
    return 1;
}


void EcritureDynamique(char texte[], int x, int y,int vitesse){
    for(int i=0; i<strlen(texte); i++){
        gotoxy(x+i,y);
        Sleep(vitesse);
        printf("%c",texte[i]);
     }
 }


 int JouerEncore(){
    
    char texte[]="On passe a la partie suivante?";
    char textechoix[]="Oui[O] / Non [N]";
    int largeurTermi=0, hauteurTermi=0;

    //recuperer la taille du terminal
    tailleTerminal(&largeurTermi, &hauteurTermi);

    //Centrer le 1er texte et l'écrire
    int x=(largeurTermi-strlen(texte))/2;
    int y= hauteurTermi/2;
    EcritureDynamique(texte,x,y,50);

    //Centrer le 2ème texte et lécrire
    x=(largeurTermi-strlen(textechoix))/2;
    y= hauteurTermi/2;
    EcritureDynamique(textechoix,x,y+1,50);

    //Recupérer la récuperer la réponse
    gotoxy((largeurTermi/2),(hauteurTermi/2)+2);
    char choix='\n';
    char validation='\0';
     int bon=0;
     while(!bon){
        choix=getche();
        if(choix=='O' || choix=='N')
        {
            while(1)
            {
                validation=getche();
                if(validation=='\r'){
                    if(choix=='O')
                    return 1;
                    else return 0;
                }else if(validation=='\b'){
                    gotoxy((largeurTermi/2),(hauteurTermi/2)+2);
                    printf(" "); 
                    gotoxy((largeurTermi/2),(hauteurTermi/2)+2);
                    choix='\n';
                    break;
                }else{
                    printf("\b \b");
                    gotoxy((largeurTermi/2)+1,(hauteurTermi/2)+2);
                }
            }
        }else
        {
            printf("\b \b"); //Effacer les caractères qui ne répondent pas à ceux demandés
            gotoxy((largeurTermi/2),(hauteurTermi/2)+2);
        }
     }
    
}


void clearLine() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD written;

    // Obtenir la position actuelle du curseur
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD pos = csbi.dwCursorPosition;
    
    // Déplacer le curseur au début de la ligne
    pos.X = 0;
    SetConsoleCursorPosition(hConsole, pos);

    // Effacer la ligne avec des espaces
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, pos, &written);

    // Remettre le curseur au début de la ligne
    SetConsoleCursorPosition(hConsole, pos);
}



void DemarrerJeu(char Joueur1[], char Joueur2[], int tourActuel, int totalTours, int numCommencer)
    {
    //On lance les fonctions interfaces et autres 



    }




void NouvellePartie()
{
    Effacer();
char choixNouvellePartie='O';
char choix='\n';
char validation='\0';
int bon=0;
//Si une sauvegarde existe
    if(!verifSauvegarde()){
        
            char texte[]="Attention: Une partie a ete sauvegardee. En poursuivant vous ecraserez les sauvegardes!\n";
            int largeur=0, hauteur=0;
            tailleTerminal(&largeur,&hauteur);
            largeur = (largeur-strlen(texte))/2;
            hauteur /= 2;
            EcritureDynamique(texte,largeur,hauteur-1,0);
            
            strcpy(texte,"Voulez-vous lancer la nouvelle partie? Oui[O] / Non[N]\n");
            tailleTerminal(&largeur,&hauteur);
            largeur = (largeur-strlen(texte))/2;
            hauteur /= 2;
            EcritureDynamique(texte,largeur,hauteur,0);
            tailleTerminal(&largeur,&hauteur);
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
            Effacer();
        }
    }

    //Recupérer les informations si une nouvelle partie est lancée
    if(choixNouvellePartie=='O')
    {   
        char **lesinfos=malloc(sizeof(char *)*4);
       
        for(int i=0; i<5; i++){
            lesinfos[i]=malloc(sizeof(char)*70);
        }
        strcpy(lesinfos[0],"Nom du joueur 1: \n");
        strcpy(lesinfos[1],"Nom du joueur 2: \n");
        strcpy(lesinfos[2],"Combien de parties voulez-vous effectuez?\n");
        strcpy(lesinfos[3],"Qui desire entamer la partie: Joueur 1 [1] ou Joueur 2 [2]\n");
        
        int largeurT=0;
        int hauteurT=0;
        int x=0, y=0;
        bon=0;
        choix='\n';
        validation='\0';

        for(int i=0; i<4; i++)
        {
            tailleTerminal(&largeurT,&hauteurT);
            x=(largeurT-strlen(lesinfos[i]))/2;
            y=(hauteurT/3)+(2*i);
            gotoxy(x,y);
            printf("%s",lesinfos[i]);
            tailleTerminal(&largeurT,&hauteurT);
            gotoxy((largeurT/2),y+1);   
            char test[10]="a";
            char *converti=NULL;
            switch(i){
                case 0:{
                scanf("%s",nomJoueur1);
                gotoxy((largeurT/2),y+1);
                clearLine();
                EcritureDynamique(nomJoueur1,((largeurT-strlen(nomJoueur1))/2),(y+1),0);
                break;
                }
                case 1:{
                    scanf("%s",nomJoueur2);
                    gotoxy((largeurT/2),y+1);
                    clearLine();
                    EcritureDynamique(nomJoueur2,((largeurT-strlen(nomJoueur2))/2),(y+1),0);
                    break;
                }
                case 2:{
                  do{
                      gotoxy((largeurT/2),y+1);
                      clearLine();
                      gotoxy((largeurT/2),y+1);
                      scanf("%s",test);    
                  }while(!isNumber(test) || test[0]=='\r');  
                  nbreTours=strtol(test,&converti,10);
                  gotoxy((largeurT/2),y+1);
                  clearLine();
                  EcritureDynamique(test,((largeurT-strlen(nomJoueur2))/2),(y+1),0);
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
                        numJoueurCommencerPartie=strtol(test,&converti,10);
                    }while(!isNumber(test) || (numJoueurCommencerPartie!=1 && numJoueurCommencerPartie!=2));
                    numJoueurCommencerPartie=strtol(test,&converti,10);
                    break;
                }                
            }    
        }
        for(int i=0; i<4; i++){
            free(lesinfos[i]);
        }
        free(lesinfos);
        scoreJoueur1=0; 
        scoreJoueur2=0;

        DemarrerJeu(nomJoueur1,nomJoueur2,1,nbreTours,numJoueurCommencerPartie);
    }else{
        afficherMenu();
    }
}


void lancerJeu(){
    
    Effacer();
    int largeurTermi=0, hauteurTermi=0;
        
    //Definir les dimensions du terminal pour les affichages
    tailleTerminal(&largeurTermi, &hauteurTermi);

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
    Effacer();

       int one=1;
       char *convert;
       char *texte=malloc(sizeof(char)*65);
       do{
            if(toursJoues<nbreTours){
                if(JouerEncore()){
                    Effacer();
                    strcpy(texte,"Qui desire entamer la partie: Joueur 1 [1] ou Joueur 2 [2]\n");
                    EcritureDynamique(texte,(largeurTermi-strlen(texte))/2,(hauteurTermi/2)-1,0);
                    do{
                        gotoxy(largeurTermi/2,(hauteurTermi/2));
                        clearLine();
                        gotoxy(largeurTermi/2,(hauteurTermi/2));
                        scanf("%s",texte);
                        numJoueurCommencerPartie=strtol(texte,&convert,10);
                    }while((numJoueurCommencerPartie!=1 && numJoueurCommencerPartie!=2) || !isNumber(texte)); 
                    numJoueurCommencerPartie=strtol(texte,&convert,10);
                  free(texte);
                  free(convert);
            DemarrerJeu(nomJoueur1,  nomJoueur2, toursJoues+1,nbreTours,numJoueurCommencerPartie);
                }
            }else{
                afficherMenu();
            }
        }while(toursJoues<=nbreTours);
      
}



void rectangle(int x, int y, int lon, int haut)
{
    int i;
    gotoxy(x,y); printf("%c",218);
    gotoxy(x+lon,y); printf("%c",191);
    gotoxy(x, y+haut); printf("%c",192);
    gotoxy(x+lon, y+haut); printf("%c",217);     
    for (i=1; i<lon;i++)
    {
        gotoxy(x+i,y); printf("%c",196); 
        gotoxy(x+i,y+haut); printf("%c",196);
    }
    for (i=1; i<haut;i++)
    {
        gotoxy(x,y+i); printf("%c",179); 
        gotoxy(x+lon,y+i); printf("%c",179);
    }
}


void afficherMenu() {
    char choixmenu;
    getConsoleSize(&width,&height);
    int menuWidth = (int)(width * 0.4);
    int menuHeight = (int)(height * 0.4);
    int menuX = (width - menuWidth) / 2;
    int menuY = (height - menuHeight) / 2;
    int upper=menuHeight/3;
    int optionZone=2*menuHeight/3;
    while (1) {
        system("clear || cls");  // Efface l'écran (compatible Linux/Windows)
        rectangle(menuX,menuY,menuWidth,upper);
        rectangle(menuX,menuY+upper+1,menuWidth,optionZone);
       
       gotoxy(menuX+(menuWidth-4)/2,menuY+(upper/2)); printf("MENU");
       
       gotoxy(menuX+3,menuY+upper+optionZone*0.3);printf("X - Charger Partie");
       gotoxy(menuX+3,menuY+upper+optionZone*0.5);printf("Y - Nouvelle Partie");
       gotoxy(menuX+3,menuY+upper+optionZone*0.9);printf("Q - Quitter");
       rectangle(menuX,menuY+menuHeight+1,menuWidth,menuHeight*0.3);
       gotoxy(menuX+3,menuY+menuHeight+(upper)/2);printf("Votre choix : ");


        choixmenu = getchar(); // Récupère l'entrée utilisateur
        while (getchar() != '\n'); // Vide le buffer pour éviter les erreurs

        choixmenu = tolower(choixmenu); // Convertit en minuscule

        switch (choixmenu) {
            case 'x':
                chargerPartie();
                break;
            case 'y':
                nouvellePartie();
                break;
            case 'q':
                printf("Fermeture du programme...\n");
                exit(0);
            default:
                // L'entrée invalide est ignorée, pas d'affichage d'erreur
                break;
        }
    }

}

     //-----hashage-----
    void hashWord( char *word , int size){
        int i = 0 ;
        char ch ;

        while(i < size-1){
            ch = getch() ;
            // sortie lorsque l'utilisateur appuie la touche entrée
            if( ch == '\r'){
            word[i]='\0';
            break; 
            }

            // supression d'un indice lorsque l'utilisateur appuie la touche backspace
            if( ch == '\b' && i > 0){
                    printf("\b \b") ;
                    i-- ;
            }
            //incrémentation de caractère à la chaîne
            else{
                word[i] = ch ;
                printf("*") ;
                i++ ;
            }

        }
    }

    //-----cursorMove-----
            void gotoxy(int x, int y) 
            { 
                HANDLE hConsoleOutput; 
                COORD dwCursorPosition; 
                fflush(stdout); 
                dwCursorPosition.X = x; 
                dwCursorPosition.Y = y; 
                hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
                SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition); 
            } 

            void initialiserVariables() {
                getConsoleSize(&width,&height);
                frameX=(width-(8*width/9))/2;
                frameY=(height-(8*height/9))/2;
                frameLong=8*width/9;
                frameHeight=8*height/9;
                scorefieldX1=frameX+3;
                scorefieldY1=frameY+3;
                scorefieldX2= mainframeLong+5;
                scorefieldY2= scorefieldY1;
                scorefieldLong=frameLong*0.2;
                scorefieldHeight=frameHeight*0.15;
                mainframeLong=frameLong*0.5;
                mainframeX=frameX+(frameLong-mainframeLong)/2;
                mainframeY=frameY;
                mainframeHeight=frameHeight;
                scorefieldX2 = mainframeX + mainframeLong + 3;
                scorefieldY2 = scorefieldY1;
            
                gameEntryFieldX = mainframeX + (mainframeLong / 8);
                gameEntryFieldY = scorefieldY1;
                gameEntryFieldHeight = scorefieldHeight;
                gameEntryFieldLong = (3 * mainframeLong) / 4;
            
                EntryFieldX1 = gameEntryFieldX;
                EntryFieldY1 = mainframeY + (mainframeHeight / 2);
                EntryFieldLong = gameEntryFieldLong;
                EntryFieldHeight = gameEntryFieldHeight / 2;
            
                EntryFieldX2 = EntryFieldX1;
                EntryFieldY2 = EntryFieldY1 + 5;
            
                AIX = EntryFieldX1;
                AIY = EntryFieldY2 + 5;

                play1CursorX = EntryFieldX1 + (EntryFieldLong / 3);
                play1CursorY = EntryFieldY1 + (EntryFieldHeight / 2);
            
                play2CursorX = EntryFieldX2 + (EntryFieldLong / 3);
                play2CursorY = EntryFieldY2 + (EntryFieldHeight / 2);
            
                AImoveX = AIX + (EntryFieldLong / 3);
                AImoveY = AIY + (EntryFieldHeight / 2);
            
                score1moveX = scorefieldX1 + (scorefieldLong / 2);
                score1moveY = scorefieldY1 + (scorefieldHeight / 2);
            
                score2moveX = scorefieldX2 + (scorefieldLong / 2);
                score2moveY = scorefieldY2 + (scorefieldHeight / 2);
            
                gambaseX = gameEntryFieldX + ((gameEntryFieldLong-9) / 2);
                gamebaseY = gameEntryFieldY + (gameEntryFieldHeight / 2);

                
            }
            
    //-----rectangle------        
        void rectangle(int x, int y, int lon, int haut)
    {
        int i;
        gotoxy(x,y); printf("%c",218);
        gotoxy(x+lon,y); printf("%c",191);
        gotoxy(x, y+haut); printf("%c",192);
        gotoxy(x+lon, y+haut); printf("%c",217);     
        for (i=1; i<lon;i++)
        {
            gotoxy(x+i,y); printf("%c",196); 
            gotoxy(x+i,y+haut); printf("%c",196);
        }
        for (i=1; i<haut;i++)
        {
            gotoxy(x,y+i); printf("%c",179); 
            gotoxy(x+lon,y+i); printf("%c",179);
        }
    }
    void setConsoleSize(int width, int height) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
        // 1. Définir la taille du buffer
        COORD bufferSize = {width, height};
        SetConsoleScreenBufferSize(hConsole, bufferSize);
    
        // 2. Définir la taille de la fenêtre (rectangulaire)
        SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    }
    //----tailleEcran------
    void getConsoleSize(int *width, int *height) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        } else {
            *width = 0;
            *height = 0;
        }
    }



    //-----Interfaces-----
    void afficherInterface(){
        int i=0;
        for(i=0;i<15;i++){
            printf("\n\n");
        }
        // system("mode con: cols=170 lines=50");
        rectangle(scorefieldX1,scorefieldY1,scorefieldLong,scorefieldHeight);
        rectangle(mainframeX,mainframeY,mainframeLong,mainframeHeight);
        rectangle(scorefieldX2,scorefieldY2,scorefieldLong,scorefieldHeight);
        rectangle(gameEntryFieldX,gameEntryFieldY,gameEntryFieldLong,gameEntryFieldHeight);
        rectangle(EntryFieldX1, EntryFieldY1, EntryFieldLong, EntryFieldHeight);
        rectangle(EntryFieldX2, EntryFieldY2, EntryFieldLong, EntryFieldHeight);
        rectangle(AIX,AIY,EntryFieldLong,EntryFieldHeight);
        
        for(i=0;i<15;i++){
            printf("\n");
        }

    }
// Centrage du mot du joueur 1
    void centerword1(char *word){
        int i=0;
        initialiserVariables();
         player1();
          for(i=0;i<strlen(word);i++){
             printf(" ");
          }
          initialiserVariables();
          play1CursorX=EntryFieldX1 + ((EntryFieldLong-strlen(word)) / 2);
          player1();
          printf("%s",word);
    }
// Centrage du mot du joueur 2
    void centerword2(char *word){
        int i=0;
        initialiserVariables();
         player2();
          for(i=0;i<strlen(word);i++){
             printf(" ");
          }
          initialiserVariables();
          play2CursorX=EntryFieldX2 + ((EntryFieldLong-strlen(word)) / 2);
          player2();
          printf("%s",word);
    }
// centrage du mot trouvé par l'IA
    void centerwordAI(char *word){
        int i=0;
        initialiserVariables();
          AIX=EntryFieldX1 + ((EntryFieldLong-strlen(word)) / 2);
          AImove();
          printf("%s",word);
    }
    //  hashe et centre le mot saisit du joueur 1  
    void centeredhash1(char *word, int size){
        int i=0;
          player1();
          hashWord(word,size);
          player1();
          for(i=0;i<strlen(word);i++){
             printf(" ");
          }
          initialiserVariables();
          play1CursorX=EntryFieldX1 + ((EntryFieldLong-strlen(word)) / 2);
          player1();
          for(i=0;i<strlen(word);i++){
            printf("*");
         }

    }

    //  hashe et centre le mot saisit du joueur 2
    void centeredhash2(char *word, int size){
        int i=0;
          player2();
          hashWord(word,size);
          player2();
          for(i=0;i<strlen(word);i++){
             printf(" ");
          }
          initialiserVariables();
          play2CursorX=EntryFieldX2 + ((EntryFieldLong-strlen(word)) / 2);
          player2();
          for(i=0;i<strlen(word);i++){
            printf("*");
         }

    }

    //  redirige champ d'entrée joueur 1
    void player1(){
        gotoxy(play1CursorX,play1CursorY);
    }
    //  redirige champ d'entrée joueur 2
    void player2(){
        gotoxy(play2CursorX,play2CursorY);
    }
    //  redirige champ IA
    void AImove(){
        gotoxy(AImoveX,AImoveY);
    }
    //  redirige champ score joueur 1
    void player1Score(){
        gotoxy(score1moveX,score1moveY);
    }
    //  redirige champ score joueur 2
    void player2Score(){
        gotoxy(score2moveX,score2moveY);
    }
    //  redirige champ d'entrée de jeu voyelle consonne
    void EntryField(){
        gotoxy(gambaseX,gamebaseY);
    }
    // redirige nom joueur 1
    void namePlay1(){
        gotoxy(score1moveX-3,score1moveY-(score1moveY/3));
    }
    // redirige nom joueur 2
    void namePlay2(){
        gotoxy(score2moveX-3,score2moveY-(score2moveY/3));
    }
    // Jouer

// Nouvelles fonctions pour améliorer la structure du code

// Initialise et affiche l'interface complète avec les scores, noms et grille
void initialiserInterface() {
    afficherInterface();
    namePlay1();printf("Joueur 1");
    namePlay2();printf("Joueur 2");
    player1Score();printf("0");
    player2Score();printf("0");
    EntryField();printf("WASOPEDNLQ");
}

// Demande et traite la saisie du mot pour le joueur 1
void demanderMotJoueur1(char *mot) {
    gotoxy(EntryFieldX1, EntryFieldY1-1);
    printf("Joueur 1, entrez votre mot:");
    player1();
    centeredhash1(mot, 10);
}

// Demande et traite la saisie du mot pour le joueur 2
void demanderMotJoueur2(char *mot) {
    gotoxy(EntryFieldX2, EntryFieldY2-1);
    printf("Joueur 2, entrez votre mot:");
    player2();
    centeredhash2(mot, 10);
}
