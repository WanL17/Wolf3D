/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** Handles parsing of the map.
*/
#include "my.h"

static bool parse_header(FILE *fp, map_t *map)
{
    char line[128];

    if (!fgets(line, sizeof(line), fp))
        return false;
    if (sscanf(line, "%d %d", &map->width, &map->height) != 2)
        return false;
    if (!fgets(line, sizeof(line), fp))
        return false;
    if (sscanf(line, "%d %d", &map->spawn_x, &map->spawn_y) != 2)
        return false;
    if (map->width <= 0 || map->height <= 0)
        return false;
    return true;
}

static int parse_row(const char *line, map_t *map, int y)
{
    for (int x = 0; x < map->width; x++) {
        if (line[x] != '0' && line[x] != '1')
            return 84;
        map->grid[y][x] = line[x] - '0';
    }
    if (line[map->width] != '\n' && line[map->width] != '\0')
        return 84;
    return 0;
}

static bool read_file_lines(FILE *fp, map_t *map)
{
    char line[4096];

    for (int y = 0; y < map->height; y++) {
        if (!fgets(line, sizeof(line), fp))
            return false;
        if (parse_row(line, map, y))
            return false;
    }
    return true;
}

static bool is_invalid_spawn(const map_t *map)
{
    if (map->spawn_x < 0 || map->spawn_x >= map->width)
        return true;
    if (map->spawn_y < 0 || map->spawn_y >= map->height)
        return true;
    if (map->grid[map->spawn_y][map->spawn_x] != 0)
        return true;
    return false;
}

bool load_map(const char *path, map_t *map)
{
    FILE *fp = fopen(path, "r");

    if (!fp)
        return 84;
    map->grid = NULL;
    if (!parse_header(fp, map) || !alloc_grid(map) || !read_file_lines(fp, map)
        || is_invalid_spawn(map)) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    return true;
}
