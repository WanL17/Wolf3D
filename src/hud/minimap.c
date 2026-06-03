/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** minimap.c
*/
#include "my.h"

static void create_player_pos_point(game_t *game, player_t *player)
{
    sfCircleShape *pl = sfCircleShape_create();
    sfVector2f pos = {player->x / 4, player->y / 4};

    if (!pl)
        return;
    sfCircleShape_setRadius(pl, 4.0);
    sfCircleShape_setOrigin(pl, (sfVector2f){4.0, 4.0});
    sfCircleShape_setFillColor(pl, sfGreen);
    sfCircleShape_setPosition(pl, pos);
    sfRenderWindow_drawCircleShape(game->window, pl, NULL);
    sfCircleShape_destroy(pl);
}

static void create_entity_pos_point(game_t *game)
{
    sfCircleShape *circle = sfCircleShape_create();
    entity_t *entity = game->entities;

    if (!circle)
        return;
    sfCircleShape_setRadius(circle, 4.0);
    sfCircleShape_setOrigin(circle, (sfVector2f){4.0, 4.0});
    sfCircleShape_setFillColor(circle, sfRed);
    while (entity){
        sfCircleShape_setPosition(circle, (sfVector2f){entity->x / 4,
                entity->y / 4});
        sfRenderWindow_drawCircleShape(game->window, circle, NULL);
        entity = entity->next;
    }
    sfCircleShape_destroy(circle);
}

static void draw_minimap_tile(sfRectangleShape *minimap, game_t *game,
    int x, int y)
{
    sfRectangleShape_setPosition(minimap, (sfVector2f){
            x * 16,
            y * 16
    });
    if (game->map->grid[y][x] == 1)
        sfRectangleShape_setFillColor(minimap, sfColor_fromRGB(
                128, 128, 128));
    else
        sfRectangleShape_setFillColor(minimap, sfBlack);
    sfRenderWindow_drawRectangleShape(game->window, minimap,
        NULL);
}

void create_minimap(game_t *game, player_t *player)
{
    sfRectangleShape *minimap = sfRectangleShape_create();
    sfVector2f size = {TILE_SIZE / 4.0f, TILE_SIZE / 4.0f};

    if (!minimap)
        return;
    sfRectangleShape_setSize(minimap, size);
    sfRectangleShape_setScale(minimap, (sfVector2f){1.0, 1.0});
    sfRectangleShape_setFillColor(minimap, sfBlack);
    for (int y = 0; y < game->map->height; y++)
        for (int x = 0; x < game->map->width; x++)
            draw_minimap_tile(minimap, game, x, y);
    create_entity_pos_point(game);
    create_player_pos_point(game, player);
    sfRectangleShape_destroy(minimap);
}
