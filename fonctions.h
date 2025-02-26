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

//Declaration des structures

/** 
 * @brief
 * motPossible
 * @champ {char *} le mot généré par l'anagramme
 * @champ {motPossible **} le pointeur vers le tabelau des fils du 
 * généré a partir du mot précédent
 */
typedef struct motPossible {
    char *mot;
    struct motPossible **suivant;
    } motPossible;
  
/**
 * @brief 
 * Possibilites 
 * Liste chainée des mots possibles
 * @champ {motPossible *} tableau e pointeur vers les premiers lettres soit les lettres générées
 */
    typedef struct Possibilites{
     motPossible *premier[9];
    }Possibilites;

    
// Déclaration des fonctions


/**
 * @brief 
 * Supprimer un caractère d'une chaine 
 * Pour supprimer les caractères déja utilisés par le noeud parent afin de produire un mot unique dans la génération suivante
 * @param str la chaine 
 * @param c le caractère a supprimer
 * @return char* 
 */
char *removeChar(char *str, char c);

/**
 * @brief 
 * Générer les anagrammes uniques possibles d'un noeud 
 * @param Noeud Le noeud à considérer pour génerer ses fils 
 * @param taille taille du tableau de lettres de la génération des noeuds à créer
 * @param tableau tableau des lettres générées par les joueurs
 * @return motPossible* le tableau des mots générés
 */
motPossible *Anagramme_(motPossible *Noeud, int taille, char tableau[]);

/**
 * @brief 
 * Générer entièrement l'arbre en partant d'une racine jusqu'à sa base
 * @param Noeud L'un des noeuds initial de l'arbre (de la 1ère génération)
 * @param tailleGen taille du tableau de lettres de la génération à créer
 * @param chaine le tableau des lettres générées par les joueurs
 */
void CreationArbre(motPossible *Noeud,int tailleGen, char* chaine);
#endif