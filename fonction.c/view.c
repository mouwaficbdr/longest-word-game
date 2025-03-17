#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include "../fonction.h/view.h"
#include "../fonction.h/utilitaire.h"
#include "../fonction.h/controller.h"

// Prototypes des fonctions pour éviter les déclarations implicites
void afficherNotificationTour(int numeroTour);
void afficherReviewPartie(void);

//Dimensions du terminal et rectangle qui composent l'affichage global
int width,height;               
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



void afficherMenu() {
    Effacer();
    char choixmenu;
    getConsoleSize(&width,&height);
    int menuWidth = (int)(width * 0.4);
    int menuHeight = (int)(height * 0.4);
    int menuX = (width - menuWidth) / 2;
    int menuY = (height - menuHeight) / 2;
    int upper=menuHeight/3;
    int optionZone=2*menuHeight/3;
    
        rectangle(menuX,menuY-3,menuWidth,upper);
        rectangle(menuX,menuY+upper-2,menuWidth,optionZone);
       
       gotoxy(menuX+(menuWidth-4)/2,menuY+(upper/2)-3); printf("MENU");
       
       gotoxy(menuX+3,menuY+upper+optionZone*0.3-3);printf("[X] - Charger Partie");
       gotoxy(menuX+3,menuY+upper+optionZone*0.5-3);printf("[Y] - Nouvelle Partie");
       gotoxy(menuX+3,menuY+upper+optionZone*0.9-3);printf("[Q] - Quitter");
       rectangle(menuX,menuY+menuHeight-1,menuWidth,menuHeight*0.35);

       gotoxy((2+width-strlen("Choisissez une option valide et confirmez\n"))/2,(menuY+menuHeight+(upper)/2)-1);
       printf("Choisissez une option valide et confirmez\n");


     // Convertit en minuscule
     char validerChoix=0;
     
     do{
        gotoxy(width/2,(menuY+menuHeight+(upper)/2));
        choixmenu=getch();
        switch (choixmenu) {
            case 'X':{
                printf("X");
                do {
                    choixmenu=getch();
                    if(choixmenu=='\r'){
                        // Vérifier d'abord si une sauvegarde existe
                        if (verifSauvegarde()) {
                            chargerPartie(); // Charger la partie seulement si une sauvegarde existe
                            afficherReviewPartie(); // Afficher la review de la partie chargée
                            lancerJeu(); // Passer directement au tour suivant au lieu de revenir au menu
                        } else {
                            // Si aucune sauvegarde n'existe, afficher un message et revenir au menu
                            Effacer();
                            int largeurTermi = 0, hauteurTermi = 0;
                            getConsoleSize(&largeurTermi, &hauteurTermi);
                            
                            char message[] = "Aucune sauvegarde trouvee!";
                            EcritureDynamique(message, (largeurTermi-strlen(message))/2, hauteurTermi/2, 0);
                            Sleep(2000); // Attendre 2 secondes
                            afficherMenu(); // Revenir au menu
                        }
                        break;
                    }
                }while(choixmenu!='\b');
                if(choixmenu=='\b') 
                {
                    printf("\b \b");
                    choixmenu='\n';
                }
                break;
            }
            case 'Y':{
                printf("Y");
                do {
                    choixmenu=getch();
                    if(choixmenu=='\r'){
                        nouvellePartie();
                        break;
                    }
                }while(choixmenu!='\b');
                if(choixmenu=='\b') 
                {
                    printf("\b \b");
                    choixmenu='\n';
                }
                break;
            }
            case 'Q':{
                printf("Q");
                do {
                    choixmenu=getch();
                    if(choixmenu=='\r'){
                        exit(0);
                        break;
                    }
                }while(choixmenu!='\b');
                if(choixmenu=='\b') 
                {
                    printf("\b \b");
                    choixmenu='\n';
                }
                break;
            }
            default: choixmenu='\n';
            break;
        }
    }while(choixmenu=='\n');
                
        
        
    
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
            if( ch == '\b' ){
                if(i==0){
                   printf("");
                }
                else{
                    printf("\b \b") ;
                    i-- ;
                }
                    
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
            
                score1moveX = scorefieldX1 + ((scorefieldLong-Intlen(Joueur1.score[Partie.tourJoues]))/2);
                score1moveY = scorefieldY1 + (scorefieldHeight / 2);
            
                score2moveX = scorefieldX2 + ((scorefieldLong-Intlen(Joueur2.score[Partie.tourJoues]))/2);
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

    //----tailleEcran------
    



    //-----Interfaces-----
    void afficherInterface(){
        int i=0;
        for(i=0;i<15;i++){
            printf("\n\n");
        }
        initialiserVariables();
        // system("mode con: cols=170 lines=50");
        rectangle(scorefieldX1,scorefieldY1,scorefieldLong,scorefieldHeight);
        rectangle(mainframeX,mainframeY,mainframeLong,mainframeHeight);
        rectangle(scorefieldX2,scorefieldY2,scorefieldLong,scorefieldHeight);
        rectangle(gameEntryFieldX,gameEntryFieldY,gameEntryFieldLong,gameEntryFieldHeight);
        rectangle(EntryFieldX1, EntryFieldY1, EntryFieldLong, EntryFieldHeight);
        rectangle(EntryFieldX2, EntryFieldY2, EntryFieldLong, EntryFieldHeight);
        rectangle(AIX,AIY,EntryFieldLong,EntryFieldHeight);

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
          AIX=((2*EntryFieldX1+EntryFieldLong-strlen(word)) / 2);
         
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
        gotoxy(AIX,AIY+1);
    }
    //  redirige champ score joueur 1
    void player1Score(){
        gotoxy(score1moveX,score1moveY);
    }
    //  redirige champ score joueur 2
    void player2Score(){
        gotoxy(score2moveX,score2moveY);
    }
    //  redirige à la ligne de prompt du joueur qui commence
    void prompt(){
        gotoxy((frameX+((frameLong-70)/2)),frameY-2);
    }
    //  redirige champ d'entrée de jeu voyelle consonne
    void EntryField(){
        gotoxy(gambaseX,gamebaseY);
    }
    // redirige nom joueur 1
    void namePlay1(){
        gotoxy(1+(2*scorefieldX1+scorefieldLong-strlen(Joueur1.nom))/2,score1moveY-(score1moveY/3)-1);
    }
    // redirige nom joueur 2
    void namePlay2(){
        gotoxy(1+(2*scorefieldX2+scorefieldLong-strlen(Joueur2.nom))/2,score2moveY-(score2moveY/3)-1);
    }
    // Jouer

/**
 * Affiche un petit rectangle notification indiquant le passage au tour suivant
 * @param numeroTour Numéro du tour auquel on passe
 */
void afficherNotificationTour(int numeroTour) {
    int largeurTermi = 0, hauteurTermi = 0;
    
    // Récupérer les dimensions du terminal
    getConsoleSize(&largeurTermi, &hauteurTermi);
    
    // Définir les dimensions du rectangle de notification
    int notifWidth = 25;
    int notifHeight = 5;
    int notifX = (largeurTermi - notifWidth) / 2;
    int notifY = hauteurTermi * 0.1; // En haut de l'écran
    
    // Dessiner le rectangle pour la notification
    rectangle(notifX, notifY, notifWidth, notifHeight);
    
    // Afficher le message de notification
    char message[50];
    sprintf(message, "Passage au tour %d", numeroTour);
    
    gotoxy(notifX + (notifWidth - strlen(message)) / 2, notifY + 2);
    printf("%s", message);
    
    // Pas d'attente, car l'affichage doit être simultané avec la revue
}

/**
 * Affiche un résumé détaillé de la partie dans un rectangle centré à l'écran.
 * Utilise les informations de la partie chargée pour afficher les détails.
 */
void afficherReviewPartie() {
    // Effacer complètement l'écran avant d'afficher la revue
    Effacer();
    
    int largeurTermi = 0, hauteurTermi = 0;
    
    // Récupérer les dimensions du terminal
    getConsoleSize(&largeurTermi, &hauteurTermi);
    
    // Afficher la notification de passage au tour suivant
    afficherNotificationTour(Partie.tourJoues + 1);
    
    // Définir les dimensions du rectangle de revue
    int revueWidth = largeurTermi * 0.7;
    // Hauteur fixe pour la partie supérieure (titre et infos générales)
    int hauteurFixe = 12;
    // Hauteur de chaque tour (3 lignes par tour)
    int hauteurParTour = 3;
    // Hauteur supplémentaire pour le message de navigation
    int hauteurNav = 4;
    
    // Nombre de tours à afficher (derniers tours)
    int toursAffiches = 3; // On affiche les 3 derniers tours
    
    // Calculer la hauteur totale nécessaire
    int revueHeight = hauteurFixe + (toursAffiches * hauteurParTour) + hauteurNav;
    
    int revueX = (largeurTermi - revueWidth) / 2;
    int revueY = (hauteurTermi - revueHeight) / 2 + 3;
    
    // Dessiner le rectangle pour la revue
    rectangle(revueX, revueY, revueWidth, revueHeight);
    
    // Afficher le titre centré
    char titre[] = "RESUME DE LA PARTIE CHARGEE";
    gotoxy(revueX + (revueWidth - strlen(titre)) / 2, revueY + 2);
    printf("%s", titre);
    
    // Afficher les informations générales
    gotoxy(revueX + 4, revueY + 4);
    printf("Joueur 1: %s (Score: %d)", Joueur1.nom, Joueur1.scoreTotal);
    
    gotoxy(revueX + 4, revueY + 6);
    printf("Joueur 2: %s (Score: %d)", Joueur2.nom, Joueur2.scoreTotal);
    
    gotoxy(revueX + 4, revueY + 8);
    printf("Progression: %d tours joues sur %d", Partie.tourJoues, Partie.nbreTours);
    
    // Afficher l'historique des tours
    gotoxy(revueX + 4, revueY + 10);
    printf("Derniers tours joues:");
    
    // Calculer le point de départ pour l'affichage des tours
    int debutAffichage = (Partie.tourJoues > toursAffiches) ? Partie.tourJoues - toursAffiches : 0;
    
    // Afficher les tours
    int ligneY = revueY + 12;
    for (int i = debutAffichage; i < Partie.tourJoues; i++) {
        gotoxy(revueX + 8, ligneY);
        printf("Tour %d:", i + 1);
        
        gotoxy(revueX + 12, ligneY + 1);
        printf("%s - Mot: %s, Score: %d", Joueur1.nom, Joueur1.mot[i], Joueur1.score[i]);
        
        gotoxy(revueX + 12, ligneY + 2);
        printf("%s - Mot: %s, Score: %d", Joueur2.nom, Joueur2.mot[i], Joueur2.score[i]);
        
        ligneY += hauteurParTour;
    }
    
    // Afficher message pour continuer
    gotoxy(revueX + (revueWidth - strlen("Appuyez sur ENTREE pour continuer...")) / 2, revueY + revueHeight - 2);
    printf("Appuyez sur ENTREE pour continuer...");
    
    // Attendre l'entrée utilisateur
    char touche;
    do {
        touche = getch();
    } while (touche != 13); // Attendre la touche ENTRÉE
}

