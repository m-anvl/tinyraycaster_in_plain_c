#ifndef UTILS_H_SENTRY
#define UTILS_H_SENTRY

#include <stdint.h>

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);

void unpack_color(const uint32_t* color, const uint8_t* r, const uint8_t* g, const uint8_t* b, const uint8_t* a);

void dropPpmImage(const char* fileName, uint32_t* image, size_t imageSize, const int width, const int height);

#endif // !UTILS_H_SENTRY
