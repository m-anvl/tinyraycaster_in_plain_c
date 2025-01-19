#include <SDL3/SDL.h>
#include "input.h"

enum { EXIT_APP = 0, CONTINUE_APP = 1 };

SDL_Event event;

int get_input(player_t* player)
{
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT ||
			(SDL_KEYDOWN == event.type &&
				SDLK_ESCAPE == event.key.keysym.sym))
			return EXIT_APP;

		if (SDL_KEYUP == event.type) {

			switch (event.key.keysym.sym) {
			case 'a':
			case 'd':
				player->turn = 0;
				break;
			case 'w':
			case 's':
				player->walk = 0;
				break;
			default:
				break;
			}
		}

		if (SDL_KEYDOWN == event.type) {

			switch (event.key.keysym.sym) {
			case 'a':
				player->turn = -1;
				break;
			case 'd':
				player->turn = 1;
				break;
			case 'w':
				player->walk = 1;
				break;
			case 's':
				player->walk = -1;
				break;
			default:
				break;
			}
		}
	}

	return CONTINUE_APP;
}
