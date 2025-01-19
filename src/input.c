#include <SDL3/SDL.h>
#include "input.h"

enum { EXIT_APP = 0, CONTINUE_APP = 1 };

SDL_Event event;

int get_input(player_t* player)
{
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT ||
            (SDL_EVENT_KEY_DOWN == event.type &&
                SDLK_ESCAPE == event.key.key))
            return EXIT_APP;

        if (SDL_EVENT_KEY_UP == event.type) {

            switch (event.key.key) {
            case SDLK_A:
            case SDLK_D:
                player->turn = 0;
                break;
            case SDLK_W:
            case SDLK_S:
                player->walk = 0;
                break;
            default:
                break;
            }
        }

        if (SDL_EVENT_KEY_DOWN == event.type) {

            switch (event.key.key) {
            case SDLK_A:
                player->turn = -1;
                break;
            case SDLK_D:
                player->turn = 1;
                break;
            case SDLK_W:
                player->walk = 1;
                break;
            case SDLK_S:
                player->walk = -1;
                break;
            default:
                break;
            }
        }
    }

    return CONTINUE_APP;
}
