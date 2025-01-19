#ifndef TEXTURE_H_SENTRY
#define TEXTURE_H_SENTRY

#include "defs.h"

texture_t* load_texture(const char* filename, const uint32_t format);

void destroy_texture(texture_t* texture);

uint32_t get_texel(const texture_t* texture, const size_t i, const size_t j, const size_t idx);

uint32_t* texture_column(const texture_t* tex, const size_t tex_id,
    const size_t tex_coord, const size_t col_height);

#endif // !TEXTURE_H_SENTRY
