
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>



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
// Fonction qui compte le nombre de chiffres dans un entier
int Intlen(int n){
    int count=0;
    if (n == 0) {
        count = 1;
        return count;
    } else {
        // Compter les chiffres en divisant par 10
        while (n != 0) {
            n /= 10;
            count++;
        }
        return count;
    }
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

 void EffacerZone(int x, int y, int lon, int haut){
    gotoxy(x,y);
    for(int i=0;i<lon; i++){
        for(int j=0; j<haut;j++){
            printf(" ");
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