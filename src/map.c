#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "map.h"

static const char map_sample[] = "0000222222220000"\
                                 "1              5"\
                                 "1              5"\
                                 "1     01111    5"\
                                 "0     0        5"\
                                 "0     3     1155"\
                                 "0   1000       5"\
                                 "0   3  0       5"\
                                 "5   4  100011  5"\
                                 "5   4   1      4"\
                                 "0       1      4"\
                                 "2       1  44444"\
                                 "0     000      4"\
                                 "0 111          4"\
                                 "0              4"\
                                 "0002222244444444";

map_t* map_init(void)
{
    int w = 16;
    int h = 16;
    assert(strlen(map_sample) == w * h);

    map_t* map = NULL;
    map = (map_t*)malloc(sizeof(*map));
    assert(map);

    map->w = w;
    map->h = h;
    map->map_str = map_sample;

    return map;
}

int get_map_cell(map_t* map, const size_t i, const size_t j)
{
    assert(i < map->w&& j < map->h);

    return map->map_str[i + j * map->w] - '0';
}

int is_map_cell_empty(map_t* map, const size_t i, const size_t j)
{
    assert(i < map->w&& j < map->h);

    return map->map_str[i + j * map->w] == ' ';
}

