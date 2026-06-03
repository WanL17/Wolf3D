/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** create_weapons.c
*/
#include "my.h"

static sfSprite *create_weapon_sprite(weapon_t *weapon, char *filename,
    sfVector2f *scale, game_t *game)
{
    sfVector2u w_size = sfRenderWindow_getSize(GAME_WIN);
    sfSprite *sprite = sfSprite_create();

    weapon->txtr = sfTexture_createFromFile(filename, NULL);
    if (!weapon->txtr || !sprite)
        return NULL;
    weapon->t_size = (sfVector2i){weapon->txtr_rect.width,
        weapon->txtr_rect.height};
    sfSprite_setTexture(sprite, weapon->txtr, sfTrue);
    sfSprite_setTextureRect(sprite, weapon->txtr_rect);
    sfSprite_setScale(sprite, *scale);
    sfSprite_setPosition(sprite, (sfVector2f){(w_size.x - weapon->t_size.x *
                scale->x) / 2, w_size.y - weapon->t_size.y * scale->y});
    return sprite;
}

static bool create_weapons2(game_t *game, player_t *player)
{
    weapon_t *gun = &player->weapons[GUN_WEAPON];

    gun->txtr_rect = (sfIntRect){0, 0, GUN_WIDTH, GUN_HEIGHT};
    gun->sprite = create_weapon_sprite(gun, GUN_SPRITE_SHEET,
        &((sfVector2f){8, 8}), game);
    gun->clock = sfClock_create();
    gun->sound = sfMusic_createFromFile(GUN_SOUND);
    if (!gun->sprite || !gun->txtr || !gun->clock || !gun->sound)
        return false;
    gun->damage = GUN_BULLET_DAMAGE;
    gun->speed = GUN_SPEED;
    gun->states = GUN_STATES;
    gun->max_ammo = GUN_AMMO;
    gun->cur_ammo = GUN_AMMO;
    return true;
}

bool create_weapons(player_t *player, game_t *game)
{
    weapon_t *knife = &player->weapons[KNIFE_WEAPON];

    player->cur_weapon = KNIFE_WEAPON;
    knife->txtr_rect = (sfIntRect){0, 0, KNIFE_WIDTH, KNIFE_HEIGHT};
    knife->sprite = create_weapon_sprite(knife,
        KNIFE_SPRITE_SHEET, &((sfVector2f){2, 2}), game);
    knife->clock = sfClock_create();
    knife->sound = sfMusic_createFromFile(KNIFE_SOUND);
    if (!knife->sprite || !knife->txtr || !knife->clock || !knife->sound)
        return false;
    knife->speed = KNIFE_SPEED;
    knife->states = KNIFE_STATES;
    knife->max_ammo = KNIFE_AMMO;
    knife->cur_ammo = KNIFE_AMMO;
    knife->damage = KNIFE_DAMAGE;
    return create_weapons2(game, player);
}
