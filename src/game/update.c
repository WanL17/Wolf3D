/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** the updating portion of sprite rendering
*/

#include "my.h"

float get_elapsed_time(sfClock *clock)
{
    return sfTime_asSeconds(sfClock_getElapsedTime(clock));
}

static void update_weapon(game_t *game, player_t *player)
{
    double seconds;
    weapon_t *weapon = &player->weapons[player->cur_weapon];

    (void)game;
    if (!weapon->time)
        return;
    seconds = get_elapsed_time(weapon->clock);
    if (seconds >= weapon->speed) {
        sfClock_restart(weapon->clock);
        if (weapon->time > 1)
            weapon_sprite_anim(player);
        weapon->time--;
    }
}

static void update_player(game_t *game, player_t *player)
{
    float bobbing = 0;

    for (int i = 0; i < 4; i++){
        if (player->inputs[i]){
            angle_to_player_movement(player, (-1 + i * 0.5) * M_PI, game);
            bobbing = BOBBING_SPEED;
        }
    }
    if (bobbing)
        player->bobbing = fmod(player->bobbing + bobbing, M_PI * 2);
    if (!bobbing)
        neutralise_bobbing(player);
    player->angle += player->new_angle;
    while (player->angle < M_PI * -1)
        player->angle += M_PI * 2;
    while (player->angle > M_PI)
        player->angle -= M_PI * 2;
}

static void update_sky(game_t *game, player_t *player)
{
    sfFloatRect sky_rect = sfSprite_getGlobalBounds(game->sky);
    sfVector2f new_position = {0, 0};

    new_position.x = sky_rect.left - player->new_angle * SKY_SPEED;
    while (new_position.x < 0)
        new_position.x = SCREEN_WIDTH + new_position.x;
    new_position.x = fmod(new_position.x, SCREEN_WIDTH);
    sfSprite_setPosition(game->sky, new_position);
}

void update_sprites(game_t *game, player_t *player)
{
    update_weapon(game, player);
    update_entities(game, player);
    update_player(game, player);
    update_sky(game, player);
}
