#ifndef DE8B904D_F3C7_463B_993A_017D0850612E
#define DE8B904D_F3C7_463B_993A_017D0850612E


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
 * Efface le terminal au maximum et definit un alias pour raccouris les chemins de repertoires dérangeant
 */
void Effacer();


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
 * Verifie qu'un nombre initialement recupéré sous forme de chaine et bel et bien un nombre
 * @param string la chaine (nombre)
 * @return int 1 si la chaine est un nombre ou 0 sinon
 */
int isNumber(char *string);

// 
/**
 * @brief 
 * Compte le nombre de chiffres dans un entier
 * @param n 
 * @return int 
 */
int Intlen(int n);

/**
 * @brief 
 * Efface une zone à partir de coordonnées passés 
 * @param x 
 * @param y 
 * @param lon 
 * @param haut 
 */
void EffacerZone(int x, int y, int lon, int haut);
#endif /* DE8B904D_F3C7_463B_993A_017D0850612E */
