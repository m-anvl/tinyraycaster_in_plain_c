#ifndef MAP_H_SENTRY
#define MAP_H_SENTRY

#include "defs.h"

map_t* map_init(void);
int get_map_cell(map_t* map, const size_t i, const size_t j);
int is_map_cell_empty(map_t* map, const size_t i, const size_t j);

#endif // !MAP_H_SENTRY
