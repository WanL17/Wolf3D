/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** passive actions of the text
*/

#include "my.h"

void text_fade(game_t *game, player_t *player, text_t *text)
{
    float seconds = 0.0;
    float speed = 2.0f;
    sfColor color = sfText_getColor(text->text);
    sfTime time = sfClock_getElapsedTime(game->menu->timer);

    (void)player;
    seconds = time.microseconds / 1000000.0f;
    color.a = (sin(seconds * speed) + 1.0f) / 2.0f * 255.0f;
    sfText_setColor(text->text, color);
}

void volume_text(game_t *game, player_t *player, text_t *text)
{
    char str[4];

    (void)player;
    snprintf(str, 4, "%d", game->volume);
    sfText_setString(text->text, str);
}

void resolution_text(game_t *game, player_t *player, text_t *text)
{
    char str[12];

    (void)player;
    if (game->menu->res_index == 0)
        snprintf(str, 9, "Windowed");
    else
        snprintf(str, 11, "Fullscreen");
    sfText_setString(text->text, str);
}

void framerate_text(game_t *game, player_t *player, text_t *text)
{
    char str[4];

    (void)player;
    snprintf(str, 4, "%i", fps_choice[game->menu->fps_index]);
    sfText_setString(text->text, str);
}

void static_text(game_t *game, player_t *player, text_t *text)
{
    (void)player;
    (void)game;
    (void)text;
    return;
}
