/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** score.c
*/
#include "my.h"

bool create_score_texts(game_t *game, player_t *pl)
{
    char score[5];

    for (int i = 0; i < 2; i++) {
        pl->scores[i] = sfText_create();
        if (!pl->scores[i])
            return false;
        sfText_setFont(pl->scores[i], game->menu->font[1]);
        sfText_setColor(pl->scores[i], sfWhite);
        sfText_setOutlineThickness(pl->scores[i], 3);
        sfText_setOutlineColor(pl->scores[i], sfBlack);
        sfText_setCharacterSize(pl->scores[i], 30);
    }
    sfText_setString(pl->scores[0], "SCORE :");
    sfText_setPosition(pl->scores[0], (sfVector2f){600, 0});
    snprintf(score, 5, "%i", pl->score);
    sfText_setString(pl->scores[1], score);
    sfText_setPosition(pl->scores[1], (sfVector2f){730, 0});
    return true;
}

void display_score(game_t *game, player_t *pl)
{
    char score[5];

    sfRenderWindow_drawText(GAME_WIN, pl->scores[0], NULL);
    snprintf(score, 5, "%i", pl->score);
    sfText_setString(pl->scores[1], score);
    sfRenderWindow_drawText(GAME_WIN, pl->scores[1], NULL);
}
