#include "common.h"

#include "defs.h"
#include "framebuffer.h"
#include "init.h"
#include "input.h"
#include "map.h"
#include "render.h"
#include "texture.h"
#include "timer.h"
#include "utils.h"

/*  Paths to assets with textures
    macro ASSETS_DIR defined in CMakeLists.txt */
#define WALL_TEX_PATH       ASSETS_DIR "walltext.bmp"
#define MONSTERS_TEX_PATH   ASSETS_DIR "monsters.bmp"

int main(int argc, char* argv[])
{
    long then;
    float remainder;

    then = SDL_GetTicks();
    remainder = 0;

    uint32_t color_white = pack_color(255, 255, 255, 255);
    uint32_t color_ray = pack_color(160, 160, 160, 255);

    framebuffer_t* fb = framebuffer_create(SCREEN_WIDTH, SCREEN_HEIGHT, color_white);
    map_t* map = map_init();

    player_t player = { 3.456f, 2.345f, 1.523f, M_PI / 3.0f, 0, 0 };

    texture_t* tex_walls = load_texture(WALL_TEX_PATH, SDL_PIXELFORMAT_ABGR8888);
    texture_t* tex_sprites = load_texture(MONSTERS_TEX_PATH, SDL_PIXELFORMAT_ABGR8888);

    if (!tex_walls || !tex_sprites) {
        puts("Failed to load textures");
        return -1;
    }

    sprite_t sprites[NUM_OF_SPRITES] = {
        {3.523f, 3.812f, 0, 2},
        {1.834f, 8.765f, 0, 0},
        {5.323f, 5.365f, 0, 1},
        {14.32f, 13.36f, 0, 3},
        {4.123f, 10.26f, 0, 1} };

    app game;
    init_app(&game, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Texture* fb_texture = SDL_CreateTexture(game.rndr, SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING, (int)fb->w, (int)fb->h);


    while (get_input(&player)) {

        // update player position
        {
            player.angle += (float)player.turn * 0.05f;

            float nx = player.x + player.walk * cosf(player.angle) * 0.1f;
            float ny = player.y + player.walk * sinf(player.angle) * 0.1f;

            if ((int)nx >= 0 && (int)nx < (int)map->w && (int)ny >= 0 && (int)ny < (int)map->h) {

                if (is_map_cell_empty(map, nx, player.y))
                    player.x = nx;
                if (is_map_cell_empty(map, player.x, ny))
                    player.y = ny;
            }

            // update dist each sprite
            for (size_t i = 0; i < NUM_OF_SPRITES; i++) {
                sprites[i].player_dist = sqrtf(pow(player.x - sprites[i].x, 2.0f) +
                    pow(player.y - sprites[i].y, 2.0f));
            }
            // sort sprites
            qsort(sprites, NUM_OF_SPRITES, sizeof(sprite_t), sprites_cmp);
        }

        // render scene to framebuffer
        render(fb, map, &player, sprites, NUM_OF_SPRITES, tex_walls,
            tex_sprites, color_white, color_ray);

        // copy framebuffer to screen
        {
            SDL_UpdateTexture(fb_texture, NULL, fb->img, (int)fb->w * 4);
            SDL_RenderClear(game.rndr);
            SDL_RenderTexture(game.rndr, fb_texture, NULL, NULL);
            SDL_RenderPresent(game.rndr);
        }

        cap_framerate(&then, &remainder);
    }

    SDL_DestroyTexture(fb_texture);

    shutdown_app(&game);

    if (map) {
        free(map);
        map = NULL;
    }

    destroy_texture(tex_walls);
    tex_walls = NULL;

    destroy_texture(tex_sprites);
    tex_sprites = NULL;

    destroy_framebuffer(fb);
    fb = NULL;

    return 0;
}
