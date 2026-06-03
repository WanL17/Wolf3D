/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** update.c
** This is what every entity will run on each frame and where its behaviour
** will happen.
*/
#include "game.h"

static void hp_pickup(entity_t *entity, player_t *pl)
{
    if (entity->type == ENTITY_PICKUP_HP) {
        if (player_entity_collision(pl, entity)) {
            entity->alive = 0;
            pl->hp += 50;
        }
    }
}

static void bullet(entity_t *entity, player_t *pl)
{
    if (entity->type == ENTITY_BULLET) {
        if (player_entity_collision(pl, entity)) {
            entity->alive = 0;
            pl->hp -= ENTITY_DAMAGE;
        }
    }
}

static void default_update(entity_t *entity, player_t *pl)
{
    if (!entity->alive)
        return;
    hp_pickup(entity, pl);
    bullet(entity, pl);
    if (entity->health <= 0)
        entity->alive = false;
}

static void destroy_entity(player_t *player, entity_t *entity)
{
    if (entity->sprite)
        sfSprite_destroy(entity->sprite);
    free(entity);
    player->score += 100;
}

static void unlink_entity(entity_t *entity, entity_t **list, entity_t *prev)
{
    if (prev)
        prev->next = entity->next;
    else
        *list = entity->next;
}

void update_entities(game_t *game, player_t *player)
{
    entity_t *entity = game->entities;
    entity_t *prev = NULL;
    entity_t *next;

    while (entity) {
        next = entity->next;
        if (entity->update)
            entity->update(entity, game, player);
        else
            default_update(entity, player);
        if (!entity->alive) {
            unlink_entity(entity, &game->entities, prev);
            destroy_entity(player, entity);
            entity = next;
            continue;
        }
        entity_movement(game, player, entity);
        prev = entity;
        entity = next;
    }
}
