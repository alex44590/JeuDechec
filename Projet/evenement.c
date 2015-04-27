#include "evenement.h"

void mettreAJourEvent(Input* in){
	in->sourisRelachee = FALSE;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		//Gestion du clavier
		case SDL_KEYDOWN:
			if (event.key.keysym.sym <= 127)
				in->clavier[event.key.keysym.sym] = 1;
			else if (KEYCODE_REDUIT(event.key.keysym.sym) > 128 && KEYCODE_REDUIT(event.key.keysym.sym) <= 353)
				in->clavier[KEYCODE_REDUIT(event.key.keysym.sym)] = 1;
			else if (KEYCODE_REDUIT(event.key.keysym.sym) == 128) // Cas de la touche VerrouillerMajuscule (CAPSLOCK)
				in->clavier[KEYCODE_REDUIT(event.key.keysym.sym)] = !in->clavier[KEYCODE_REDUIT(event.key.keysym.sym)];
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym <= 127)
				in->clavier[event.key.keysym.sym] = 0;
			else if (KEYCODE_REDUIT(event.key.keysym.sym) > 128 && KEYCODE_REDUIT(event.key.keysym.sym) <= 353)
				in->clavier[KEYCODE_REDUIT(event.key.keysym.sym)] = 0;
			break;

		//Gestion de la souris
		case SDL_MOUSEMOTION:
			in->posSouris.x = event.motion.x;
			in->posSouris.y = event.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			in->sourisEnfoncee = TRUE;
			in->sourisRelachee = FALSE;
			in->clicSouris.x = event.button.x;
			in->clicSouris.y = event.button.y;
			break;

		case SDL_MOUSEBUTTONUP:
			in->sourisEnfoncee = FALSE;
			in->sourisRelachee = TRUE;
			break;

		//Cas ou l'on appuie sur la croix
		case SDL_QUIT:
			in->quit = TRUE;

		default:
			break;
		}
		SDL_Delay(5);
	}
}