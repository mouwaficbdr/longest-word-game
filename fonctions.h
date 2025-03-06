#ifndef FONCTIONS_H
#define FONCTIONS_H

// Définition du nombre maximum de tours possibles
#define MAX_TOURS 50

// Dclaration des constantes
extern const int nbreJoueur;        // Nombre de joueurs dans la partie (fixé à 2)
extern const int nbreTotalLettresGrille;  // Nombre total de lettres dans la grille de jeu (9 lettres)
extern const char voyelles[6];      // Tableau contenant toutes les voyelles disponibles pour le jeu
extern const char consonnes[20];    // Tableau contenant toutes les consonnes disponibles pour le jeu

// Déclaration des variables
extern char nomJoueur1[10];         // Nom du premier joueur (limité à 9 caractères + terminateur)
extern char nomJoueur2[10];         // Nom du deuxième joueur (limité à 9 caractères + terminateur)
extern int numJoueurCommencerPartie; // Numéro du joueur qui commence la partie (1 ou 2)
extern int nbreTours;               // Nombre total de tours pour la partie complète

// Variables globales supplémentaires pour l'état du jeu
extern int scoreJoueur1;            // Score actuel du premier joueur
extern int scoreJoueur2;            // Score actuel du deuxième joueur
extern int toursJoues;              // Nombre de tours déjà joués

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


// Tableaux pour l'historique des mots et scores
extern char motsJoueur1[MAX_TOURS][20];  // Historique des mots joués par le joueur 1 
extern char motsJoueur2[MAX_TOURS][20];  // Historique des mots joués par le joueur 2
extern int scoresJoueur1[MAX_TOURS];     // Historique des scores du joueur 1
extern int scoresJoueur2[MAX_TOURS];     // Historique des scores du joueur 2

//Déclaration des structures

// Dclaration des fonctions

/**
 * @param mot 
 * @param grilleCaractere 
 * Vérifie si le mot de l'utilisateur respecte les caractères de la grille
 * Si oui, elle renvoit la valeur 1 
 * Sinon, elle renvoit la valeur 0
 */
int validationChar(char mot[], char grilleCaractere[]);

/**
 * @brief 
 * Ranger le dictionnaire suivant les lettres de l'alphabet 
 */
void RangerDico();


  /**
 * @brief 
 * Supprimer toutes les occurences d'un caractère dans une chaine
 * @param chaine *chaine
 * @param c le caractère
 */
void removeSameChar(char *chaine, char c);


/**
 * @brief 
 * Verifier si un caractère a deja été utilisé lors de la recherche dans le dictionnaire
 * pour éviter les doubles parcours pour un même caractère
 * @param tab chaine des caractères restants
 * @param c le caractère 
 * @return 1 si le caractère est dans la chaine (soit il est non utilisé) et 0 sinon
 */
int notUsed(char tab[], char c);


/**
 * @brief 
 * Recherche le mot le plus long dans une grille
 * @param grille 
 * @return char* le plus long mot
 */
 char *LongestWord(char grille[]);

//La fonction validationMots vérifie si un mot se retrouve dans le dictionnaire. Si oui, il renvoie la taille du mot (correspondant au score du joueur) si non il renvoie 0 pour indiquer que le mot n'existe pas dans le dictionnaire
int validationMots(char mot[]);

/**
 * Sauvegarde l'état actuel de la partie dans un fichier texte (sauvegarde.txt).
 * Utilise les variables globales pour les informations de la partie (noms, scores, tours).
 * La grille n'est pas sauvegardée car elle sera régénérée à la reprise de la partie.
 * Inclut l'historique des mots joués et leurs scores pour chaque joueur.
 */
void sauvegarderPartie(void);

/**
 * Charge une partie précédemment sauvegardée à partir du fichier sauvegarde.txt.
 * Les données sont chargées directement dans les variables globales définies.
 * La grille n'est pas chargée car elle sera régénérée à la reprise de la partie.
 * 
 * @return 1 si le chargement a réussi, 0 en cas d'échec
 */
int chargerPartie(void);

/**
 * Affiche un résumé détaillé de la partie sauvegardée.
 * Montre les informations de base de la partie (noms, scores, progression) 
 * et l'historique des coups joués tour par tour.
 * La grille n'est pas affichée car elle n'est pas sauvegardée.
 */
void reviewPartie();

/**
 * Vérifie si une sauvegarde existe déjà dans le fichier sauvegarde.txt.
 * 
 * @return 1 si une sauvegarde existe et est valide, 0 sinon
 */
int verifSauvegarde(void);

/**
 * Efface le fichier de sauvegarde s'il existe.
 * Cette fonction permet de supprimer une sauvegarde existante
 * avant de commencer une nouvelle partie.
 * 
 * @return 1 si la sauvegarde a été effacée avec succès ou n'existait pas, 0 en cas d'échec
 */
int effacerSauvegarde(void);

/**
 * Enregistre les mots et scores d'un tour dans l'historique.
 * Met à jour les tableaux globaux motsJoueur1, motsJoueur2, scoresJoueur1, scoresJoueur2.
 * Incrémente également le compteur de tours joués (toursJoues) et met à jour les scores totaux.
 * 
 * @param motJoueur1 Le mot proposé par le joueur 1 pour ce tour
 * @param motJoueur2 Le mot proposé par le joueur 2 pour ce tour
 * @param scoreMotJoueur1 Le score obtenu par le joueur 1 pour ce mot
 * @param scoreMotJoueur2 Le score obtenu par le joueur 2 pour ce mot
 * @return 1 si l'enregistrement a réussi, 0 si le nombre maximum de tours est atteint
 */
int enregistrerTour(const char motJoueur1[], const char motJoueur2[], int scoreMotJoueur1, int scoreMotJoueur2);

/**
 * Récupère les variables nécessaire et démarre une nouvelle partie ou charge une partie sauvegardée
 * @param Joueur1 
 * @param Joueur2 
 * @param tourActuel 
 * @param totalTours 
 * @param numCommencer 
 */
void DemarrerPartie(char Joueur1[], char Joueur2[], int tourActuel, int totalTours, int numCommencer);


/**
 * @brief 
 * Efface le terminal au maximum et definit un alias pour raccouris les chemins de repertoires dérangeant
 */
void Effacer();


/**
 * @brief 
 * Verifie qu'un nombre initialement recupéré sous forme de chaine et bel et bien un nombre
 * @param string la chaine (nombre)
 * @return int 1 si la chaine est un nombre ou 0 sinon
 */
int isNumber(char *string);


/**
 * @brief 
 * Initialise les variables pour démarrer un jeu 
 * Affiche une message d'alerte s'il y'a une sauvegarde en cours qui sera écrasée si les joueurs lancent confirmeleur choix
 * Sinon on retourne au menu
 */
void nouvellePartie();


/**
 * @brief 
 * Affiche le menu pour choisir une option nouvelle partie ou charger une partie ou encore quitter le jeu
 */
void afficherMenu();

/**
 * @brief 
 * Ecrire progressivement un texte à une position et une vitesse(appartition des caractères par au nombre de ms définit) donné
 * @param texte 
 * @param x 
 * @param y 
 * @param vitesse 
 */
void EcritureDynamique(char texte[], int x, int y,int vitesse);


/**
 * @brief 
 * Affiche un message à la fin d'une partie pour vérifier si les joueurs decident de continuer à jouer ou non 
 */
int JouerEncore();


/**
 * @brief 
 * Fonction principale qui lance le jeu
 */
void lancerJeu();


/**
 * @brief 
 * Efface une ligne en cas de saisie erronée
 */
void clearLine();

extern void getConsoleSize(int *width, int *height) ;

extern void rectangle(int x, int y, int lon, int haut);

//Fonction pour generer les caracteres aleatoire et donc le mot a 9 lettres
extern void genererCaractereAleatoires(int);

//Fonction pour afficher le menu du jeux 
extern void afficherMenu();

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
extern void setConsoleSize(int width, int height);
extern void namePlay1();
extern void namePlay2();
extern void prompt();
// Nouvelles fonctions pour améliorer la structure du code
extern void initialiserInterface();
extern void demanderMotJoueur1(char *mot);
extern void demanderMotJoueur2(char *mot);


#endif
