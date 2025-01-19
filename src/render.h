#ifndef RENDER_H_SENTRY
#define RENDER_H_SENTRY

#include "common.h"

#include "defs.h"
#include "utils.h"
#include "texture.h"
#include "framebuffer.h"
#include "map.h"

void render(framebuffer_t* fb, map_t* map, player_t* player,
    sprite_t sprites[], size_t sprites_cnt, texture_t* tex_walls,
    texture_t* tex_sprite, const uint32_t color_clear, const uint32_t color_cone);

int sprites_cmp(const sprite_t* a, const sprite_t* b);

#endif // !RENDER_H_SENTRY
