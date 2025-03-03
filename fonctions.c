#include <conio.h>
#include <stdio.h>
#include <windows.h> 
#include <ctype.h>
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
int toursJoues;
char choixConsonneVoyelle;
int ScoreJoueur1;
int ScoreJoeur2;

// Définition des fonctions

void tailleTerminal(int *largeur, int *hauteur){
    CONSOLE_SCREEN_BUFFER_INFO terminal;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &terminal);
    *largeur= terminal.srWindow.Right - terminal.srWindow.Left +1;
    *hauteur= terminal.srWindow.Bottom - terminal.srWindow.Top +1;
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
                    return 1;
                }else if(validation=='\b'){
                    gotoxy((largeurTermi/2),(hauteurTermi/2)+2);
                    printf(" "); 
                    gotoxy((largeurTermi/2),(hauteurTermi/2)+2);
                    choix='\n';
                    break;
                }else{
                    printf("\b \b");
                    gotoxy((largeurTermi/2),(hauteurTermi/2)+2);
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
        ScoreJoueur1=0; 
        ScoreJoeur2=0;

        DemarrerJeu(nomJoueur1,nomJoueur2,1,nbreTours,numJoueurCommencerPartie);
    }else{
        menu();
    }
}


void DemarrerJeu(char Joueur1[], char Joueur2[], int tourActuel, int totalTours, int numCommencer)
    {
    //On lance les fonctions interfaces et autres 

    }


void menu(){
 
        //Eunock

    //Affichage des zones de menu avec le switch sur les touches du clavier pour choisir
    // NouvellePartie() ou ChargerPartie() et lancer la fonction correspondante 
    //Option Quitter stopper le programme
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

    menu();

       while(toursJoues<nbreTours){
            if(JouerEncore()){
                do{
                    printf("Qui désire entamer la partie: Joueur 1 [1] ou Joueur 2 [2]\n");
                    scanf("%d",&numJoueurCommencerPartie);
                }while(numJoueurCommencerPartie!=1 && numJoueurCommencerPartie!=2); 

        DemarrerJeu(nomJoueur1,  nomJoueur2, toursJoues+1,nbreTours,numJoueurCommencerPartie);
            }else{
                menu();
            }
       }

    Effacer();
}

int verifSauvegarde(){
    //Mouwafic
}

void effacerSauvegarde(){
    //Mouwafic
}