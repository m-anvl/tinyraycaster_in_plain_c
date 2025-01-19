#ifndef INIT_H_SENTRY
#define INIT_H_SENTRY

#include "defs.h"

void init_app(app* game, int w, int h);
void shutdown_app(app* game);

#if 0
void init_app(SDL_Window **wnd, SDL_Renderer **rndr, int width, int height);
#endif

#endif // !INIT_H_SENTRY
