#pragma once

struct NoeudArbre;
struct arc;
struct cellule;

/* Sommet */
typedef struct {
	int numero;
	char* nom;
	float coordonnee_x;
	float coordonnee_y;
	struct cellule* voisins;

	struct arc* arrive_par; // pointeur vers le meilleur arc à connecté à l’ACM
	float PPC; // cout de l’arc arrive_par

	struct NoeudArbre* noeudArbreACM;

} Sommet;



/* Liste de Sommet */
typedef struct cellules {
	Sommet val;
	struct cellules * suiv;
}* ListeSommet;