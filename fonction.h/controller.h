#ifndef AD958C8B_DA37_4398_8D2B_15FDCBF9A9D1
#define AD958C8B_DA37_4398_8D2B_15FDCBF9A9D1

#define MAX_TOURS 50

extern const int nbreJoueur;        // Nombre de joueurs dans la partie (fixé à 2)
extern const int nbreTotalLettresGrille;  // Nombre total de lettres dans la grille de jeu (9 lettres)
extern const char voyelles[6];      // Tableau contenant toutes les voyelles disponibles pour le jeu
extern const char consonnes[20];    // Tableau contenant toutes les consonnes disponibles pour le jeu

typedef struct Joueur{
    char nom[15];
    char mot[MAX_TOURS][10]; // Définition des tableaux pour l'historique des mots 
    int score[MAX_TOURS];   // Définition des tableaux pour l'historique des scores
    int scoreTotal;
  }Joueur;
  
  //Représentative d'un Jeu car le champs nbresTours y est present mais ne sera modifié qu'une fois soit lorsquon demande les infos sur la nouvelle partie
  typedef struct PartieJ{
    char lettreGenerees[10];
    int nbreTours;
    int tourJoues;
    int numJoueurCommencer;
  }PartieJ;

extern PartieJ Partie;
extern Joueur Joueur1;
extern Joueur Joueur2;


// Déclaration des fonctions

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
 * Recherche le mot le plus long dans une grille
 * @param grille 
 * @return char* le plus long mot
 */
char *LongestWord(char grille[]);

/**
 * @brief 
 *  Vérifie si un mot se retrouve dans le dictionnaire. Si oui, il renvoie la taille du mot (correspondant au score du joueur) si non il renvoie 0 pour indiquer que le mot n'existe pas dans le dictionnaire
 * @param mot 
 * @return int 
 */
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
 * @brief 
 * Initialise les variables pour démarrer un jeu 
 * Affiche une message d'alerte s'il y'a une sauvegarde en cours qui sera écrasée si les joueurs lancent confirmeleur choix
 * Sinon on retourne au menu
 */
void nouvellePartie();


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
 * Verifier si un caractère a deja été utilisé lors de la recherche dans le dictionnaire
 * pour éviter les doubles parcours pour un même caractère
 * @param tab chaine des caractères restants
 * @param c le caractère 
 * @return 1 si le caractère est dans la chaine (soit il est non utilisé) et 0 sinon
 */
int notUsed(char tab[], char c);


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


#endif /* AD958C8B_DA37_4398_8D2B_15FDCBF9A9D1 */
