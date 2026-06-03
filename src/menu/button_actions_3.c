/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** more button_actions
*/

#include "my.h"

void return_pause_button(game_t *game, player_t *player, button_t *button)
{
    (void)player;
    (void)button;
    switch_menu(game, PAUSE_WINDOW);
}
