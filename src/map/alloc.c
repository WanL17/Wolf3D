/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** Handles allocs and freeing the map.
*/
#include "my.h"

bool alloc_grid(map_t *map)
{
    map->grid = calloc(map->height, sizeof(int *));
    if (!map->grid)
        return false;
    for (int y = 0; y < map->height; y++) {
        map->grid[y] = calloc(map->width, sizeof(int));
        if (!map->grid[y]) {
            return false;
        }
    }
    return true;
}

void free_map(map_t *map)
{
    if (!map && !map->grid)
        return;
    if (map->grid){
        for (int y = 0; y < map->height; y++)
            free(map->grid[y]);
        free(map->grid);
    }
    free(map);
}
