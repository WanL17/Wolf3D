/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** weapons_animation.c
*/
#include "my.h"

static void reset_weapon_anim(weapon_t *weapon)
{
    if (weapon->txtr_rect.left >= weapon->t_size.x * weapon->states)
        weapon->txtr_rect.left = 0;
}

void weapon_sprite_anim(player_t *pl)
{
    weapon_t *weapon = &pl->weapons[pl->cur_weapon];

    weapon->txtr_rect.left += weapon->t_size.x;
    reset_weapon_anim(weapon);
    sfSprite_setTextureRect(weapon->sprite, weapon->txtr_rect);
    sfClock_restart(weapon->clock);
}
