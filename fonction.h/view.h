#ifndef D1FDB7D8_23C6_4483_BE99_D3F93C17C3A4
#define D1FDB7D8_23C6_4483_BE99_D3F93C17C3A4

extern int scorefieldX1, scorefieldY1, scorefieldLong, scorefieldHeight;
extern int scorefieldCursorX1, scorefieldCursorY1;
extern int mainframeX, mainframeY, mainframeLong, mainframeHeight;
extern int scorefieldX2, scorefieldY2;
extern int gameEntryFieldX, gameEntryFieldY, gameEntryFieldHeight, gameEntryFieldLong;
extern int EntryFieldX1, EntryFieldY1, EntryFieldLong, EntryFieldHeight;
extern int EntryFieldX2, EntryFieldY2;
extern int AIX, AIY;
extern int play1CursorX, play1CursorY;
extern int play2CursorX, play2CursorY;
extern int AImoveX, AImoveY;
extern int score1moveX, score1moveY;
extern int score2moveX, score2moveY;
extern int gambaseX, gamebaseY;
extern int height,width;
extern int frameX, frameY, frameLong, frameHeight;



/**
 * @brief 
 * Efface une ligne en cas de saisie erronée
 */
void clearLine();

/**
 * @brief 
 * Récupère les dimensions du terminal dans le contenu des pointeurs passés en paramètre
 * @param width 
 * @param height 
 */
extern void getConsoleSize(int *width, int *height) ;

/**
 * @brief 
 * Desinner un rectangle aux coordonnées et dimensions passés en paramètre
 * @param x 
 * @param y 
 * @param lon 
 * @param haut 
 */
extern void rectangle(int x, int y, int lon, int haut);


/**
 * @brief 
 * Affiche le menu pour choisir une option nouvelle partie ou charger une partie ou encore quitter le jeu
 */
extern void afficherMenu();

/**
 * @brief 
 * Affiche la revue détaillée d'une partie en cours ou chargée
 */
extern void afficherReviewPartie(void);



extern void hashWord(char*word, int size);
extern void gotoxy(int x, int y);
extern void rectangle(int x, int y, int lon, int haut);
extern void afficherInterface();
extern void initialiserVariables();
extern void player1();
extern void player2();
extern void AImove();
extern void player1Score();
extern void player2Score();
extern void EntryField();
extern void centeredhash1(char *word, int size);
extern void centeredhash2(char *word, int size);
extern void centerword1(char *word);
extern void centerword2(char *word);
extern void centerwordAI(char *word);
extern void getConsoleSize(int *width, int *height);
extern void namePlay1();
extern void namePlay2();
extern void prompt();

#endif /* D1FDB7D8_23C6_4483_BE99_D3F93C17C3A4 */
