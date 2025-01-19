#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
    return (a << 24) + (b << 16) + (g << 8) + r;
}

void unpack_color(const uint32_t* color, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a)
{
    *r = (*color >> 0) & 255;
    *g = (*color >> 8) & 255;
    *b = (*color >> 16) & 255;
    *a = (*color >> 24) & 255;
}

void dropPpmImage(const char* filename, uint32_t* image, size_t image_size,
    const int width, const int height)
{
    assert(image_size == width * height);
    FILE* fptr;
    fptr = fopen(filename, "wb");
    assert(fptr);
    fprintf(fptr, "P6\n%d %d\n255\n", width, height);

    for (size_t i = 0; i < width * height; i++) {

        uint8_t r, g, b, a;
        unpack_color(&(image[i]), &r, &g, &b, &a);
        fwrite(&r, sizeof(uint8_t), 1, fptr);
        fwrite(&g, sizeof(uint8_t), 1, fptr);
        fwrite(&b, sizeof(uint8_t), 1, fptr);
    }

    fclose(fptr);
}