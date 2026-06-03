/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** create_base.C
*/
#include "my.h"

static void set_player_health_txtrs(player_t *player)
{
    player->health_max = sfTexture_createFromFile(
        "./assets/images/health-max.png", NULL);
    player->health_high = sfTexture_createFromFile(
        "./assets/images/health-mid.png", NULL);
    player->health_mid = sfTexture_createFromFile(
        "./assets/images/health-low.png", NULL);
    player->health_low = sfTexture_createFromFile(
        "./assets/images/health-verylow.png", NULL);
}

bool create_ammo_hp_textures(player_t *player)
{
    char *ammo_txtrs[4] = {"./assets/images/ammo_max.png", "./assets/images/am"
        "mo_high.png", "./assets/images/ammo_mid.png", "./assets/images/ammo_l"
        "ow.png"};

    set_player_health_txtrs(player);
    if (!player->health_max || !player->health_high || !player->health_mid ||
        !player->health_low)
        return false;
    for (int i = 0; i < 4; i++){
        player->t_ammo[i] = sfTexture_createFromFile(ammo_txtrs[i], NULL);
        if (!player->t_ammo[i])
            return false;
    }
    return true;
}

bool create_hud(game_t *game, player_t *player)
{
    sfVector2u window_size = sfRenderWindow_getSize(game->window);
    sfVector2f position_button = {0.0, 0.0};
    sfVector2f scale = {0.45, 0.45};

    player->hud = sfSprite_create();
    player->hud_txtr = sfTexture_createFromFile
        ("./assets/images/HUD.png", NULL);
    if (!player->hud || !player->hud_txtr)
        return false;
    sfSprite_setTexture(player->hud, player->hud_txtr, sfTrue);
    sfSprite_setScale(player->hud, scale);
    position_button.x = 0.0 + 5.0f;
    position_button.y = window_size.y - (335.0 * scale.y) - 10;
    sfSprite_setPosition(player->hud, position_button);
    return true;
}

sfSprite *create_health_sprite(sfTexture *texture, sfSprite *hud)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f hud_pos = sfSprite_getPosition(hud);
    sfVector2f pos = {0.0, 0.0};
    sfVector2f scale = {0.45, 0.45};

    if (!sprite)
        return NULL;
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, scale);
    pos.x = hud_pos.x + sfTexture_getSize(texture).x / 11;
    pos.y = hud_pos.y + sfTexture_getSize(texture).y * 1.99f;
    sfSprite_setPosition(sprite, pos);
    return sprite;
}

sfSprite *create_ammo_sprite(sfTexture *texture, sfSprite *hud)
{
    sfSprite *sprite = sfSprite_create();
    sfVector2f hud_pos = sfSprite_getPosition(hud);
    sfVector2f pos = {0.0, 0.0};
    sfVector2f scale = {0.45, 0.45};

    if (!sprite)
        return NULL;
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setScale(sprite, scale);
    pos.x = hud_pos.x + sfTexture_getSize(texture).x / 2.835f;
    pos.y = hud_pos.y + sfTexture_getSize(texture).y * 3.76f;
    sfSprite_setPosition(sprite, pos);
    return sprite;
}
