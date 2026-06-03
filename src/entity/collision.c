/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** Handles collisions.
*/

#include "game.h"

static float entity_hitbox_size(entity_t *entity)
{
    if (entity->type == ENTITY_PICKUP_HP || entity->type == ENTITY_PICKUP_AMMO)
        return 12.f;
    if (entity->type == ENTITY_BULLET)
        return 4.0f;
    return 10.f;
}

int player_entity_collision(player_t *player, entity_t *entity)
{
    float dx = player->x - entity->x;
    float dy = player->y - entity->y;
    float radius = entity_hitbox_size(entity);

    return dx * dx + dy * dy <= radius * radius;
}
