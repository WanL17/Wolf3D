/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** difficulty.c
*/
#include "my.h"

static float get_loop_time(sfClock *clock)
{
    sfTime timer = sfClock_getElapsedTime(clock);
    float seconds = (float)(timer.microseconds) / 1000000;

    return seconds;
}

void make_entities_faster(game_t *game)
{
    if (game->entities->move - 1 > 0) {
        for (entity_t *e = game->entities; e; e = e->next)
            e->move -= 1;
    }
}

void increase_difficulty(game_t *game)
{
    float seconds = get_loop_time(game->difficulty);
    float refresh = 25;

    if (seconds >= refresh) {
        game->ent_spawn += 2;
        make_entities_faster(game);
        sfClock_restart(game->difficulty);
    }
}
