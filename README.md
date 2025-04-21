# 🕹️ Longest Word Game

## 📖 Description

**Longest Word Game** est un jeu interactif où les joueurs concourent pour créer le mot valide le plus long à partir d'une grille de lettres générées aléatoirement.

## 💡 Fonctionnalités Principales

- **Système de jeu multijoueur** : Jusqu'à deux joueurs peuvent s'affronter pour obtenir le score le plus élevé.
- **Modes de jeu** :
  - Mode multijoueur.
  - Mode solo contre une intelligence artificielle (IA) avec différents niveaux de difficulté.
- **Validation des mots** :
  - Vérification des mots par rapport à une grille de lettres.
  - Validation dans un dictionnaire intégré.
- **Gestion des parties** :
  - Sauvegarde et chargement des parties en cours.
  - Historique des scores et des mots joués.
- **Interface utilisateur** :
  - Affichage dynamique avec menus interactifs.
  - Support pour des tailles d'écran variables.
- **Outils complémentaires** :
  - Organisation automatique du dictionnaire.
  - Suppression des caractères redondants dans les mots.

## 🏗️ Architecture du Code

Le projet suit une architecture modulaire avec les composants suivants :

### Fichiers Sources
1. **`main.c`** : Point d'entrée principal pour exécuter le jeu.
2. **`controller.c`** : Gestion des règles et des flux du jeu.
3. **`view.c`** : Affichage graphique et interactions utilisateur.
4. **`utilitaire.c`** : Fonctions utilitaires pour la manipulation de chaînes et d'autres fonctionnalités.

### Fichiers d'En-têtes
1. **`controller.h`** : Définitions des structures comme `Joueur` et fonctions de gestion.
2. **`view.h`** : Déclarations pour le rendu graphique et les menus.
3. **`utilitaire.h`** : Fonctions utilitaires (e.g., nettoyage de terminal, validation de chaînes).

## 🛠️ Compilation et Exécution

### Prérequis
- Un compilateur C (e.g., [GCC](https://gcc.gnu.org/)).
- Système d'exploitation Windows (pour les fonctions spécifiques à la console).

### Instructions
1. Clonez le dépôt :
   ```bash
   git clone https://github.com/mouwaficbdr/longest-word-game.git
   cd longest-word-game
   ```
2. Compilez le projet :
   ```bash
   gcc -o longest-word-game main.c fonction.c/*.c -I fonction.h
   ```
3. Lancez le jeu :
   ```bash
   ./longest-word-game
   ```

## 📜 Règles du Jeu

1. Deux joueurs entrent leurs noms et définissent qui commence.  
2. Ils choisissent à tour de rôle s’ils veulent ajouter une **consonne (C)** ou une **voyelle (V)**.  
3. Une lettre aléatoire du type demandé est ajoutée à la grille (jusqu'à 9 lettres).  
4. Chaque joueur propose secrètement un mot utilisant ces lettres.
5. Le mot sera validé selon sa présence dans le dictionnaire et sa conformité avec la grille.  
6. Le système attribue un score basé sur la longueur du mot valide.  
7. Le jeu continue pendant le nombre de tours définis au départ.  
8. Le joueur avec le score le plus élevé à la fin des tours gagne !

## 🤝 Contributeurs

- [**AIHOUNHIN Eunock**](https://github.com/Eunock-web)  
- [**ATOHOUN Andy**](https://github.com/e-mandy)  
- [**BADAROU Mouwafic**](https://github.com/mouwaficbdr)
- [**OGOUDEDJI Seathiel**](https://github.com/seathiel-12)  
- [**OKWUDIAFOR Wesley**](https://github.com/wesley-kami)  

## 📂 Structure des Dossiers

```
.
├── fonction.c/
│   ├── controller.c
│   ├── view.c
│   ├── utilitaire.c
├── fonction.h/
│   ├── controller.h
│   ├── view.h
│   ├── utilitaire.h
├── main.c
└── README.md
```

## 🔧 Améliorations Futures

- Ajout d'un mode réseau pour jouer en ligne.
- Support multilingue (e.g., dictionnaires dans d'autres langues).
