#pragma once

#include "arc.h"

typedef struct maillon {
	void *val;
	struct maillon *suiv;
} *Liste;

int est_vide_liste(Liste);
Liste ajouter_tete(void *, Liste, size_t);
Liste ajouter_queue(void *, Liste, size_t);
void afficher_liste(Liste);
void afficher_arc(Arc);
void afficher_sommet(Sommet);
Liste supprimer_tete(Liste);

int recherche_elt_liste(Liste, void *);
Liste ajout_tri(Sommet *, Liste);
