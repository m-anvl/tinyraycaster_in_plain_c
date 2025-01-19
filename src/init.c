#include "init.h"
#include "common.h"

void init_subsystems(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
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

void init_app(app* game, int w, int h)
{
    init_subsystems();

    game->scr_h = SCREEN_HEIGHT;
    game->scr_w = SCREEN_WIDTH;
    game->title = WND_TITLE;

    game->wnd = SDL_CreateWindow(game->title,
        game->scr_w, game->scr_h, SDL_WINDOW_RESIZABLE);

    if (!game->wnd) {
        ERR_SDL(SDL_CreateWindow, true);
    }

    game->rndr = SDL_CreateRenderer(game->wnd, NULL);

    if (!game->rndr) {
        ERR_SDL(SDL_CreateRenderer, true);
    }
}

void shutdown_app(app* game)
{
    SDL_DestroyRenderer(game->rndr);
    SDL_DestroyWindow(game->wnd);
}
