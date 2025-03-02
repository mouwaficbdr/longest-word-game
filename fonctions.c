#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
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
char choixConsonneVoyelle;
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
// Définition des fonctions

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
                // Initialisation des dimensions et positions
                scorefieldX1 = 12;
                scorefieldY1 = 5;
                scorefieldLong = 12;
                scorefieldHeight = 4;
            
                scorefieldCursorX1 = scorefieldX1 + (scorefieldLong / 2);
                scorefieldCursorY1 = scorefieldY1 + (scorefieldHeight / 2);
            
                mainframeX = scorefieldX1 + scorefieldLong + 3;
                mainframeY = scorefieldY1 - 3;
                mainframeLong = scorefieldLong * 5;
                mainframeHeight = scorefieldHeight * 6;
            
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
                EntryFieldY2 = EntryFieldY1 + 3;
            
                AIX = EntryFieldX1;
                AIY = EntryFieldY2 + 3;
            
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
            
                gambaseX = gameEntryFieldX + (gameEntryFieldLong / 3);
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

    void player1(){
        gotoxy(play1CursorX,play1CursorY);
    }
    void player2(){
        gotoxy(play2CursorX,play2CursorY);
    }
    void AImove(){
        gotoxy(AImoveX,AImoveY);
    }
    void player1Score(){
        gotoxy(score1moveX,score1moveY);
    }
    void player2Score(){
        gotoxy(score2moveX,score2moveY);
    }
    void EntryField(){
        gotoxy(gambaseX,gamebaseY);
    }
    // Jouer
