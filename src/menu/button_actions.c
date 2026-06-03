/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** actions taken based on button
*/

#include "my.h"

void left_volume_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    if (game->volume > 0) {
        game->volume -= 10;
        sfListener_setGlobalVolume((float)game->volume);
    }
    sfSprite_setColor(button->sprite, sfWhite);
}

void right_volume_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    if (game->volume < 100) {
        game->volume += 10;
        sfListener_setGlobalVolume((float)game->volume);
    }
    sfSprite_setColor(button->sprite, sfWhite);
}

void return_main_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    (void)button;
    switch_menu(game, MAIN_MENU);
}

void play_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    (void)button;
    switch_menu(game, GAME_WINDOW);
}

void setting_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    (void)button;
    switch_menu(game, SETTINGS_MENU);
}
