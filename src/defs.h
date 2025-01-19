#ifndef DEFS_H_SENTRY
#define DEFS_H_SENTRY

#include <SDL3/SDL.h>
#include <stdint.h>

#define WND_TITLE       "Shooter"
#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   512

#define FRAMEBUFFER_SIZE SCREEN_WIDTH*SCREEN_HEIGHT

#define NUM_OF_SPRITES 5

typedef struct tag_application {
    SDL_Window* wnd;
    SDL_Renderer* rndr;
    uint32_t scr_w, scr_h;
    const char* title;
} app;

typedef struct tag_framebuffer {
    size_t w, h;
    uint32_t* img;
} framebuffer_t;

typedef struct tag_player {
    float x, y;
    float angle;
    float fov;
    int turn, walk;
} player_t;

typedef struct tag_sprite {
    float x, y;
    float player_dist;
    size_t tex_id;
} sprite_t;

typedef struct tag_map {
    int w, h;
    const char* map_str;
} map_t;

typedef struct tag_texture {
    size_t img_w, img_h;
    size_t count, size;
    uint32_t* img;
} texture_t;


#endif // !DEFS_H_SENTRY
