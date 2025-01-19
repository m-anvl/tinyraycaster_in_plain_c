#include <SDL3/SDL.h>
#include <time.h>

#include "timer.h"

void cap_framerate(int32_t* then, float* remainder)
{
    int32_t wait, frame_time;

    wait = (int32_t)(16.0f + *remainder);

    *remainder -= (int32_t)*remainder;

    frame_time = SDL_GetTicks() - *then;

    wait -= frame_time;

    if (wait < 1)
        wait = 1;

    SDL_Delay((uint32_t)wait);

    *remainder += 0.334f;
    *then = SDL_GetTicks();
}
