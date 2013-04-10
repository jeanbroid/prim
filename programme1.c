#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"
#include "utils.h"

File algo_fileACM(void) {
	// ListeSommet C;

	Liste C;

	File fileACM;
	Sommet d; // Sommet de départ

	Liste liste_sommet; // liste de tous les sommets du fichier
	Liste liste_arc; // liste de tous les arcs du fichier

	// DEBUT ALGO

	Liste p;
	for(p=liste_sommet; !est_vide_liste(p); p=p->suiv) {
		(*(Sommet*) p->val).PPC = FLT_MAX; 	//mettre un coût infini
		(*(Sommet*) p->val).arrive_par = NULL;
	}

	d.PPC = 0;
	d.arrive_par = NULL;
	fileACM = creer_file();
	C = ajouter_queue(&d, C, sizeof(Sommet));

	while( !est_vide_file(fileACM) ) {

		/* POUR TOUTES LES FONCTIONS QUI SUIVENT FAUDRA LES ECRIRE DANS UN FICHIER
		 POUR UN CODE PLUS EXPLICITE */

		// sommet j de C de plus petit PPC;
		Sommet sommet_ppc_min;
		sommet_ppc_min = trouver_min_liste_sommet(C);
		float min = sommet_ppc_min.PPC;
		// on récupère le sommet de plus petit PPC et son coût

		// supprimer j de C;
		if ( (*(Sommet*) C->val).PPC == min) {
			// cas si j premier élément de C
			C = C->suiv;
		} 
		else {
			for (p=C; !est_vide_liste((Liste) p); p=p->suiv) {
				if ( (*(Sommet*) p->suiv->val).PPC == min ) {
					// on a trouvé j
					// il faut maintenant le supprimer de la liste

					// cas général
					// a voir si bug dans cas particuliers
					Liste tmp;
					tmp = p->suiv->suiv;
					free_liste(p->suiv);
					p->suiv = tmp;
				}
			}
		}

		// si j n'est pas dans d;
		if (recherche_elt_liste(C, &sommet_ppc_min) != 1) {
			fileACM = enfiler(fileACM, &sommet_ppc_min.arrive_par, sizeof(Arc));
		}

		// il faut maintenant récupérer les adjacents à j

		Liste liste_sommet_adjacent;
		Liste q;

		for (q=liste_arc; !est_vide_liste(liste_arc); q=q->suiv) {

			/* on a le droit au memcmp ici: il faut passé par calloc+memset, soit malloc
			 ici on regarde a gauche et a droite de l'arc car on a juste les arcs dans un 
			 seul sens pour le moment, il faudrait peut être les doubler lors de la lecture */

			if ( memcmp((*(Arc*) q->val).sommet_depart, &sommet_ppc_min ) == 1 ){
				liste_sommet_adjacent = ajouter_queue((*(Arc*) q->val).sommet_depart, liste_sommet_adjacent, sizeof(Sommet));
			} 
			else if ( memcmp((*(Arc*) q->val).sommet_arrive, &sommet_ppc_min ) == 1) {
				liste_sommet_adjacent = ajouter_queue((*(Arc*) q->val).sommet_arrive, liste_sommet_adjacent, sizeof(Sommet));
			}
		}

		// sommet_ppc_min.voisins = liste_sommet_adjacent;


		// ListeSommet p

		for (p=liste_sommet_adjacent; !est_vide_liste( p); p=p->suiv) {
			if ( (*(Sommet*) p->val).PPC > min ) {

				(*(Sommet*) p->val).PPC = min;

				/* il faut maintenant mettre l'arc j=>k dans arrive_par */

				Arc arc;
				arc.cout = (*(Sommet*) p->val).PPC;
				arc.sommet_depart = &sommet_ppc_min;
				arc.sommet_arrive = (Sommet*) p->val;

				(*(Sommet*) p->val).arrive_par = &arc;

				if (recherche_elt_liste(C, (Sommet*) p->val)) {
					C = ajouter_queue((Sommet*) p->val, C, sizeof(Sommet));
				}
				else {
					printf("nothing now \n");
				}

			}
		}
	}

	return fileACM;
	// FIN ALGO
}

int main(int argc, char* argv[]) {

	File fileACM;
	fileACM = algo_fileACM();	

	return 0;
}