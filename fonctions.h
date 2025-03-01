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
extern char choixConsonneVoyelle;

// Déclaration des fonctions

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
 * Vérifie si un mot repond au caractère de la grille
 * @param mot 
 * @param grilleCaractere 
 * @return int 1 si le mot est valide et 0 sinon
 */
int validationChar(char mot[], char grilleCaractere[]);


/**
 * @brief 
 * Recherche le mot le plus long dans une grille
 * @param grille 
 * @return char* le plus long mot
 */
 char *LongestWord(char grille[]);

#endif