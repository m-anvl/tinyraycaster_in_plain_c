#ifndef FRAMEBUFFER_H_SENTRY
#define FRAMEBUFFER_H_SENTRY

#include "defs.h"

framebuffer_t* framebuffer_create(const size_t w, const size_t h, const uint32_t clearColor);

void clear_screen(framebuffer_t* fb, const uint32_t color);

void set_pixel(framebuffer_t* fb, const size_t x, const size_t y, const uint32_t color);

void draw_rect(framebuffer_t* fb, const size_t rectX, const size_t rectY,
	const size_t rectW, const size_t rectH, const uint32_t color);

#endif // !FRAMEBUFFER_H_SENTRY
