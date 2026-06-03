/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** use_weapons.c
*/
#include "my.h"

static void decreasing_ammo(player_t *pl, weapon_t *weapon)
{
    if (pl->cur_weapon != KNIFE_WEAPON)
        weapon->cur_ammo--;
}

static void is_entity_dead(player_t *pl, entity_t *entity)
{
    if (entity->health <= 0) {
        switch (pl->cur_weapon) {
            case GUN_WEAPON :
                pl->weapons[GUN_WEAPON].cur_ammo = GUN_AMMO;
            default :
                return;
        }
    }
}

static int collision_bullet(
    player_t *pl, sfVector2f *bullet, entity_t *entities, weapon_t *weapon)
{
    sfVector2f d = {cosf(pl->angle), sinf(pl->angle)};

    for (int i = 0; i < 1000; i++) {
        if (bullet->x >= entities->x - 10 &&
            bullet->x <= entities->x + 10 &&
            bullet->y >= entities->y - 10 &&
            bullet->y <= entities->y + 10) {
            entities->health -= weapon->damage;
            is_entity_dead(pl, entities);
            return TRUE;
        }
        bullet->x = pl->x + d.x * i;
        bullet->y = pl->y + d.y * i;
    }
    return FALSE;
}

void detect_an_enemy_gun(player_t *pl, entity_t *entities, weapon_t *weapon)
{
    sfVector2f bullet = {0};

    for (; entities; entities = entities->next) {
        bullet.x = 0;
        bullet.y = 0;
        if (collision_bullet(pl, &bullet, entities, weapon) == TRUE)
            return;
    }
}

void detect_an_enemy_knife(player_t *pl, entity_t *entities, weapon_t *weapon)
{
    sfVector2f aim = {cos(pl->angle), sin(pl->angle)};
    sfVector2f slash = {pl->x + aim.x, pl->y + aim.y};

    for (; entities; entities = entities->next) {
        if (slash.x >= entities->x - ENTITY_WIDTH && slash.x <= entities->x +
            ENTITY_WIDTH && slash.y >= entities->y - ENTITY_HEIGHT &&
            slash.y <= entities->y + ENTITY_HEIGHT) {
            entities->health -= weapon->damage;
            is_entity_dead(pl, entities);
            return;
        }
    }
}

void use_weapons(game_t *game, player_t *pl)
{
    weapon_t *weapon = &pl->weapons[pl->cur_weapon];

    if (game->event.mouseButton.button == sfMouseLeft
        && weapon->cur_ammo > 0) {
        if (weapon->time <= 0) {
            decreasing_ammo(pl, weapon);
            weapon->time = weapon->states + 1;
            sfClock_restart(weapon->clock);
            sfMusic_play(weapon->sound);
        }
        if (pl->cur_weapon == KNIFE_WEAPON) {
            detect_an_enemy_knife(pl, game->entities, weapon);
        } else {
            detect_an_enemy_gun(pl, game->entities, weapon);
        }
    }
}
