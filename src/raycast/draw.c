/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** draw sprites and the such
*/

#include "my.h"

static void draw_weapon(game_t *game, player_t *player)
{
    weapon_t *weapon = &player->weapons[player->cur_weapon];

    if (weapon->time > 1)
        sfRenderWindow_drawSprite(GAME_WIN, weapon->sprite, NULL);
}

void draw_sky(game_t *game)
{
    sfVector2f new_position = {0, 0};
    sfFloatRect sky_rect = sfSprite_getGlobalBounds(game->sky);

    sky_rect = sfSprite_getGlobalBounds(game->sky);
    sfRenderWindow_drawSprite(game->window, game->sky, NULL);
    new_position.x = sky_rect.left - SCREEN_WIDTH;
    sfSprite_setPosition(game->sky, new_position);
    sfRenderWindow_drawSprite(game->window, game->sky, NULL);
    new_position.x += SCREEN_WIDTH;
    sfSprite_setPosition(game->sky, new_position);
}

void draw_sprites(game_t *game, player_t *player)
{
    draw_entities(game, player);
    draw_weapon(game, player);
    draw_particles(game, game->particule);
}
