#include <assert.h>
#include <stdlib.h>

#include "framebuffer.h"
#include "utils.h"

framebuffer_t* framebuffer_create(const size_t w, const size_t h, const uint32_t clear_color)
{
	framebuffer_t* fb = (framebuffer_t*)malloc(sizeof(*fb));
	assert(fb);

	fb->w = w;
	fb->h = h;
	fb->img = (uint32_t*)malloc(sizeof(uint32_t) * w * h);

	assert(fb->img);

	clear_screen(fb, clear_color);

	return fb;
}

void destroy_framebuffer(framebuffer_t* fb)
{
	if (fb) {
		free(fb->img);
		fb->img = NULL;
		free(fb);
	}
}

void clear_screen(framebuffer_t* fb, const uint32_t color)
{
	size_t screen_size = fb->w * fb->h;
	for (size_t i = 0; i < screen_size; i++) {
		fb->img[i] = color;
	}
}

void set_pixel(framebuffer_t* fb, const size_t x, const size_t y, const uint32_t color)
{
	assert(x < fb->w && y < fb->h);
	fb->img[x + y * fb->w] = color;
}

void draw_rect(framebuffer_t* fb, const size_t x, const size_t y,
	const size_t w, const size_t h, const uint32_t color)
{
	for (size_t i = 0; i < w; i++) {

		for (size_t j = 0; j < h; j++) {

			size_t cx = x + i;
			size_t cy = y + j;

			if (cx < fb->w && cy < fb->h) {
				set_pixel(fb, cx, cy, color);
			}
		}
	}
}