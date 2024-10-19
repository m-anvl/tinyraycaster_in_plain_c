#include "init.h"
#include "common.h"

void init_subsystems(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		ERR_SDL(SDL_Init, true);
	}
	atexit(SDL_Quit);

#if 0
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		ERR_SDL(IMG_Init, true);
	}
	atexit(IMG_Quit);

	if (TTF_Init() < 0) {
		ERR_SDL(TTF_Init, true);
	}
	atexit(TTF_Quit);
#endif
}

void init_app(app *game, int w, int h)
{
	init_subsystems();

	game->scr_h = SCREEN_HEIGHT;
	game->scr_w = SCREEN_WIDTH;
	game->title = WND_TITLE;

	game->wnd = SDL_CreateWindow(game->title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		game->scr_w, game->scr_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!game->wnd) {
		ERR_SDL(SDL_CreateWindow, true);
	}

	game->rndr = SDL_CreateRenderer(game->wnd, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!game->rndr) {
		ERR_SDL(SDL_CreateRenderer, true);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

}

#if 0
void init_app(SDL_Window **wnd, SDL_Renderer **rndr, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		ERR_SDL(SDL_Init, true);
	}
	atexit(SDL_Quit);

	if (SDL_CreateWindowAndRenderer(width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, wnd, rndr)) {

		printf("Error SDL_CreateWindowAndRenderer(): %s\n", SDL_GetError());
		exit(-1);
	}
}
#endif

void shutdown_app(app * game)
{
	SDL_DestroyRenderer(game->rndr);
	SDL_DestroyWindow(game->wnd);
}