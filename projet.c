#include <stdio.h>

#define LARGEUR  6
#define LONGUEUR 7

char grille[LARGEUR][LONGUEUR]; // déclaration et allocation du tableau

void initgrille() {
  for(int i = 0; i < LARGEUR; i++) {
    for(int j = 0; j < LONGUEUR; j++) {
      grille[i][j] = ' '; // caractère vide défini avec des guillemets simples
    }
  }
}


void affichegrille() {
  printf("+---+---+---+---+---+---+---+\n");
  for(int i = 0; i < LARGEUR; i++) {
    printf("|"); // affiche un séparateur de colonne au début de chaque ligne
    for(int j = 0; j < LONGUEUR; j++) {
      printf(" %c |", grille[i][j]); // affiche l'élément de la grille et un séparateur de colonne
    }
    printf("\n"); // passe à la ligne suivante

    // affiche un séparateur horizontal entre les lignes
    printf("+");
    for(int j = 0; j < LONGUEUR; j++) {
      printf("---+"); // affiche trois tirets entre chaque colonne
    }
    printf("\n"); // passe à la ligne suivante
  }
  printf("\n");
}

/*
  Vérifie si la case actuelle est valide
*/
int verifieSicaseValide(int a, int b) {
  if (grille[a][b] == ' ' && a < LARGEUR && b < LONGUEUR ) {
    return 1;
  }
  return 0;  
} 

int verifieSiUnJoueurAgagner(char player) {
  int i, j;
  
  // Vérifier les lignes
  for (i = 0; i < LARGEUR; i++) {
    for (j = 0; j < LONGUEUR - 3; j++) {
      if (grille[i][j] == player && grille[i][j+1] == player && grille[i][j+2] == player && grille[i][j+3] == player) {
        return 1;
      }
    }
  }

  // Vérifier les colonnes
  for (i = 0; i < LARGEUR - 3; i++) {
    for (j = 0; j < LONGUEUR; j++) {
      if (grille[i][j] == player && grille[i+1][j] == player && grille[i+2][j] == player && grille[i+3][j] == player) {
        return 1;
      }
    }
  }

  // Vérifier les diagonales (vers le bas à droite)
  for (i = 0; i < LARGEUR - 3; i++) {
    for (j = 0; j < LONGUEUR - 3; j++) {
      if (grille[i][j] == player && grille[i+1][j+1] == player && grille[i+2][j+2] == player && grille[i+3][j+3] == player) {
        return 1;
      }
    }
  }

  // Vérifier les diagonales (vers le bas à gauche)
  for (i = 0; i < LARGEUR - 3; i++) {
    for (j = 3; j < LONGUEUR; j++) {
      if (grille[i][j] == player && grille[i+1][j-1] == player && grille[i+2][j-2] == player && grille[i+3][j-3] == player) {
        return 1;
      }
    }
  }

  // S'il n'y a pas de combinaison gagnante, retourner 0
  return 0;
}

/*
  Vérifie s'il existe une case valide
*/
int verifieSiExisteCaseValide() {
  for (int i = 0; i < LARGEUR; i++) {
    for(int j = 0; j<LONGUEUR;j++) {
      if (verifieSicaseValide(i,j) == 1) {
        return 1;
      }
      
    }
  }
  return 0;
}

void programmePrincipale() {
  initgrille();
  affichegrille();
  char joueur, ordinateur;
  int numeroCase, colonne,a,b;
  
  /*
    le joueur choisit sa couleur
  */

    do {
        printf("Choisissez une couleur:\n\nB->Blanc\nN->Noir\n");
        scanf(" %c", &joueur);
        if (joueur != 'B' && joueur != 'N') {
          printf("\n\n\033[1;31mVous ne pouvez que selectionner N ou B. Réessayez.\033[0m\n\n");
        } 
    } while (joueur != 'B' && joueur != 'N');


  
  /*
    affiche au joueur la couleur et le symbole représentant la symbole choisi de joueur.
  */
  if (joueur == 'B') {
    printf("\n\n\033[34mVous avez choisi la couleur blanche. Vos cases jouaient seront représentées par la symbole B.\033[0m\n\n");
    ordinateur = 'N';
  }else{
    printf("\n\n\033[34mVous avez choisi la couleur noire. Vos cases jouaient seront représentées par le symbole N.\033[0m\n\n");
    ordinateur = 'B';
  }
  
  /*
    le joueur joue et l'ordinateur également
  */

  while (verifieSiExisteCaseValide() == 1 && (verifieSiUnJoueurAgagner(joueur) == 0 && verifieSiUnJoueurAgagner(ordinateur) == 0)) {
    //le joueur joueN
    do{
      printf("Choisissez une case : ");
      scanf(" %d", &numeroCase);

      printf("Choisissez une colonne : ");
      scanf(" %d", &colonne);

      if (verifieSicaseValide(numeroCase-1, colonne-1) == 0 || numeroCase<1 || colonne < 1) {
        printf("\n\n\033[1;31mMerci de selectionner une case valide.\033[0m\n\n");
      }

    }while (verifieSicaseValide(numeroCase-1, colonne-1) == 0 || numeroCase<1 || colonne < 1);

    grille[numeroCase-1][colonne-1] = joueur;
    affichegrille();
    

    /*
    jeu de l'odinateur
   */
    do {
      a = rand() % LARGEUR;
      b = rand() % LONGUEUR;
    } while (verifieSicaseValide(a, b) == 0);
    grille[a][b] = ordinateur;
    printf("\n\n\033[34mL'ordinateur a joué en (%d, %d)\033[0m\n\n", a+1, b+1);
    affichegrille();   
  }   
  if (verifieSiUnJoueurAgagner(joueur) == 1) {
    printf("\n\n\033[34mFélicitation. Vous avez gagné.\033[0m\n\n");
  }

 if (verifieSiUnJoueurAgagner(ordinateur) == 1) {
    printf("\n\n\033[34mVous avez malheureusement perdu.\033[0m\n\n");
  }
  
}

int main() {
  programmePrincipale();
  return 0;
}