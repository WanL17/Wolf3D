/*
** EPITECH PROJECT, 2026
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** create_entities.c
*/
#include "my.h"

static int count_entities(entity_t *entities)
{
    int count = 0;

    for (; entities; entities = entities->next) {
        count++;
    }
    return count;
}

void make_entities_spawn(game_t *game)
{
    while (count_entities(game->entities) < game->ent_spawn)
        spawn_entity(game, ENTITY_BULLET, game->enemy_txtr);
}
