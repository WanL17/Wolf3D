/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** destroy sprite structures and the such
*/

#include "my.h"

void destroy_entities(game_t *game)
{
    entity_t *current = game->entities;
    entity_t *next;

    while (current) {
        next = current->next;
        if (current->sprite)
            sfSprite_destroy(current->sprite);
        free(current);
        current = next;
    }
    game->entities = NULL;
}
