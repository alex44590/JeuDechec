#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "commun.h"
#include "casePseudo.h"
#include "option.h"
#include "bouton.h"


#define NB_BOUTON_MP (STATISTIQUES+1)

/*Création de la structure MenuPrincipal*/
typedef struct{
	Bouton* boutonmp;
	Option optionmp;
	CasePseudo CasePseudomp
	
}MenuPrincipal;
/*terminaison par mp pour menu principal*/


#endif