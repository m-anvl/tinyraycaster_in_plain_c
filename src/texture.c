#include <assert.h>
#include <stdio.h>
#include <SDL3/SDL.h>

#include "utils.h"
#include "texture.h"

texture_t* load_texture(const char *filename, const uint32_t format)
{
	texture_t* texture = (texture_t*)malloc(sizeof(*texture));
	assert(texture);

	SDL_Surface* tmp = SDL_LoadBMP(filename);
	if (!tmp) {
		printf("Error SDL_LoadBMP(): %s\n", SDL_GetError());
		return NULL;
	}

	SDL_Surface* surface = SDL_ConvertSurface(tmp, format);
    SDL_DestroySurface(tmp);

	if (!surface) {
		printf("Error SDL_ConvertSurfaceFormat(): %s\n", SDL_GetError());
		return NULL;
	}

	int w = surface->w;
	int h = surface->h;

	if (w * 4 != surface->pitch) {
		puts("Error: the texture must be a 32 bit image");
		SDL_DestroySurface(surface);
		return NULL;
	}

	if (w != h * (w / h)) {
		puts("Error: the texture file must contain N square textures packed horizontally");
        SDL_DestroySurface(surface);
		return NULL;
	}

	texture->count = w / h;
	texture->size = w / texture->count;
	texture->img_w = w;
	texture->img_h = h;

	uint8_t* pix_map = surface->pixels;

	texture->img = (uint32_t*)malloc(sizeof(uint32_t) * w * h);
	assert(texture->img);

	for (size_t j = 0; j < h; j++) {

		for (size_t i = 0; i < w; i++) {
			uint8_t r = pix_map[(i + j * w) * 4 + 0];
			uint8_t g = pix_map[(i + j * w) * 4 + 1];
			uint8_t b = pix_map[(i + j * w) * 4 + 2];
			uint8_t a = pix_map[(i + j * w) * 4 + 3];

			//assert(i + j * w > w * h);
			texture->img[i + j * w] = pack_color(r, g, b, a);
		}
	}

    SDL_DestroySurface(surface);

	return texture;
}

void destroy_texture(texture_t* texture)
{
	if (texture) {
		free(texture->img);
		texture->img = NULL;
		free(texture);
	}
}

uint32_t get_texel(const texture_t *texture, const size_t i, const size_t j, const size_t idx)
{
	assert(i < texture->size && j < texture->size && idx < texture->count);

	return texture->img[i + idx * texture->size + j*texture->img_w];
}

uint32_t* texture_column(const texture_t *tex, const size_t tex_id,
	const size_t tex_coord, const size_t col_height)
{	
	assert(tex_coord < tex->size && tex_id < tex->count);

	uint32_t* column = (uint32_t*)malloc(sizeof(uint32_t) * col_height);
	assert(column);

	for (size_t y = 0; y < col_height; y++) {
		column[y] = get_texel(tex, tex_coord, (y * tex->size) / col_height, tex_id);
	}

	return column;
}
