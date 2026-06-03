/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** spawn.c
** TODO: Later on the different variables (like spd_x and sprite origin)
** will be changed based on entity->type.
*/

#include "game.h"

static sfVector2f random_vector2f(sfVector2f *max)
{
    sfVector2f v;

    v.x = ((float)rand() / (float)RAND_MAX) * max->x;
    v.y = ((float)rand() / (float)RAND_MAX) * max->y;
    return v;
}

void set_en_default_var(game_t *game, entity_t *entity, entity_type_t type)
{
    sfVector2f map_size = {game->map->width * 64, game->map->height * 64};
    sfVector2f pos = random_vector2f(&map_size);
    sfIntRect rect = {0};

    while (is_wall(pos.x, pos.y, game))
        pos = random_vector2f(&map_size);
    entity->type = type;
    entity->x = pos.x;
    entity->y = pos.y;
    entity->alive = true;
    entity->move = ENTITY_SPEED;
    entity->health = ENTITY_HEALTH;
    rect.height = ENTITY_WIDTH;
    rect.width = ENTITY_HEIGHT;
    rect.left = 0;
    rect.top = 0;
    sfSprite_setTextureRect(entity->sprite, rect);
}

void spawn_entity(game_t *game, entity_type_t type, sfTexture *texture)
{
    entity_t *entity = malloc(sizeof(*entity));
    sfFloatRect b;

    if (!entity)
        return;
    entity->sprite = sfSprite_create();
    entity->update = NULL;
    if (!entity->sprite) {
        free(entity);
        return;
    }
    sfSprite_setTexture(entity->sprite, texture, sfTrue);
    set_en_default_var(game, entity, type);
    b = sfSprite_getLocalBounds(entity->sprite);
    sfSprite_setOrigin(entity->sprite, (sfVector2f){b.width / 2.f, b.height});
    sfSprite_setScale(entity->sprite, (sfVector2f){20, 20});
    entity->next = game->entities;
    game->entities = entity;
}
