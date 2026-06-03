/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** entity_comportement.c
*/
#include "my.h"

static void entity_anim_movement(entity_t *entity)
{
    sfIntRect rect = sfSprite_getTextureRect(entity->sprite);

    if (rect.left < ENTITY_WIDTH * 2)
        rect.left += ENTITY_WIDTH;
    else
        rect.left = 0;
    sfSprite_setTextureRect(entity->sprite, rect);
}

void entity_movement(game_t *game, player_t *pl, entity_t *entity)
{
    sfVector2f direction = {0};
    float speed = 0;

    if (entity->move > 0) {
        entity->move--;
        return;
    }
    direction.x = pl->x - entity->x;
    direction.y = pl->y - entity->y;
    speed = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (speed != 0) {
        direction.x /= speed;
        direction.y /= speed;
    }
    if (!is_wall(entity->x + direction.x, entity->y, game))
        entity->x += direction.x;
    if (!is_wall(entity->x, entity->y + direction.y, game))
        entity->y += direction.y;
    entity_anim_movement(entity);
    entity->move = ENTITY_SPEED;
}
