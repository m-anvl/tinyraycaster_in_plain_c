#include "render.h"

#define DEPTH_BUFFER_SIZE SCREEN_WIDTH/2

int sprites_cmp(const sprite_t* a, const sprite_t* b)
{
    return b->player_dist - a->player_dist;
}


int wall_tex_coord_x(const float hit_x, const float hit_y, texture_t* tex_walls)
{
    float x = hit_x - floorf(hit_x + .5f);
    float y = hit_y - floorf(hit_y + .5f);

    int tex = x * tex_walls->size;

    if (fabsf(y) > fabsf(x)) {
        tex = y * tex_walls->size;
    }

    if (tex < 0) {
        tex += tex_walls->size;
    }

    assert(tex >= 0 && tex < (int)(tex_walls->size));

    return tex;
}

void mapShowSprite(sprite_t* sprite, framebuffer_t* fb, map_t* map)
{
    const size_t rectW = fb->w / (map->w * 2);
    const size_t rectH = fb->h / map->h;

    draw_rect(fb, sprite->x * rectW - 3, sprite->y * rectH - 1,
        6, 6, pack_color(255, 0, 0, 255));
}

void draw_sprite(sprite_t* sprite, float* depth_buffer, framebuffer_t* fb,
    player_t* player, texture_t* tex_sprite)
{
    float sprite_dir = atan2f(sprite->y - player->y, sprite->x - player->x);

    while (sprite_dir - player->angle > M_PI) {
        sprite_dir -= 2 * M_PI;
    }

    while (sprite_dir - player->angle < -M_PI) {
        sprite_dir += 2 * M_PI;
    }

    size_t sprite_screen_size = min(1000, (int)(fb->h / sprite->player_dist));

    int h_offset = (sprite_dir - player->angle) * (fb->w / 2) / player->fov + (fb->w / 2) / 2 - sprite_screen_size / 2;
    int v_offset = fb->h / 2 - sprite_screen_size / 2;

    for (size_t i = 0; i < sprite_screen_size; i++) {

        if (h_offset + (int)i < 0 || h_offset + i >= fb->w / 2) {
            continue;
        }

        if (depth_buffer[h_offset + i] < sprite->player_dist) {
            continue;
        }

        for (size_t j = 0; j < sprite_screen_size; j++) {

            if (v_offset + (int)j < 0 || v_offset + j >= fb->h) {
                continue;
            }

            uint32_t color = get_texel(tex_sprite, i * tex_sprite->size / sprite_screen_size,
                j * tex_sprite->size / sprite_screen_size, sprite->tex_id);

            uint8_t r, g, b, a;
            unpack_color(&color, &r, &g, &b, &a);

            if (a > 128) {
                set_pixel(fb, fb->w / 2 + h_offset + i, v_offset + j, color);
            }
        }
    }
}

void render(framebuffer_t* fb, map_t* map, player_t* player, sprite_t sprites[], size_t sprites_cnt,
    texture_t* tex_walls, texture_t* texSprite, const uint32_t colorClear, const uint32_t colorCone)
{
    clear_screen(fb, colorClear);

    // draw map
    const size_t rectW = fb->w / (map->w * 2); //size one map cell
    const size_t rectH = fb->h / map->h;

    for (size_t j = 0; j < map->h; j++)
    {
        for (size_t i = 0; i < map->w; i++) {

            if (is_map_cell_empty(map, i, j)) {
                continue;
            }

            size_t rectX = i * rectW;
            size_t rectY = j * rectH;
            size_t texID = get_map_cell(map, i, j);
            assert(texID < tex_walls->count);
            draw_rect(fb, rectX, rectY, rectW, rectH, get_texel(tex_walls, 0, 0, texID));
        }
    }

    float depth_buffer[DEPTH_BUFFER_SIZE];
    for (int d = 0; d < DEPTH_BUFFER_SIZE; d++)
        depth_buffer[d] = 1000.0f;

    // draw visible cone and 3D view
    for (size_t i = 0; i < fb->w / 2; i++) {
        float angle = player->angle - player->fov / 2 + player->fov * i / (float)(fb->w / 2);

        //ray
        for (float t = 0.0f; t < 20; t += 0.01f) {

            float x = player->x + t * cosf(angle);
            float y = player->y + t * sinf(angle);
            set_pixel(fb, x * rectW, y * rectH, colorCone); // draw cone

            if (is_map_cell_empty(map, x, y)) {
                continue;
            }

            size_t texID = get_map_cell(map, x, y);
            assert(texID < tex_walls->count);

            float dist = t * cosf(angle - player->angle);
            depth_buffer[i] = dist;
            size_t column_height = min(2000, (int)(fb->h / dist));
            int tex_coord_x = wall_tex_coord_x(x, y, tex_walls);

            uint32_t* column = texture_column(tex_walls, texID, tex_coord_x, column_height);

            int pixX = i + fb->w / 2;

            for (size_t j = 0; j < column_height; j++) {
                int pixY = j + fb->h / 2 - column_height / 2;

                if (pixY >= 0 && pixY < (int)(fb->h)) {
                    set_pixel(fb, pixX, pixY, column[j]);
                }
            }

            free(column);
            column = NULL;
            break;
        }
    }

    // update player distance
    for (size_t i = 0; i < sprites_cnt; i++) {
        sprites[i].player_dist = sqrtf(
            powf(player->x - sprites[i].x, 2.0f)
            + powf(player->y - sprites[i].y, 2.0f));
    }

    // sort sprites
    qsort(sprites, sprites_cnt, sizeof(sprite_t), sprites_cmp);

    // draw sprites
    for (size_t i = 0; i < sprites_cnt; i++) {
        mapShowSprite(&sprites[i], fb, map);
        draw_sprite(&sprites[i], depth_buffer, fb, player, texSprite);
    }
}
