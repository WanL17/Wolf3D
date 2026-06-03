/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** more button_actions
*/

#include "my.h"

void quit_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    (void)button;
    sfRenderWindow_close(game->window);
}

void left_res_button(game_t *game, player_t *player, button_t *button)
{
    sfVideoMode mode = {800, 600, 32};

    (void)player;
    if (game->menu->res_index - 1 >= 0) {
        game->menu->res_index--;
        sfRenderWindow_destroy(game->window);
        game->window = sfRenderWindow_create(mode, "Wolf3D", sfDefaultStyle,
            NULL);
    }
    sfSprite_setColor(button->sprite, sfWhite);
}

void right_res_button(game_t *game, player_t *player, button_t *button)
{
    sfVideoMode mode = {800, 600, 32};

    (void)player;
    if (game->menu->res_index + 1 <= 2) {
        game->menu->res_index++;
        sfRenderWindow_destroy(game->window);
        game->window = sfRenderWindow_create(mode, "Wolf3D", sfFullscreen,
            NULL);
    }
    sfSprite_setColor(button->sprite, sfWhite);
}

void left_fps_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    if (game->menu->fps_index - 1 >= 0) {
        game->menu->fps_index--;
        sfRenderWindow_setFramerateLimit(
            game->window, fps_choice[game->menu->fps_index]);
    }
    sfSprite_setColor(button->sprite, sfWhite);
}

void right_fps_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    if (game->menu->fps_index + 1 <= 8) {
        game->menu->fps_index++;
        sfRenderWindow_setFramerateLimit(
            game->window, fps_choice[game->menu->fps_index]);
    }
    sfSprite_setColor(button->sprite, sfWhite);
}
