#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include "../fonction.h/view.h"
#include "../fonction.h/utilitaire.h"
#include "../fonction.h/controller.h"


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
                        chargerPartie();
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
