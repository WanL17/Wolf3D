/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** header for map stuff
*/

/* Map format */
/*
** int int   -- Map width and height
** int int   -- spawn coords (x;y), invalid if beyond world limits or in wall
** 10001     -- 1 is wall, 0 is air.
** 01100
** 11001
*/
#ifndef MAP_FILE_H
    #define MAP_FILE_H

    #include "my.h"

typedef struct {
    int width;
    int height;
    int spawn_x;
    int spawn_y;
    int **grid;
} map_t;

bool load_map(const char *path, map_t *map);
void free_map(map_t *map);
bool alloc_grid(map_t *map);
#endif
