#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

#include "utils.h"


FileArc algo_fileACM(void) {
	ListeSommet C;
	FileArc fileACM;
	Sommet d; // Sommet de départ

	ListeSommet liste_sommet; //liste de tous les sommets du fichier

	// DEBUT ALGO

	ListeSommet p;
	for(p=liste_sommet; !est_vide_liste((Liste) p); p=p->suiv) {
		(p->sommet).PPC = FLT_MAX; 	//mettre un coût infini
		(p->sommet).arrive_par = NULL;
	}

	d.PPC = 0;
	d.arrive_par = NULL;
	fileACM = (FileArc) creer_liste();
	C = (ListeSommet) ajouter_queue(&d, (Liste) C, sizeof(Sommet));

	while( !est_vide_file((File) fileACM) ) {


		/* POUR TOUTES LES FONCTIONS QUI SUIVENT FAUDRA LES ECRIRE DANS UN FICHIER
		 POUR UN CODE PLUS EXPLICITE */

		// sommet j de C de plus petit PPC;
		Sommet sommet_ppc_min;
		sommet_ppc_min = trouver_min_liste_sommet(C);
		float min = sommet_ppc_min.PPC;
		

		// supprimer j de C;
		if ( C->sommet.PPC == min) {
			// cas si j premier élément de C
			C = C->suiv;
		} 
		else {
			for (p=C; !est_vide_liste((Liste) p); p=p->suiv) {
				if ( (p->suiv->sommet).PPC == min ) {
					// on a trouvé j
					// il faut maintenant le supprimer de la liste

					// cas général
					// a voir si bug dans cas particuliers
					ListeSommet tmp;
					tmp = p->suiv->suiv;
					free_liste((Liste) p->suiv);
					p->suiv = tmp;
				}
			}
		}

		// si j n'est pas dans d;
		if (recherche_elt_liste((Liste) C, &sommet_ppc_min) != 1) {
			fileACM = (FileArc) enfiler((File) fileACM, &sommet_ppc_min.arrive_par, sizeof(Arc));
		}


		// SUITE ALGO ...

	}

	return fileACM;
	// FIN ALGO
}


int main(int argc, char* argv[]) {

	FileArc fileACM;
	fileACM = algo_fileACM();	

	return 0;
}