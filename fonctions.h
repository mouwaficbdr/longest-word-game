#ifndef FONCTIONS_H
#define FONCTIONS_H

// Déclaration des constantes
extern const int nbreJoueur;
extern const int nbreTotalLettresGrille;
extern const char voyelles[6];
extern const char consonnes[20];

// Déclaration des variables
extern char nomJoueur1[10];
extern char nomJoueur2[10];
extern int numJoueurCommencerPartie;
extern int nbreTours;
extern int toursJoues;
extern char choixConsonneVoyelle;

// Déclaration des fonctions


void gotoxy(int x, int y);


/**
 * @brief 
 * Définit les dimensions du terminal 
 * @param largeur 
 * @param hauteur 
 */
void tailleTerminal(int *largeur, int *hauteur);


/**
 * @brief 
 * Récupère les variables nécessaire et démarre une nouvelle partie ou charge une partie sauvegardée
 * @param Joueur1 
 * @param Joueur2 
 * @param tourActuel 
 * @param totalTours 
 * @param numCommencer 
 */
void DemarrerJeu(char Joueur1[], char Joueur2[], int tourActuel, int totalTours, int numCommencer);


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
void NouvellePartie();


/**
 * @brief 
 * Affiche le menu pour choisir une option nouvelle partie ou charger une partie ou encore quitter le jeu
 */
void menu();

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
 * Verifie si une sauvegarde d'un jeu est faite
 * @return int 1 si oui 0 sinon
 */
int verifSauvegarde();

/**
 * @brief 
 * Efface la sauvegarde si les joueurs confirment
 */
void effacerSauvegarde();


/**
 * @brief 
 * Efface une ligne en cas de saisie erronée
 */
void clearLine();

#endif